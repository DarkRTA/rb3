#include "bandtrack/GemManager.h"
#include "bandobj/ArpeggioShape.h"
#include "bandtrack/NowBar.h"
#include "bandtrack/Track.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/RGUtl.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "game/TrainerPanel.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Group.h"
#include "rndobj/Trans.h"
#include "track/TrackWidget.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

int sBeardThreshold = 480;

int GetBeardThreshold() { return sBeardThreshold; }

DataNode SetKeyGlow(DataArray *arr) {
    sBeardThreshold = arr->Int(1);
    return 0;
}

GemManager::GemManager(const TrackConfig &cfg, TrackDir *dir)
    : mTrackDir(dir), mTrackConfig(cfg), mTemplate(cfg),
      mConfig(SystemConfig("track_graphics")), mGemData(0), unk14(0), mBegin(0), mEnd(0),
      unkb8(0), mNowBar(0), mBonusGems(0), mInCoda(0), unkc4(0),
      unkc8(dir->SecondsToY(dir->TopSeconds())),
      unkcc(dir->SecondsToY(dir->BottomSeconds())), mTailsGrp(0), unkfc(0), unk100(0),
      unk104(0), mEnabledSlots(0), unk10c(0), unk118(0), unk12c(0), unk130(-1),
      unk134(960) {
    mNowBar = new NowBar(mTrackDir, mTrackConfig);
    mTemplate.Init(mTrackDir->Find<ObjectDir>("gem_tail", true));
    static bool firstPass = true;
    if (firstPass) {
        sBeardThreshold =
            SystemConfig("track_graphics")->FindInt("key_glow_threshold_ticks");
        firstPass = false;
    }
    unk134 = SystemConfig("track_graphics")->FindInt("rg_run_space_ticks");
    SetupGems(0);
    UpdateLeftyFlip(false);
    DataRegisterFunc("set_key_glow", SetKeyGlow);
    unk12c = mTrackDir->Find<RndDir>("chord_shape_outline", true)->mLocalXfm.v.y + 0.01f;
    unkd8.reserve(10);
}

GemManager::~GemManager() {
    RELEASE(mNowBar);
    ClearArpeggios();
    mGems.clear();
}

void GemManager::InitRGTuning(BandUser *bandUser) {
    MILO_ASSERT(bandUser, 0xAE);
    bool isRG = bandUser->GetTrack()->GetType() == real_guitar;
    bool isRB = bandUser->GetTrack()->GetType() == real_bass;
    if (isRG || isRB) {
        BandSongMetadata *metadata = (BandSongMetadata *)TheSongMgr.Data(
            TheSongMgr.GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
        );
        std::vector<int> vec18;
        if (isRG) {
            vec18.reserve(6);
            for (int i = 0; i < 6; i++) {
                vec18.push_back(metadata->RealGuitarTuning(i));
            }
        } else {
            vec18.reserve(4);
            for (int i = 0; i < 4; i++) {
                vec18.push_back(metadata->RealBassTuning(i));
            }
        }
        RGSetTuning(vec18);
    }
}

