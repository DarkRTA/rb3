#pragma once
#include "obj/Object.h"
#include "rndobj/Dir.h"
#include "rndobj/Cam.h"
#include "obj/ObjPtr_p.h"
#include "obj/Msg.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include <list>
#include <vector>

class UIComponent;
class UITrigger;

/** "Top-level UI Object,
 * contains UI components and an optional camera" */
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
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual ~PanelDir();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object *);
    virtual void DrawShowing();
    virtual void Enter();
    virtual void Exit();
    // every vfunc below this line is PanelDir's
    /** Get the current camera to use. */
    virtual RndCam *CamOverride();
    /** Are we in the process of entering a state? */
    virtual bool Entering() const;
    /** Are we in the process of exiting a state? */
    virtual bool Exiting() const;
    /** Get the current focused component. */
    virtual UIComponent *FocusComponent() { return mFocusComponent; }
    /** Find the UIComponent with the given name in this PanelDir. */
    virtual UIComponent *FindComponent(const char *name);
    /** Set this PanelDir's focus component.
     * @param [in] newComponent The new focus component.
     * @param [in] nav_type The component's navigation type.
     */
    virtual void SetFocusComponent(UIComponent *newComponent, Symbol nav_type);

    void SendTransition(const Message &msg, Symbol forward, Symbol back);
    /** Add the supplied component to this PanelDir's list of components. */
    void AddComponent(UIComponent *component);
    /** Update the state of the focus component (either focused or normal). */
    void UpdateFocusComponentState();
    /** Set whether or not to show the focus component. */
    void SetShowFocusComponent(bool show);
    void EnableComponent(UIComponent *, RequestFocus);
    void DisableComponent(UIComponent *, JoypadAction);
    bool PanelNav(JoypadAction, JoypadButton, Symbol);
    UIComponent *ComponentNav(UIComponent *, JoypadAction, JoypadButton, Symbol);
    /** Get the first focusable UIComponent in this PanelDir. */
    UIComponent *GetFirstFocusableComponent();
    void SyncEditModePanels();
    bool
    PropSyncEditModePanels(std::vector<FilePath> &, DataNode &, DataArray *, int, PropOp);

    /** Get a DataArray of all focusable components in this PanelDir. */
    DataNode GetFocusableComponentList();
    DataNode OnEnableComponent(const DataArray *);
    DataNode OnDisableComponent(const DataArray *);
    DataNode OnMsg(const ButtonDownMsg &);

    void SetCam(RndCam *cam) { mCam = cam; }
    void SetOwnerPanel(class UIPanel *p) { mOwnerPanel = p; }
    RndCam *GetCam() const { return mCam; }

    DECLARE_REVS
    static bool sAlwaysNeedFocus;
    NEW_OBJ(PanelDir);
    static void Init() { REGISTER_OBJ_FACTORY(PanelDir); }

    /** The currently focused-on component. */
    UIComponent *mFocusComponent; // 0x18c
    class UIPanel *mOwnerPanel; // 0x190
    /** "Camera to use in game, else standard UI cam" */
    ObjPtr<RndCam> mCam; // 0x194
    /** The list of UITriggers within this PanelDir. */
    std::list<UITrigger *> mTriggers; // 0x1a0
    /** The list of UIComponents within this PanelDir. */
    std::list<UIComponent *> mComponents; // 0x1a8
    /** "Trigger postprocs before drawing this panel.
     * If checked, this panel will not be affected by the postprocs." */
    bool mCanEndWorld; // 0x1b0
    /** "Forces the usage of the 'cam' property to render in milo. This is a milo only
     * feature." */
    bool mUseSpecifiedCam; // 0x1b1
    /** "Additional panels to display behind this panel." */
    std::vector<RndDir *> mBackPanels; // 0x1b4
    /** The file paths of the aforementioned back panels. */
    std::vector<FilePath> mBackFilenames; // 0x1bc
    /** "Additional panels to display in front of this panel." */
    std::vector<RndDir *> mFrontPanels; // 0x1c4
    /** The file paths of the aforementioned front panels. */
    std::vector<FilePath> mFrontFilenames; // 0x1cc
    /** "Whether or no this panel displays its view only panels" */
    bool mShowEditModePanels; // 0x1d4
    /** Whether or not to show the currently focused component. */
    bool mShowFocusComponent; // 0x1d5
};
