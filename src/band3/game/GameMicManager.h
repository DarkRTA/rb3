#pragma once
#include "game/GameMic.h"
#include "obj/Msg.h"
#include "obj/Dir.h"
#include "synth/MicManagerInterface.h"

class GameMicManager : public MicManagerInterface, public MsgSource {
public:
    GameMicManager();
    virtual ~GameMicManager();
    virtual void HandleMicsChanged();
    virtual void SetPlayback(bool);
    virtual float GetEnergyForMic(const MicClientID &);

    void LoadMicFx();
    void SetSynapseProximity(float);
    void SetSynapseSlackyness(float);
    void SetSynapseFocus(float);
    void SetSynapseAmount(float);
    void DeleteMic(int);
    void CreateMic(int);
    bool HasMic(const MicClientID &) const;
    GameMic *GetMic(const MicClientID &);
    void InitFakeMics();
    void ApplyPlayback(bool, GameMic *) const;
    void HookUpFxForMicId(GameMic *);
    int GetMicCount() const;
    void SetOverdriveEffectEnable(bool);
    void Poll(float);
    void SetPitchCorrectionTarget(bool, bool, float, float, float, float, float);

    static void Init();
    static void Terminate();

    ObjDirPtr<ObjectDir> unk20; // 0x20
    bool unk2c;
    bool unk2d;
    bool unk2e;
    bool unk2f;
    float mSynapseProximity; // 0x30
    float mSynapseFocus; // 0x34
    int mMicCount; // 0x38
    std::vector<GameMic *> mMics; // 0x3c
    std::vector<GameMic *> mFakeMics; // 0x44
    bool mPlayback; // 0x4c
};

extern GameMicManager *TheGameMicManager;