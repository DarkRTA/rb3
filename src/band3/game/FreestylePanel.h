#pragma once
#include "beatmatch/BeatMatchController.h"
#include "game/BandUser.h"
#include "game/Metronome.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "beatmatch/BeatMatchControllerSink.h"

class FreestylePanel : public UIPanel, public BeatMatchControllerSink {
public:
    FreestylePanel();
    OBJ_CLASSNAME(FreestylePanel);
    OBJ_SET_TYPE(FreestylePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~FreestylePanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool Swing(int, bool, bool, bool, bool, GemHitFlags);

    void CreateController();
    void SetBpm(int);
    void EnableMetronome(bool);
    void SetMetronomeVolume(int, int);
    void SetFreestylePaused(bool);
    void HandleSolo();
    BandUser *GetFreestyleUser();

    DataNode OnMsg(const JoypadConnectionMsg &);

    BeatMatchController *mController; // 0x3c
    BandUser *mUser; // 0x40
    float unk44; // 0x44 - bpm?
    float unk48;
    int unk4c;
    Metronome *mMetronome; // 0x50
    bool unk54;
    float unk58;
    float unk5c;
    bool mFreestylePaused; // 0x60
};