#include "ui/PanelDir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/ObjVersion.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "rndobj/Cam.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

INIT_REVS(PanelDir)

PanelDir::PanelDir() : mFocusComponent(0), mOwnerPanel(0), mCam(this, 0), mCanEndWorld(1), mUseSpecifiedCam(0), mShowEditModePanels(0), mShowFocusComponent(1) {
    if(TheLoadMgr.EditMode()) mShowEditModePanels = true;
}

PanelDir::~PanelDir() {
    for (std::vector<class PanelDir*>::iterator it = mBackPanels.begin(); it != mBackPanels.end(); it++) {
        delete (*it);
        *it = NULL;
    }
    for (std::vector<class PanelDir*>::iterator it = mFrontPanels.begin(); it != mFrontPanels.end(); it++) {
        delete (*it);
        *it = NULL;
    }
}

SAVE_OBJ(PanelDir, 57)

void PanelDir::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(8, 0)
    PushRev(packRevs(gAltRev, gRev), this);    
    RndDir::PreLoad(bs);
}

void PanelDir::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gAltRev = getAltRev(revs);
    gRev = getHmxRev(revs);
    if(this == Dir()){
        if(gRev != 0) bs >> mCam;
        if(gRev == 2){
            Symbol s;
            bs >> s;
        }
    }
    if(gRev > 3) bs >> mCanEndWorld;
    if(gRev > 4) bs >> mBackFilenames >> mFrontFilenames;
    if(gRev > 5) bs >> mShowEditModePanels;
    if(gRev > 7){
        if(gLoadingProxyFromDisk){
            bool b;
            bs >> b;
        }
        else bs >> mUseSpecifiedCam;
    }
    SyncEditModePanels();
}

BEGIN_COPYS(PanelDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(PanelDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mCam)
        COPY_MEMBER(mCanEndWorld)
        COPY_MEMBER(mBackFilenames)
        COPY_MEMBER(mFrontFilenames)
        COPY_MEMBER(mShowEditModePanels)
        COPY_MEMBER(mUseSpecifiedCam)
        SyncEditModePanels();
    END_COPYING_MEMBERS
END_COPYS

void PanelDir::Enter(){
    RndDir::Enter();
    // iterate through mTriggers
    SendTransition(ui_enter_msg, ui_enter_forward, ui_enter_back);
}

void PanelDir::Exit(){
    RndDir::Exit();
    SendTransition(ui_exit_msg, ui_exit_forward, ui_exit_back);
}

BEGIN_PROPSYNCS(PanelDir)
    SYNC_PROP(cam, mCam)
    SYNC_PROP(postprocs_before_draw, mCanEndWorld)
    SYNC_PROP(use_specified_cam, mUseSpecifiedCam)
    SYNC_PROP(focus_component, mFocusComponent) // ????
    SYNC_PROP(owner_panel, mOwnerPanel)

    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS