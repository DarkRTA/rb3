#pragma once
#include "meta_band/ClosetMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "ui/UIComponent.h"

class CharacterCreatorPanel : public TexLoadPanel {
public:
    CharacterCreatorPanel();
    OBJ_CLASSNAME(CharacterCreatorPanel);
    OBJ_SET_TYPE(CharacterCreatorPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CharacterCreatorPanel();
    virtual void Enter();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    void CreateNewCharacter();
    void AddGridThumbnails(Symbol);
    void SetGender(Symbol);

    int unk4c;
    std::map<int, UIComponent*> unk50; // 0x50
    ClosetMgr* mClosetMgr; // ClosetMgr*
    int unk6c; // TourCharLocal*
    int unk70;
    int unk74; // FaceTypeProvider*
    int mOutfitProvider; // OutfitProvider*
    int unk7c; // FaceHairProvider*
    int unk80; // FaceOptionsProvider*
    int unk84; // UIGridProvider*
    int unk88; // EyebrowsProvider*
    int unk8c; // UIGridProvider*
    Symbol unk90; // gender
    Symbol unk94;
    bool unk98;
    bool unk99;
};