void GemManager::DrawTrackMasks(int i1, int i2) {
    for (int i = i2 != -1 ? i2 : i1; i <= i1; i += 0xf0) {
        if (i > unk10c) {
            int i174 = 0;
            int i3 = i;
            if (TheGame->InTrainer()) {
                i3 = GetLoopTick(i, i174);
            }
            i3 = TheSongDB->GetCommonPhraseID(mTrackConfig.TrackNum(), i3);
            Extent ext170(-1, -1);
            if (i3 != -1 && TheSongDB->IsUnisonPhrase(i3)) {
                if (TheSongDB->GetCommonPhraseExtent(
                        mTrackConfig.TrackNum(), i3, ext170
                    )) {
                    Symbol nameSym = mGemData->FindArray(unison, false)->Sym(1);
                    TrackWidget *w = GetWidgetByName(nameSym);
                    Transform tf98;
                    tf98.Reset();
                    tf98.v.y = mTrackDir->SecondsToY(TickToSeconds(ext170.unk0 + i174));
                    w->AddInstance(
                        tf98, TickToSeconds(ext170.unk4) - TickToSeconds(ext170.unk0)
                    );
                    unk10c = ext170.unk4 + i174;
                }
            }
        }
    }

    for (; unk118 < mArpeggioPhrases.size(); unk118++) {
        ArpeggioPhrase *curPhrase = &mArpeggioPhrases[unk118];
        if (curPhrase->unk4 >= i2)
            continue;
        if (curPhrase->unk0 > i1)
            break;
        Gem &curGem = mGems[curPhrase->unk8];
        ArpeggioShapePool *pool = mTrackDir->GetArpeggioShapePool();
        ArpeggioShape *poolShape = pool->GetArpeggioShape();
        bool lefty = mTrackConfig.IsLefty();
        float f11 = mTrackDir->SecondsToY(TickToSeconds(curPhrase->unk0));
        if (curPhrase->unk10) {
            poolShape->ShowChordShape(false);
        } else {
            Symbol nameSym = mGemData->FindArray(arpeggio, false)->Sym(1);
            TrackWidget *w5 = GetWidgetByName(nameSym);
            Transform tfc8;
            tfc8.Reset();
            tfc8.v.y = f11;
            int i10 = curPhrase->unk4;
            if (TheTrainerPanel && TheGame->InTrainer()) {
                i10 = Min(
                    curPhrase->unk4,
                    (curPhrase->unk0
                     - (GetLoopTick(curPhrase->unk0)
                        - TheTrainerPanel->GetCurrentStartTick()))
                        + TheTrainerPanel->GetLoopTicks(TheTrainerPanel->GetCurrSection())
                );
                curPhrase->unk4 = i10;
            }
            w5->AddInstance(tfc8, TickToSeconds(i10) - TickToSeconds(curPhrase->unk0));
            RndMesh *mesh = mTrackDir->GetChordMesh(curGem.unk_0x48, lefty);
            poolShape->SetChordShape(mesh);
            poolShape->ShowChordShape(true);
            String str168;
            int i180 = -1;
            curGem.GetChordFretLabelInfo(str168, i180);
            Transform tff8;
            mTrackDir->MakeSlotXfm(i180, tff8);
            Symbol s184;
            if (GetChordWidgetName(normal, chord_fret, s184)) {
                TrackWidget *w10 = GetWidgetByName(s184);
                if (w10)
                    w10->ApplyOffsets(tff8);
            }
            poolShape->SetFretNumber(str168, tff8.v);
        }
        poolShape->SetYPos(f11);
        poolShape->SetChordLabel(
            curGem.mChordLabel, mTrackDir->GetCurrentChordLabelPosOffset(), lefty
        );
        poolShape->HookupToParentGroup();
        curPhrase->mShape = poolShape;
        mActiveArpeggios.push_back(curPhrase);
    }
}

void GemManager::ClearArpeggios() {
    ArpeggioShapePool *pool = mTrackDir->GetArpeggioShapePool();
    while (!mActiveArpeggios.empty()) {
        pool->ReleaseArpeggioShape(mActiveArpeggios.back()->mShape);
        mActiveArpeggios.pop_back();
    }
    while (!mExpiredArpeggios.empty()) {
        pool->ReleaseArpeggioShape(mExpiredArpeggios.back()->mShape);
        mExpiredArpeggios.pop_back();
    }
}

void GemManager::ResetArpeggios(float f1) {
    ClearArpeggios();
    unk118 = 0;
    int tick = MsToTickInt(f1);
    for (; unk118 < mArpeggioPhrases.size() && mArpeggioPhrases[unk118].unk4 < tick;
         unk118++)
        ;
}

