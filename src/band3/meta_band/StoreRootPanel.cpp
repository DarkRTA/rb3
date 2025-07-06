#include "StoreRootPanel.h"
#include "BandSongMetadata.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "rndobj/Dir.h"
#include "rndobj/Overlay.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"

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

int InitStoreOverlay() { 
    gStoreUIOverlay = RndOverlay::Find(store, false);
}