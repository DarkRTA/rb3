#include "game/GameMicManager.h"
#include "GameMic.h"
#include "GameMicManager.h"
#include "game/GameMode.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "synth/FxSend.h"
#include "synth/FxSendDelay.h"
#include "synth/FxSendSynapse.h"
#include "synth/MicClientMapper.h"
#include "synth/MicManagerInterface.h"
#include "synth/Synth.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include <cstddef>

GameMicManager *TheGameMicManager;
MicClientID sNullMicClientID(-1, -1);

void GameMicManager::Init() {
    MILO_ASSERT(TheGameMicManager == NULL, 0x28);
    TheGameMicManager = new GameMicManager();
    TheDebug.AddExitCallback(GameMicManager::Terminate);
    MILO_ASSERT(TheSynth, 0x30);
    MicClientMapper *pMapper = TheSynth->GetMicClientMapper();
    TheGameMicManager->LoadMicFx();
    MILO_ASSERT(pMapper, 0x37);
    pMapper->SetMicManager(TheGameMicManager);
}

void GameMicManager::Terminate() {
    MILO_ASSERT(TheGameMicManager != NULL, 0x42);
    RELEASE(TheGameMicManager);
}

static DataNode SetProximity(DataArray *a) {
    TheGameMicManager->SetSynapseProximity(a->Float(1));
    return 0;
}

static DataNode SetSlackyness(DataArray *a) {
    TheGameMicManager->SetSynapseSlackyness(a->Float(1));
    return 0;
}

static DataNode SetFocus(DataArray *a) {
    TheGameMicManager->SetSynapseFocus(a->Float(1));
    return 0;
}

static DataNode SetAmount(DataArray *a) {
    TheGameMicManager->SetSynapseAmount(a->Float(1));
    return 0;
}

static DataNode SetEnable(DataArray *a) {
    TheGameMicManager->unk2f = a->Float(1) > 0.5;
    return 0;
}

GameMicManager::GameMicManager()
    : unk2c(0), unk2d(0), unk2e(0), unk2f(1), mSynapseProximity(-1), mSynapseFocus(-1),
      mMicCount(0), mPlayback(0) {
    DataRegisterFunc("synapse_set_proximity", SetProximity);
    DataRegisterFunc("synapse_set_amount", SetAmount);
    DataRegisterFunc("synapse_set_enable", SetEnable);
    DataRegisterFunc("synapse_set_focus", SetFocus);
    DataRegisterFunc("synapse_set_slackyness", SetSlackyness);
    mMics.resize(4);
}

GameMicManager::~GameMicManager() {}

void GameMicManager::HandleMicsChanged() {
    MicClientMapper *pMapper = TheSynth->GetMicClientMapper();
    MILO_ASSERT(pMapper, 0x92);
    std::vector<int> mics;
    pMapper->GetAllConnectedMics(mics);
    for (int i = 0; i < mMics.size(); i++) {
        if (std::find(mics.begin(), mics.end(), i) == mics.end()) {
            DeleteMic(i);
        } else
            CreateMic(i);
    }
    static GameMicsChangedMsg msg;
    MsgSource::Handle(msg, false);
}

bool GameMicManager::HasMic(const MicClientID &id) const {
    MILO_ASSERT(TheSynth, 0xB4);
    int nMicID = TheSynth->GetMicClientMapper()->GetMicIDForClientID(id);
    if (nMicID == -1) {
        return TheGameMode && TheGameMode->InMode(frame_rate);
    } else {
        MILO_ASSERT(mMics[nMicID] != NULL, 0xC3);
        return true;
    }
}

GameMic *GameMicManager::GetMic(const MicClientID &id) {
    MILO_ASSERT(TheSynth, 0xCA);
    int nMicID = TheSynth->GetMicClientMapper()->GetMicIDForClientID(id);
    if (nMicID == -1) {
        if (TheGameMode && TheGameMode->InMode(frame_rate)) {
            if (mFakeMics.empty()) {
                InitFakeMics();
            }
            return mFakeMics[id.unk0];
        } else
            return nullptr;
    } else
        return mMics[nMicID];
}

