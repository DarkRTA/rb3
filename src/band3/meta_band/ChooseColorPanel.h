#pragma once
#include "bandobj/BandCharDesc.h"
#include "bandobj/OutfitConfig.h"
#include "meta_band/ClosetMgr.h"
#include "ui/UIPanel.h"
#include "world/ColorPalette.h"

class ChooseColorPanel : public UIPanel {
public:
    ChooseColorPanel();
    OBJ_CLASSNAME(ChooseColorPanel);
    OBJ_SET_TYPE(ChooseColorPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ChooseColorPanel(){}
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();    
    virtual void Poll();    
    virtual void Load();
    virtual void Unload();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    void AddColorOption(int, ColorPalette*);
    int GetCurrentColor();
    void PreviewColor(int);

    ClosetMgr* mClosetMgr; // 0x38
    OutfitConfig* mCurrentOutfitConfig; // 0x3c
    BandCharDesc::OutfitPiece* mCurrentOutfitPiece; // 0x40
    std::map<int, ColorPalette*> mColorOptions; // 0x44
    int mNumOptions; // 0x5c
    int mCurrentOption; // 0x60
};