void GemManager::UpdateArpeggios(float f1, bool b2) {
    float ms = mTrackDir->YToSeconds(unk12c) * 1000.0f + f1;
    int i1 = MsToTickInt(ms);
    while (!mActiveArpeggios.empty()) {
        ArpeggioPhrase *currentArpeggio = mActiveArpeggios.front();
        MILO_ASSERT(currentArpeggio->mShape, 0x185);
        if (currentArpeggio->unk4 < i1) {
            currentArpeggio->mShape->FadeOutChordShape();
            mExpiredArpeggios.push_back(currentArpeggio);
            mActiveArpeggios.erase(mActiveArpeggios.begin());
        } else {
            if (!b2 || !currentArpeggio->unk10) {
                if (currentArpeggio->unk0 > i1) {
                    ms = TickToMs(currentArpeggio->unk0);
                }
                currentArpeggio->mShape->SetYPos(mTrackDir->SecondsToY(ms / 1000.0f));
            }
            break;
        }
    }
    ms = mTrackDir->SecondsToY((f1 / 1000.0f + mTrackDir->BottomSeconds()) - 0.5f);
    while (!mExpiredArpeggios.empty() && mExpiredArpeggios.front()->mShape->GetYPos() < ms
    ) {
        MILO_ASSERT(mExpiredArpeggios.front()->mShape, 0x1A8);
        mTrackDir->GetArpeggioShapePool()->ReleaseArpeggioShape(
            mExpiredArpeggios.front()->mShape
        );
        mExpiredArpeggios.erase(mExpiredArpeggios.begin());
    }
}

void GemManager::ClearTrackMasks() {
    if (mGemData) {
        DataArray *arpArr = mGemData->FindArray(arpeggio, false);
        if (arpArr) {
            Symbol name = arpArr->Sym(1);
            GetWidgetByName(name)->Clear();
        }
        DataArray *unisonArr = mGemData->FindArray(unison, false);
        if (unisonArr) {
            Symbol name = unisonArr->Sym(1);
            GetWidgetByName(name)->Clear();
        }
        unk10c = 0;
    }
}

void GemManager::SetupRealGuitarFretPos() {
    const BandUser *bandUser = mTrackConfig.GetBandUser();
    bool isRG = bandUser->GetTrack()->GetType() == real_guitar;
    bool isRB = bandUser->GetTrack()->GetType() == real_bass;
    if (isRG || isRB) {
        std::vector<GameGem> gameGems;
        int i2 = -1;
        int i38 = 0;
        int i3c = -1;
        for (int i = 0; i < mGems.size(); i++) {
            const GameGem &curGameGem = mGems[i].GetGameGem();
            if (i3c != -1 && curGameGem.GetTick() > i3c) {
                ProcessRealGuitarRun(gameGems, i38);
                i2 = curGameGem.GetLowestString();
                i3c = -1;
                if (!curGameGem.IsRealGuitarChord()) {
                    gameGems.push_back(curGameGem);
                }
            } else if (curGameGem.IsRealGuitarChord()) {
                ProcessRealGuitarRun(gameGems, i38);
                i2 = -1;
                i38++;
            } else if (curGameGem.IsMuted()) {
                ProcessRealGuitarRun(gameGems, i38);
                i2 = curGameGem.GetLowestString();
                i38++;
            } else if (i2 != (int)curGameGem.GetLowestString()) {
                ProcessRealGuitarRun(gameGems, i38);
                i2 = curGameGem.GetLowestString();
                gameGems.push_back(curGameGem);
            } else {
                if (!gameGems.empty()) {
                    GameGem &last = gameGems.back();
                    if (curGameGem.GetTick() - last.GetTick() > unk134) {
                        ProcessRealGuitarRun(gameGems, i38);
                        i2 = curGameGem.GetLowestString();
                        gameGems.push_back(curGameGem);
                        continue;
                    }
                }
                if (i3c == -1) {
                    if (TrillStartsAt(mTrackConfig.TrackNum(), curGameGem, i3c)) {
                        ProcessRealGuitarRun(gameGems, i38);
                        i2 = curGameGem.GetLowestString();
                        gameGems.push_back(curGameGem);
                        continue;
                    }
                }
                gameGems.push_back(curGameGem);
            }
        }
        ProcessRealGuitarRun(gameGems, i38);
    }
}