float GameMicManager::GetEnergyForMic(const MicClientID &id) {
    GameMic *mic = GetMic(id);
    if (mic) {
        mic->Update();
        return mic->unk28;
    } else
        return 0;
}

void GameMicManager::SetPlayback(bool b1) {
    if (mPlayback != b1) {
        mPlayback = b1;
        for (int i = 0; i < mMics.size(); i++) {
            if (mMics[i]) {
                ApplyPlayback(b1, mMics[i]);
            }
        }
    }
}

void GameMicManager::ApplyPlayback(bool b1, GameMic *iMic) const {
    MILO_ASSERT(iMic, 0x119);
    Mic *pMic = iMic->GetMyMic();
    MILO_ASSERT(pMic, 0x11E);
    if (b1) {
        pMic->StartPlayback();
    } else
        pMic->StopPlayback();
}

void GameMicManager::DeleteMic(int idx) {
    if (mMics[idx]) {
        RELEASE(mMics[idx]);
        mMicCount--;
    }
}

void GameMicManager::CreateMic(int idx) {
    if (!mMics[idx]) {
        GameMic *mic = new GameMic(idx);
        mMics[idx] = mic;
        mMicCount++;
        HookUpFxForMicId(mic);
        ApplyPlayback(mPlayback, mic);
    }
}

void GameMicManager::LoadMicFx() {
    unk20.LoadFile(FilePath(".", "sfx/mic_fx.milo"), true, false, kLoadFront, false);
}

int GameMicManager::GetMicCount() const {
    if (TheGameMode && TheGameMode->InMode(frame_rate)) {
        return 4;
    } else
        return mMicCount;
}

void GameMicManager::HookUpFxForMicId(GameMic *gmic) {
    if (!unk2c) {
        unk20.PostLoad(nullptr);
        unk2c = true;
    }
    Mic *mic = TheSynth->GetMic(gmic->mMicID);
    if (mic) {
        FxSend *send = unk20->Find<FxSend>("mic.send", false);
        mic->SetFxSend(send);
    }
}

void GameMicManager::SetOverdriveEffectEnable(bool b1) {
    if (unk20) {
        FxSend *send = unk20->Find<FxSend>("delay.send", true);
        send->SetProperty(wet_gain, b1 ? 0.0f : -96.0f);
    }
}

void GameMicManager::Poll(float f1) {
    if (unk20) {
        FxSendDelay *send = unk20->Find<FxSendDelay>("delay.send", true);
        if (send) {
            DataNode *syncProp = send->Property(tempo_sync, false);
            if (syncProp && syncProp->Int()) {
                send->SetProperty(tempo, f1);
            }
        }
    }
}

void GameMicManager::SetPitchCorrectionTarget(
    bool, bool, float, float, float, float, float
) {}

void GameMicManager::SetSynapseProximity(float f1) {
    mSynapseProximity = f1;
    FxSendSynapse *send = unk20->Find<FxSendSynapse>("synapse.send", true);
    send->SetProximityEffect(f1);
}

void GameMicManager::SetSynapseSlackyness(float f1) {
    FxSendSynapse *send = unk20->Find<FxSendSynapse>("synapse.send", true);
    float mult = f1 * 40.0f;
    send->SetAttackSmoothing(mult + 15.0f);
    send->SetReleaseSmoothing(mult + 40.0f);
}

void GameMicManager::SetSynapseAmount(float f1) {
    FxSendSynapse *send = unk20->Find<FxSendSynapse>("synapse.send", true);
    send->SetAmount(f1);
}

void GameMicManager::SetSynapseFocus(float f1) {
    mSynapseFocus = f1;
    FxSendSynapse *send = unk20->Find<FxSendSynapse>("synapse.send", true);
    send->SetProximityFocus(f1);
}

void GameMicManager::InitFakeMics() {
    if (mFakeMics.empty()) {
        mFakeMics.resize(4);
        for (int i = 0; i < 4; i++) {
            mFakeMics[i] = new GameMic(-1);
        }
    }
}