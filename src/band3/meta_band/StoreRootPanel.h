#pragma once

#include "obj/Data.h"
#include "rndobj/Overlay.h"
#include "ui/UIPanel.h"
#include "BandSongMetadata.h"
#include "obj/ObjMacros.h"
#include "rndobj/Dir.h"
#include "utl/Symbols.h"


class StoreRootPanel : public UIPanel {
public:
    StoreRootPanel();
    OBJ_CLASSNAME(StoreRootPanel);
    OBJ_SET_TYPE(StoreRootPanel);
    virtual ~StoreRootPanel();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Enter();
    virtual void Exit();
    virtual void Unload();

    DataNode OnMsg(const MetadataLoadedMsg&);

    State mMetadataState;
    DataArray *mDLCMetadata;
    DataArray *mUGCMetadata;
};

void InitStoreOverlay();
void UpdateStoreOverlay();
extern RndOverlay *gStoreUIOverlay; 