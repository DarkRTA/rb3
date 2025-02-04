#include "bandtrack/GemManager.h"
#include "bandobj/ArpeggioShape.h"
#include "bandtrack/NowBar.h"
#include "bandtrack/Track.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/RGUtl.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/SongDB.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "game/TrainerPanel.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
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
      unkb8(0), mNowBar(0), unkc0(0), mInCoda(0), unkc4(0),
      unkc8(dir->SecondsToY(dir->TopSeconds())),
      unkcc(dir->SecondsToY(dir->BottomSeconds())), unkf8(0), unkfc(0), unk100(0),
      unk104(0), unk108(0), unk10c(0), unk118(0), unk12c(0), unk130(-1), unk134(960) {
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
        BandSongMetadata *metadata = (BandSongMetadata *)TheSongMgr->Data(
            TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
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