void GemManager::ProcessRealGuitarRun(std::vector<GameGem> &gems, int &iref) {
    if (!gems.empty()) {
        if (gems.size() == 1) {
            mGems[iref].SetFretPos(2);
        } else {
            int i3 = mGems[iref].GetGameGem().GetLowestString();
            unsigned int u10 = 0;
            for (int i = 0; i < gems.size(); i++) {
                const GameGem &curGem = mGems[iref + i].GetGameGem();
                u10 |= 1 << curGem.GetFret(i3);
            }
            int i2 = -1;
            int i9 = 0;
            int i5c = 100000;
            int i60 = -1;
            for (int i = 0; i < 0x16; i++) {
                if (u10 & 1 << i) {
                    i5c = std::min(i5c, i);
                    i60 = std::max(i60, i);
                    i9++;
                }
            }
            if (i9 > 5) {
                i2 = mGems[iref].GetGameGem().GetFret(i3);
                if (i60 - i2 < 5) {
                    i9 = 4 - (i60 - i2);
                } else {
                    i9 = 2;
                    if (i2 - i5c < 5) {
                        i9 = i2 - i5c;
                    }
                    mGems[iref].SetFretPos(i9);
                    for (int i = 1; i < gems.size(); i++) {
                        int i1 = mGems[iref + i].GetGameGem().GetFret(i3);
                        if (i2 < i1) {
                            i9 = (i9 + 1) % 5;
                            i2 = i1;
                        } else if (i1 < i2) {
                            i9--;
                            i2 = i1;
                            if (i9 < 0) {
                                i9 = 4;
                            }
                        }
                        mGems[iref + i].SetFretPos(i9);
                    }
                }
            } else {
                if (i5c == i2) {
                    for (int i = 0; i < gems.size(); i++) {
                        mGems[iref + i].SetFretPos(2);
                    }
                } else {
                    i2 -= i5c;
                    for (int i = 0; i < gems.size(); i++) {
                        float gemfloat = mGems[iref + i].GetGameGem().GetFret(i3) - i5c;
                        int i68 = (5.0f / i2) * gemfloat;
                        i68 = std::min(i68, 4);
                        mGems[iref + i].SetFretPos(i68);
                    }
                }
            }
        }
        iref += gems.size();
        gems.clear();
    }
}

void GemManager::SetupRealGuitarImportantStrings() {
    const BandUser *bandUser = mTrackConfig.GetBandUser();
    bool isRG = bandUser->GetTrack()->GetType() == real_guitar;
    bool isRB = bandUser->GetTrack()->GetType() == real_bass;
    if (isRG || isRB) {
        for (int i = 1; i < mGems.size(); i++) {
        }
    }
}

void GemManager::EndRepeatedChordPhrase(
    int &repeatedChordStartTick, int &repeatedChordEndTick, int &i3
) {
    if (i3 != -1) {
        MILO_ASSERT(repeatedChordStartTick != -1, 0x56D);
        MILO_ASSERT(repeatedChordEndTick != -1, 0x56E);
        ArpeggioPhrase phrase(repeatedChordStartTick, repeatedChordEndTick, i3);
        phrase.unk10 = true;
        mArpeggioPhrases.push_back(phrase);
        i3 = -1;
        repeatedChordStartTick = -1;
        repeatedChordEndTick = -1;
    }
}

bool GemManager::RollStartsAt(int i1, const GameGem &gem, int &iref, unsigned int &uiref)
    const {
    int tick = GetLoopTick(gem.GetTick());
    bool ret;
    if (gem.IsRealGuitar()) {
        ret = TheSongDB->GetData()->RGRollStartsAt(i1, tick, iref);
    } else {
        ret = TheSongDB->GetData()->RollStartsAt(i1, tick, iref);
    }
    if (ret) {
        uiref = TheSongDB->GetData()->GetRollingSlotsAtTick(i1, tick);
    }
    iref += gem.GetTick() - tick;
    return ret;
}

bool GemManager::TrillStartsAt(int i1, const GameGem &gem, int &iref) const {
    int tick = GetLoopTick(gem.GetTick());
    bool ret;
    if (gem.IsRealGuitar()) {
        ret = TheSongDB->GetData()->RGTrillStartsAt(i1, tick, iref);
    } else {
        ret = TheSongDB->GetData()->TrillStartsAt(i1, tick, iref);
    }
    if (ret) {
        iref += gem.GetTick() - tick;
    }
    return ret;
}

void GemManager::SetGemsEnabled(float f) {
    unk14 = f;
    UpdateGemStates();
}

