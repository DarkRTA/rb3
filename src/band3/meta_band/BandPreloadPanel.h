#pragma once
#include "meta/PreloadPanel.h"
#include "meta_band/LockStepMgr.h"

class BandPreloadPanel : public PreloadPanel {
public:
    BandPreloadPanel();
    OBJ_CLASSNAME(BandPreloadPanel);
    OBJ_SET_TYPE(BandPreloadPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandPreloadPanel();
    virtual void Load();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();

    DataNode OnMsg(const LockStepStartMsg &);
    DataNode OnMsg(const LockStepCompleteMsg &);

    bool mLockInProgress; // 0x69
    LockStepMgr *mPreloadLock; // 0x6c
};