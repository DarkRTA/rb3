#ifndef UI_PANELDIR_H
#define UI_PANELDIR_H
#include "rndobj/Dir.h"

class PanelDir : public RndDir {
public:
    PanelDir();
    virtual ~PanelDir();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(PanelDir)
    OBJ_SET_TYPE(PanelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object*);

    int filler;
};

#endif

// class PanelDir : public RndDir {
//     // total size: 0x290
//     class UIComponent * mFocusComponent; // offset 0x1F4, size 0x4
//     class ObjPtr mCam; // offset 0x1F8, size 0xC
//     class list mTriggers; // offset 0x204, size 0x8
//     class list mComponents; // offset 0x20C, size 0x8
//     unsigned char mCanEndWorld; // offset 0x214, size 0x1
//     class vector mBackPanels; // offset 0x218, size 0xC
//     class vector mBackFilenames; // offset 0x224, size 0xC
//     class vector mFrontPanels; // offset 0x230, size 0xC
//     class vector mFrontFilenames; // offset 0x23C, size 0xC
//     unsigned char mShowEditModePanels; // offset 0x248, size 0x1
// };
