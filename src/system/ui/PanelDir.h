#ifndef UI_PANELDIR_H
#define UI_PANELDIR_H
#include "obj/Object.h"
#include "rndobj/Dir.h"
#include "obj/ObjPtr_p.h"
#include <list>
#include <vector>

class UIComponent;
class RndCam;

class PanelDir : public RndDir {
public:
    PanelDir();
    OBJ_CLASSNAME(PanelDir)
    OBJ_SET_TYPE(PanelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~PanelDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object*);
    virtual void DrawShowing();
    virtual void Enter();
    virtual void Exit();

    virtual int CamOverride(); // fix return type
    virtual bool Entering() const;
    virtual bool Exiting() const;
    virtual UIComponent* FocusComponent();
    virtual UIComponent* FindComponent(const char*);
    virtual void SetFocusComponent(UIComponent*, Symbol);

    void SyncEditModePanels();

    UIComponent* mFocusComponent;
    class UIPanel* mOwnerPanel;
    ObjPtr<RndCam, ObjectDir> mCam;
    std::list<void*> mTriggers;
    std::list<void*> mComponents;
    bool mCanEndWorld; // 0x1b0
    bool mUseSpecifiedCam; // 0x1b1
    std::vector<PanelDir*> mBackPanels; // 0x1b4
    std::vector<FilePath> mBackFilenames; // 0x1bc
    std::vector<PanelDir*> mFrontPanels; // 0x1c4
    std::vector<FilePath> mFrontFilenames; // 0x1cc
    bool mShowEditModePanels; // 0x1d4
    bool mShowFocusComponent; // 0x1d5

    DECLARE_REVS
};

#endif