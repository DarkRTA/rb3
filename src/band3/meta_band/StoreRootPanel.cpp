#include "StoreRootPanel.h"
#include "utl/Str.h"
#include "utl/TextStream.h"
StoreRootPanel::StoreRootPanel() {}

StoreRootPanel::~StoreRootPanel() {
    
}

void StoreRootPanel::Enter() {
    UIPanel::Enter();
}

void StoreRootPanel::Exit() {
    UIPanel::Exit();
}

void StoreRootPanel::Unload() {
    UIPanel::Unload();
}

DataNode StoreRootPanel::OnMsg(const MetadataLoadedMsg &msg) { return DataNode(kDataFloat, 6); }

BEGIN_HANDLERS(StoreRootPanel)
    HANDLE_MESSAGE(MetadataLoadedMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(149)
END_HANDLERS

void InitStoreOverlay() { 
    gStoreUIOverlay = RndOverlay::Find(store, false);
}

void UpdateStoreOverlay() {
    
    if (gStoreUIOverlay && gStoreUIOverlay->mShowing != false) {
        gStoreUIOverlay->Clear();
        //I have no idea what DAT_80D17CBC is
    }
}