void GemManager::UpdateSlotPositions() {
    Transform tf48;
    for (int i = 0; i < GetMaxSlots(); i++) {
        RndDir *dir = mNowBar->FindSmasher(i)->Dir();
        RndTransformable *smashTrans =
            dir->Find<RndTransformable>("smasher.trans", false);
        if (smashTrans) {
            tf48 = smashTrans->WorldXfm();
        } else
            tf48 = dir->WorldXfm();
        mTrackDir->SetSlotXfm(i, tf48);
    }
    for (int i = mBegin; i < mEnd; i++) {
        mGems[i].UpdateTailPositions();
    }
}

int GemManager::GetNumGems() const { return mGems.size(); }
const Gem &GemManager::GetGem(int idx) const { return mGems[idx]; }

void GemManager::PollVisibleGems(float f1, float f2) {
    float div = f1 / 1000.0f;
    float top = mTrackDir->TopSeconds() + div;
    float bot = mTrackDir->BottomSeconds() + div;
    for (int i = mBegin; i < mEnd; i++) {
        mGems[i].Poll(f1, f2, unkc4, top, bot);
    }
}

void GemManager::AdvanceBegin() {
    mGems[mBegin].RemoveRep();
    mBegin++;
}

void GemManager::AdvanceEnd() {
    Gem &lastGem = mGems[mEnd];
    Symbol gemType = GetTypeForGem(mEnd);
    if (!mTailsGrp) {
        if (mTrackConfig.IsKeyboardTrack()) {
            mTailsGrp = mTrackDir->Find<RndGroup>("key_shift_tails.grp", true);
        } else
            mTailsGrp = mTrackDir->Find<RndGroup>("tails.grp", true);
    }
    unsigned int slots = lastGem.Slots();
    lastGem.AddRep(mTemplate, mTailsGrp, gemType, mTrackConfig, true);
    mEnd++;
    if (mTrackConfig.IsKeyboardTrack()) {
        int tick = lastGem.GetGameGem().GetTick();
        for (; mEnd < mGems.size() && tick == mGems[mEnd].GetGameGem().GetTick();
             mEnd++) {
            Symbol curGemType = GetTypeForGem(mEnd);
            Gem &curGem = mGems[mEnd];
            slots |= curGem.Slots();
            curGem.AddRep(mTemplate, mTailsGrp, curGemType, mTrackConfig, true);
        }
        AddChordBracket(gemType, slots, lastGem.GetGameGem().GetMs());
    }
}

void GemManager::RememberChordWidget(TrackWidget *w) {
    for (int i = 0; i < unkd8.size(); i++) {
        if (unkd8[i] == w)
            return;
    }
    unkd8.push_back(w);
}

void GemManager::AddWidgetInstanceImpl(TrackWidget *w, int ui, float f) {
    Transform tf58;
    mTrackDir->MakeWidgetXfm(ui, f / 1000.0f, tf58);
    w->AddInstance(tf58, 0);
}

void GemManager::ReleaseSlot(int gem_id, int slot) {
    MILO_ASSERT(gem_id < mGems.size(), 0x7C4);
    mGems[gem_id].ReleaseSlot(slot);
    mNowBar->StopBurning(1 << slot);
}

void GemManager::ReleaseHitGems() {
    FOREACH (it, mHitGems) {
        Gem &gem = mGems[it->unk4];
        if (gem.CompareBounds() && !gem.Released()) {
            gem.KillDuration();
            gem.Release();
        }
        mNowBar->StopBurning(gem.Slots());
    }
}

void GemManager::PruneHitGems(float f1) {
    while (!mHitGems.empty()) {
        if (mGems[mHitGems.front().unk4].OnScreen(f1))
            break;
        else
            mHitGems.pop_front();
    }
}

void GemManager::Hit(float f1, int i2, int i3) {
    if (!mTrackConfig.AllowsOverlappingGems()) {
        ReleaseHitGems();
    }
    mGems[i2].Hit();
    mHitGems.push_back(HitGem(f1, i2, mGems[i2].Slots()));
    if (mTrackConfig.IsKeyboardTrack()) {
        CheckRemoveChordBracket(i2);
    }
    bool b28 = false;
    if (IsSpotlightGem(i2, b28)) {
        i3 |= 2;
        if (!IsSpotlightGem(i2 + 1, b28)) {
            i3 |= 4;
        }
    }
    mNowBar->Hit(f1, i2, mInCoda, i3, mGems[i2].UseRGChordStyle());
}

