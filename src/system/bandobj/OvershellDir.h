#pragma once
#include "ui/PanelDir.h"

class BandList;

class OvershellDir : public PanelDir {
public:
    OvershellDir();
    OBJ_CLASSNAME(OvershellDir)
    OBJ_SET_TYPE(OvershellDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~OvershellDir(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    void CacheLists();
    void ConcealAllLists(bool);
    void ViewChanged();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Symbol mSlotView; // 0x1d8
    bool mInTrackMode; // 0x1dc
    Symbol mControllerType; // 0x1e0
    bool mOnlineEnabled; // 0x1e4
    bool mIsLocal; // 0x1e5
    int mPadNum; // 0x1e8
    Symbol mPlatform; // 0x1ec
    std::vector<BandList*> mBandLists; // 0x1f0
    Symbol mDefaultOption; // 0x1f8
    int mDefaultOptionIndex; // 0x1fc
};