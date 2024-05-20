#ifndef UI_PANELDIR_H
#define UI_PANELDIR_H
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

    UIComponent* mFocusComponent;
    class UIPanel* mPanel;
    ObjPtr<RndCam, ObjectDir> mCam;
    std::list<int> mTriggers;
    std::list<int> mComponents;
    bool mCanEndWorld;
    bool mUseSpecifiedCam;
    std::vector<int> mBackPanels;
    std::vector<int> mBackFilenames;
    std::vector<int> mFrontPanels;
    std::vector<int> mFrontFilenames;
    bool mShowEditModePanels;
    bool mShowFocusComponent;
};

#endif