void GemManager::Miss(float f1, int, int slot) {
    if (slot != -1) {
        MILO_ASSERT(slot >= 0 && slot < GetMaxSlots(), 0x81A);
        if (!mTrackConfig.AllowsOverlappingGems() && mNowBar->mCurrentGem != -1) {
            Released(f1, mNowBar->mCurrentGem);
        }
        mNowBar->Miss(f1, slot);
    }
}

void GemManager::Pass(int i1) { mGems[i1].Miss(); }
void GemManager::Ignore(int) {}

void GemManager::PartialHit(float f1, int i2, unsigned int ui, int i4) {
    mGems[i2].PartialHit(ui);
    bool b28 = false;
    if (IsSpotlightGem(i2, b28)) {
        i4 |= 2;
        if (!IsSpotlightGem(i2 + 1, b28)) {
            i4 |= 4;
        }
    }
    mNowBar->PartialHit(i2, ui, mInCoda, i4);
    mHitGems.push_back(HitGem(f1, i2, ui));
}

void GemManager::FillHit(int i1, int i2) { mNowBar->FillHit(i1, i2); }

void GemManager::Released(float f1, int i2) {
    Gem &gem = mGems[i2];
    if (gem.CompareBounds()) {
        if (!gem.GetGameGem().LeftHandSlide() && !gem.Released()) {
            gem.Release();

            float unk = gem.mEnd / 1000.0f;
            if (gem.mEnd > unk) {
                gem.mTailStart = unk - gem.GetStart();

            } else
                gem.KillDuration();
            mNowBar->StopBurning(gem.Slots());
        }
    }
}

void GemManager::SetSmasherGlowing(int i1, bool b2) {
    mNowBar->SetSmasherGlowing(i1, b2);
}

void GemManager::PopSmasher(int i1) { mNowBar->PopSmasher(i1); }

void GemManager::ResetSmashers(bool b1) { mNowBar->Reset(b1); }

void GemManager::Jump(float f1) {
    while (mBegin < mEnd)
        AdvanceBegin();
    mHitGems.clear();
    mMissedPhrases.clear();
    ClearTrackMasks();
    DrawTrackMasks(MsToTickInt(mTrackDir->TopSeconds() * 1000.0f + f1), MsToTickInt(f1));

    float f5 = mTrackDir->BottomSeconds();
    int i1 = -1;
    for (int i = 0; i < mEnd; i++) {
        if (mGems[i].GetStart() < f1 / 1000.0f + f5)
            continue;
        if (i1 < 0)
            i1 = i;
        mGems[i].Reset();
    }
    mBegin = i1;
    mEnd = i1;
    mBegin = Clamp(0, i1, i1);
    mEnd = Clamp(0, mEnd, mEnd);
    ResetArpeggios(f1);
    PlayerState state;
    PollHelper(f1, state);
}

void GemManager::SetBonusGems(bool gems, const PlayerState &state) {
    mBonusGems = gems;
    UpdateGemStates();
}

void GemManager::SetInCoda(bool coda) { mInCoda = coda; }

bool GemManager::OnMissPhrase(int i1) {
    bool ret = true;
    int tracknum = mTrackConfig.TrackNum();
    Extent ext18(0, 0);
    if (TheSongDB->GetCommonPhraseExtent(tracknum, i1, ext18)) {
        int i2 = MsToTickInt(TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f);
        if (!mMissedPhrases.empty()) {
            Extent &back = mMissedPhrases.back();
            ret = back.unk4 != ext18.unk4;
            if (ret) {
                mMissedPhrases.push_back(Extent(i2, ext18.unk4));
            } else if (i2 != back.unk0)
                return ret;
            UpdateGemStates();
        } else {
            mMissedPhrases.push_back(Extent(i2, ext18.unk4));
            UpdateGemStates();
        }
    }
    return ret;
}

