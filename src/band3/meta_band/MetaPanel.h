#pragma once
#include "meta/HAQManager.h"
#include "meta/MetaMusicManager.h"
#include "meta/SongPreview.h"
#include "meta_band/Campaign.h"
#include "meta_band/NameGenerator.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "synth/MetaMusic.h"
#include "tour/Tour.h"
#include "ui/UIPanel.h"

class MetaPanel : public UIPanel {
public:
    MetaPanel();
    OBJ_CLASSNAME(MetaPanel);
    OBJ_SET_TYPE(MetaPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~MetaPanel();

    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();

    static bool sUnlockAll;
    static bool sIsPlaytest;
    static bool sLaunchedGoalMsgsOnly;
    static void Init();
    NEW_OBJ(MetaPanel);
    static void Register() { REGISTER_OBJ_FACTORY(MetaPanel); }
    static DataNode ToggleUnlockAll(DataArray *);
    static DataNode ToggleIsPlaytest(DataArray *);
    static DataNode ToggleLaunchedGoalMsgsOnly(DataArray *);

    Tour *mTour; // 0x38
    Campaign *mCampaign; // 0x3c
    NameGenerator *mNameGenerator; // 0x40
    int unk44; // 0x44
    MetaMusicManager *mMetaMusicMgr; // 0x48
    HAQManager *mHAQMgr; // 0x4c
    std::vector<int> mRecentIndices; // 0x50
    int unk58;
    MetaMusic *mMusic; // 0x5c
    SongPreview mSongPreview; // 0x60
    bool unkd4;
};