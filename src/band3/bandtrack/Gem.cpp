#include "Gem.h"
#include "bandtrack/GemManager.h"
#include "bandtrack/TrackConfig.h"
#include "beatmatch/RGUtl.h"
#include "os/Debug.h"
#include "track/TrackWidget.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/TimeConversion.h"

Gem::Gem(
    const GameGem &gg, unsigned int ui, float f1, float f2, bool b1, int i1, int i2, bool b2
)
    : mGameGem(&gg), mStart(f1), mEnd(f2), mTailStart(0), mSlots(ui), mBeardTick(i1),
      unk_0x3C(0), unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(""),
      mFirstFretString(-1), mFretPos(0), unk_0x65(-1) {
    InitChordInfo(i2, b2);
}

Gem::~Gem() { DeleteAll(mTails); }

Gem &Gem::operator=(const Gem &g) {
    (GameGem &)(*mGameGem) = *(g.mGameGem);
    mSlots = g.mSlots;

    mStart = g.mStart;
    mTailStart = g.mTailStart;
    mEnd = g.mEnd;

    mHopo = g.mHopo;
    mMissed = g.mMissed;
    mHit = g.mHit;
    mReleased = g.mReleased;
    mInvisible = g.mInvisible;

    mTails = g.mTails;
    mWidgets = g.mWidgets;
}

bool Gem::OnScreen(float ms) {
    float bottomSeconds = mGemManager->mTrackDir->BottomSeconds();

    return (ms / 1000.0f) + bottomSeconds > mEnd;
}

void Gem::Poll(float f1, float f2, float f3, float f4, float f5) {
    if (CompareBounds()) {
        float fvar1 = mStart;
        if (f4 > fvar1) {
            float fvar2 = mEnd - fvar1;
            if (f4 < fvar2)
                fvar2 = f4 - fvar1;
            float fvar3 = mTailStart;
            ApplyDuration(
                mGemManager->mTrackDir->SecondsToY(fvar3),
                mGemManager->mTrackDir->SecondsToY(f5 - fvar1),
                mGemManager->mTrackDir->SecondsToY(fvar2)
            );
            for (int i = 0; i < mTails.size(); i++) {
                mTails[i]->Poll(f1, f2, f3);
            }
        }
    }
}

void Gem::AddRep(
    GemRepTemplate &repTemp, RndGroup *grp, Symbol s, const TrackConfig &cfg, bool b5
) {
    static float startOffset = 1.5f;
    SetType(s);
    if (s != "invisible" && CompareBounds() && b5) {
        float f9 = mGemManager->mTrackDir->SecondsToY(mGameGem->mMs / 1000.0f);
        Tail *i1 = 0;
        if (mTailStart < 0)
            mTailStart = 0;
        bool rg = UseRGChordStyle();
        float f10 = mGemManager->mTrackDir->SecondsToY(mEnd - mStart);
        int i3 = mGemManager->GetMaxSlots();
        for (int i = 0; i < i3; i++) {
            if ((mSlots & 1 << i) && (!rg || mGameGem->GetRGNoteType(i) != 1)) {
                Tail *tail = new Tail(repTemp);
                mTails.push_back(tail);
                mTails.back()->SetDuration(0, 0, f10);
                Tail::SlideInfo info;
                if (mGameGem->LeftHandSlide()) {
                    info.unk0 = true;
                    if (unk_0x67_4) {
                        info.unk8 = startOffset;
                        info.unk4 = -startOffset;
                    } else {
                        info.unk4 = startOffset;
                        info.unk8 = -startOffset;
                    }
                    info.unkc = f10;
                }
                Transform tf90 = mGemManager->mTrackDir->mSlots[i];
                tf90.v.y = f9;
                tail->Init(i, tf90, rg, s, grp, info, i1);
                if (!i1 && !cfg.AllowsPartialHits())
                    i1 = tail;
            }
        }
    }
}

bool Gem::UseRGChordStyle() const {
    bool r = false;
    if (mGameGem->IsRealGuitarChord() || unk_0x67_1 || mGameGem->IsMuted())
        r = true;
    return r;
}

void Gem::RemoveRep() {
    for (int i = 0; i < mTails.size(); i++) {
        delete mTails[i];
    }
    mTails.clear();
}