bool GemManager::GetWidgetName(Symbol &sref, int i2, Symbol s3) {
    DataArray *arr = mGemData->FindArray(i2, false);
    if (!arr)
        return false;
    else {
        DataArray *symArr = arr->FindArray(s3, false);
        if (!symArr)
            return false;
        else {
            sref = symArr->Sym(1);
            return true;
        }
    }
}

bool GemManager::GetChordWidgetName(Symbol s1, Symbol s2, Symbol &sref) {
    DataArray *arr = mGemData->FindArray(s2, false);
    if (!arr)
        return false;
    else {
        DataArray *symArr = arr->FindArray(s1, false);
        if (!symArr)
            return false;
        else {
            sref = symArr->Sym(1);
            return true;
        }
    }
}

int GemManager::GetSlotIntData(int i1, Symbol s2) {
    DataArray *arr = mGemData->FindArray(i1, true);
    return arr->FindInt(s2);
}

int GemManager::GetSlotsForGem(int gem) {
    if (gem < 0 || gem >= mGems.size())
        return 0;
    else
        return mGems[gem].Slots();
}

void GemManager::EnableSlot(int slot) {
    if (!SlotEnabled(slot)) {
        mDisabledSlotsList.remove(slot);
    }
}

void GemManager::DisableSlot(int slot) {
    if (SlotEnabled(slot)) {
        mDisabledSlotsList.push_back(slot);
    }
}

bool GemManager::SlotEnabled(int slot) const {
    return std::find(mDisabledSlotsList.begin(), mDisabledSlotsList.end(), slot)
        == mDisabledSlotsList.end();
}

void GemManager::ClearGems(bool b) {
    for (int i = mBegin; i < mEnd; i++) {
        Gem &curGem = mGems[i];
        if (b || (!curGem.GetHit() || curGem.CompareBounds()) && !curGem.Released()) {
            curGem.RemoveAllInstances();
            curGem.RemoveRep();
        }
    }
}

void GemManager::ClearAllGems() {
    for (int i = 0; i < mGems.size(); i++) {
        Gem &curGem = mGems[i];
        curGem.Release();
        curGem.RemoveAllInstances();
        curGem.RemoveRep();
    }
}

void GemManager::HideGems() {
    for (int i = 0; i < mGems.size(); i++) {
        mGems[i].SetType(invisible);
    }
}

void GemManager::ClearGem(int idx) {
    Gem &curGem = mGems[idx];
    curGem.Release();
    curGem.RemoveAllInstances();
    curGem.RemoveRep();
}

bool GemManager::GetFill(int i1, FillExtent &ext) {
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    if (!player || !player->FillsEnabled(i1))
        return false;
    else {
        FillInfo *info = TheSongDB->GetData()->GetFillInfo(mTrackConfig.TrackNum());
        return !info ? false : info->FillAt(GetLoopTick(i1), ext, true);
    }
}

bool GemManager::IsInFill(int idx) {
    Player *player = mTrackConfig.GetBandUser()->GetPlayer();
    if (player->AreFillsForced())
        return true;
    else {
        FillExtent ext(0, 0, 0);
        return GetFill(idx, ext);
    }
}

bool GemManager::IsEndOfFill(int idx) {
    bool ret = false;
    FillExtent ext(0, 0, 0);
    if (GetFill(idx, ext) && ext.end == idx)
        ret = true;
    return ret;
}

void GemManager::ClearMissedPhrases() {
    mTrackConfig.GetBandUser()->GetPlayer()->mBand->mCommonPhraseCapturer->Reset();
    if (!mMissedPhrases.empty()) {
        mMissedPhrases.clear();
    }
}

TrackWidget *GemManager::GetWidgetByName(Symbol name) {
    if (mWidgets.find(name) == mWidgets.end()) {
        mWidgets[name] = mTrackDir->Find<TrackWidget>(name.mStr, true);
    }
    return mWidgets[name];
}

void GemManager::UpdateEnabledSlots() {
    mEnabledSlots = 0;
    for (int i = 0; i < mGems.size(); i++) {
        mEnabledSlots |= mGems[i].Slots();
    }
}

#pragma push
#pragma force_active on
inline int GemManager::GetMaxSlots() const { return mTrackConfig.GetMaxSlots(); }
#pragma pop
