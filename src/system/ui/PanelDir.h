#ifndef UI_PANELDIR_H
#define UI_PANELDIR_H
#include "obj/Object.h"
#include "rndobj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/Msg.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include <list>
#include <vector>

class UIComponent;
class RndCam;
class UITrigger;

class PanelDir : public RndDir {
public:
    enum RequestFocus {
        kNoFocus = 0,
        kMaybeFocus = 1,
        kAlwaysFocus = 2,
    };

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

    virtual RndCam* CamOverride();
    virtual bool Entering() const;
    virtual bool Exiting() const;
    virtual UIComponent* FocusComponent();
    virtual UIComponent* FindComponent(const char*);
    virtual void SetFocusComponent(UIComponent*, Symbol);
    void SendTransition(const Message&, Symbol, Symbol);
    void AddComponent(UIComponent*);
    void UpdateFocusComponentState();
    void SetShowFocusComponent(bool);
    void SyncEditModePanels();
    void EnableComponent(UIComponent*, RequestFocus);
    void DisableComponent(UIComponent*, JoypadAction);
    bool PanelNav(JoypadAction, JoypadButton, Symbol);
    UIComponent* GetFirstFocusableComponent();
    bool PropSyncEditModePanels(std::vector<FilePath>&, DataNode&, DataArray*, int, PropOp);

    DataNode GetFocusableComponentList();
    DataNode OnEnableComponent(const DataArray*);
    DataNode OnDisableComponent(const DataArray*);
    DataNode OnMsg(const ButtonDownMsg&);

    DECLARE_REVS
    static bool sAlwaysNeedFocus;

    UIComponent* mFocusComponent; // 0x18c
    class UIPanel* mOwnerPanel; // 0x190
    ObjPtr<RndCam, ObjectDir> mCam; // 0x194
    std::list<UITrigger*> mTriggers; // 0x1a0
    std::list<UIComponent*> mComponents; // 0x1a8
    bool mCanEndWorld; // 0x1b0
    bool mUseSpecifiedCam; // 0x1b1
    std::vector<PanelDir*> mBackPanels; // 0x1b4
    std::vector<FilePath> mBackFilenames; // 0x1bc
    std::vector<PanelDir*> mFrontPanels; // 0x1c4
    std::vector<FilePath> mFrontFilenames; // 0x1cc
    bool mShowEditModePanels; // 0x1d4
    bool mShowFocusComponent; // 0x1d5
};

#endif