void Gem::AddInstance(Symbol s1, int i2) {
    GemManager *mgr = mGemManager;
    if (mgr && mgr->mTrackDir && mgr->SlotEnabled(i2)) {
        TrackConfig *cfg = mGemManager->mTrackConfig;
        Symbol s1b8;
        Symbol s1bc = s1.mStr;
        if (mHopo && !cfg->GetDisableHopos()) {
            s1bc = MakeString("%s_hopo", s1bc.mStr);
        } else if (Check66B0()) {
            s1bc = MakeString("%s_cymbal", s1bc.mStr);
        }

        if (unk_0x66_6) {
            s1bc = MakeString("%s_arrhythmic", s1bc.mStr);
        }

        if (mGemManager->GetWidgetName(s1b8, i2, s1bc)
            && mGemManager->GetWidgetName(s1b8, i2, s1bc)) {
            if (mGameGem->IsRealGuitar()) {
                int i6 = mFretPos;
                if (cfg->IsLefty())
                    i6 = 4 - i6;
                s1b8 = MakeString("%s%02d.wid", s1b8.mStr, i6);
            }
            AddWidgetInstanceImpl(mGemManager->GetWidgetByName(s1b8), i2);
        } else
            MILO_WARN(
                "could not find widget for slot %d %s gem in %s",
                i2,
                s1.mStr,
                mGemManager->mTrackDir->Name()
            );

        if (mBeard) {
            Symbol s1c0;
            if (mGemManager->GetWidgetName(s1c0, i2, beard)) {
                TrackWidget *w2 = mGemManager->GetWidgetByName(s1c0);
                Transform tf68;
                mGemManager->mTrackDir->MakeWidgetXfm(i2, TickToSeconds(mBeardTick), tf68);
                w2->AddInstance(Transform(tf68), TickToSeconds(GetBeardThreshold()));
            }
        }

        if (unk_0x3C != 0) {
            Symbol s1c4;
            if (mGemManager->GetWidgetName(s1c4, i2, mash)) {
                TrackWidget *w2 = mGemManager->GetWidgetByName(s1c4);
                Transform tf98;
                mGemManager->mTrackDir->MakeWidgetXfm(i2, mGameGem->mMs / 1000.0f, tf98);
                w2->AddInstance(Transform(tf98), unk_0x3C);
            }
        }

        if (unk_0x65 != -1) {
            Symbol s1c8;
            if (mGemManager->GetWidgetName(s1c8, i2, fret_num)) {
                TrackWidget *wcc = mGemManager->GetWidgetByName(s1c8);
                Transform tfc8;
                mGemManager->mTrackDir->MakeWidgetXfm(i2, mGameGem->mMs / 1000.0f, tfc8);
                Vector3 v164(0, 0, 0);
                if (cfg->IsLefty()) {
                    v164.x = -v164.x;
                }
                Multiply(v164, tfc8, tfc8.v);
                int i1 = mGemManager->GetSlotIntData(i2, is_white);
                String str170(1, unk_0x65 + 'A');
                wcc->AddTextInstance(tfc8, str170, i1 == 0);
                mWidgets.insert(wcc);
            }
        }

        if (mGameGem->IsRealGuitar() && mGameGem->GetFret(i2) != -1) {
            Symbol s1d0;
            if (mGemManager->GetWidgetName(s1d0, i2, fret_num)) {
                TrackWidget *w1d4 = mGemManager->GetWidgetByName(s1d0);
                Transform tff8;
                mGemManager->mTrackDir->MakeWidgetXfm(i2, mGameGem->mMs / 1000.0f, tff8);
                float offset = mGemManager->mTrackDir->GetFretPosOffset(mFretPos);
                if (cfg->IsLefty())
                    offset = -offset;
                static DataNode &rg_widget_scale = DataVariable("rg_widget_scale");
                float scaleFloat = rg_widget_scale.Float();
                if (scaleFloat > 0)
                    offset *= scaleFloat;
                tff8.v.x += offset;
                if (scaleFloat > 0) {
                    w1d4->SetScale(scaleFloat);
                    Scale(
                        tff8.v,
                        Vector3(1.0f / scaleFloat, 1.0f, 1.0f / scaleFloat),
                        tff8.v
                    );
                }
                String str17c(RGFretNumberToString(mGameGem->GetFret(i2)));
                w1d4->AddTextInstance(tff8, str17c, false);
                mWidgets.insert(w1d4);
            }
        }
    }
}

void Gem::AddStrumInstance(Symbol s1, Symbol s2) {
    if (mGemManager == NULL || mGemManager->mTrackConfig == 0)
        return;
    int lowString = mGameGem->GetLowestString();
    int highString = mGameGem->GetHighestString();
    MILO_ASSERT(lowString != -1, 572);
    MILO_ASSERT(highString != -1, 573);
    Symbol t0;
    if (!mGemManager->GetChordWidgetName(s1, s2, t0)) {
        MILO_WARN("could not find widget for %s for %s chord gem in %s", t0, s1, s2);
        return;
    }
}

void Gem::AddHopoTails(Symbol s1) {
    if (mGemManager != 0 && mGemManager->mTrackDir != 0) {
        bool isRealGuitar = mGemManager->mTrackConfig->IsRealGuitarTrack();

        if (isRealGuitar && mHit) {
            if (s1.mStr == "miss") {
            }

            Symbol s2("");
            mGemManager->GetWidgetName(s2, 0, 0);
            TrackWidget *widget = mGemManager->GetWidgetByName(s2);

            int maxSlots = mGemManager->GetMaxSlots();

            for (int i = 0; i < maxSlots; i++) {
                if (mSlots & (1 << i) != 0) {
                    AddWidgetInstanceImpl(widget, i);
                }
            }
        }
    }
}

void Gem::Miss() {}

void Gem::Hit() {
    for (int i = 0; i < mTails.size(); i++)
        mTails[i]->Hit();
    mBeard = false;
    RemoveAllInstances();
    mHit = true;
}

void Gem::Release() {
    for (int i = 0; i < mTails.size(); i++)
        mTails[i]->Release();
    mReleased = true;
}

void Gem::KillDuration() {
    for (int i = 0; i < mTails.size(); i++)
        mTails[i]->Done();
}

void Gem::Reset() {
    mHit = false;
    mMissed = false;
    mReleased = false;
    mTailStart = 0.0;
    mBeard = false;
    mBeardTick = -1;
}

float Gem::GetStart() const {
    float val;

    if (!mBeard) {
        val = mStart;
    } else {
        val = TickToSeconds(mBeardTick);
    }

    return val;
}

void Gem::SetFretPos(int i) { mFretPos = i; }

void Gem::GetChordFretLabelInfo(String &s, int &i) const {
    s = RGFretNumberToString(mFirstFret);
    i = mFirstFretString;
}
