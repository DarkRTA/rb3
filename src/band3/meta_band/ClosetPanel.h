#pragma once
#include "game/BandUser.h"
#include "meta/DeJitterPanel.h"
#include "meta_band/ClosetMgr.h"
#include "rndobj/TexRenderer.h"
#include "world/CameraManager.h"
#include "world/CameraShot.h"

class ClosetPanel : public DeJitterPanel {
public:
    ClosetPanel();
    OBJ_CLASSNAME(ClosetPanel);
    OBJ_SET_TYPE(ClosetPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~ClosetPanel() {}
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();

    CamShot *GetCurrentShot();
    void CycleCamera();
    void GotoArtMakerShot();
    void LeaveArtMakerShot();
    void TakePortrait();
    void GotoShot(Symbol);
    void SetPortraitRenderer(RndTexRenderer *);
    BandUser *GetUser() const { return mClosetMgr->GetUser(); }
    NEW_OBJ(ClosetPanel);
    static void Init() { REGISTER_OBJ_FACTORY(ClosetPanel); }

    ClosetMgr *mClosetMgr; // 0x88
    CameraManager *mCameraManager; // 0x8c
    RndTexRenderer *mPortraitRenderer; // 0x90
    int mPortraitState; // 0x94
};
