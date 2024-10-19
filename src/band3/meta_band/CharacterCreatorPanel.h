#pragma once
#include "FaceHairProvider.h"
#include "FaceOptionsProvider.h"
#include "OutfitProvider.h"
#include "game/BandUser.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/EyebrowsProvider.h"
#include "meta_band/FaceTypeProvider.h"
#include "meta_band/TexLoadPanel.h"
#include "tour/TourCharLocal.h"
#include "ui/UIComponent.h"
#include "ui/UIGridProvider.h"

class CharacterCreatorPanel : public TexLoadPanel {
public:
    enum CharCreatorState {
        kCharCreatorState_Invalid = 0
    };

    CharacterCreatorPanel();
    OBJ_CLASSNAME(CharacterCreatorPanel);
    OBJ_SET_TYPE(CharacterCreatorPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CharacterCreatorPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    void CreateNewCharacter();
    void AddGridThumbnails(Symbol);
    void AddGridThumbnails(Symbol, Symbol);
    void SetGender(Symbol);
    void SetProviders();
    void HandleGenderChanged();
    void SetCharCreatorState(CharCreatorState);
    LocalBandUser* GetUser();
    void SetName(const char*);
    void UpdateNameLabel();
    const char* GetName();
    const char* GetDefaultVKName();

    CharCreatorState mCharCreatorState; // 0x4C
    std::map<int, UIComponent*> unk50; // 0x50
    ClosetMgr* mClosetMgr; // 0x68
    TourCharLocal* mCharacter; // 0x6c
    int unk70;
    FaceTypeProvider* mFaceTypeProvider; // 0x74
    OutfitProvider* mOutfitProvider; // 0x78
    FaceHairProvider* mFaceHairProvider; // 0x7c
    FaceOptionsProvider* mFaceOptionsProvider; // 0x80
    UIGridProvider* mFaceOptionsGridProvider; // 0x84
    EyebrowsProvider* mEyebrowsProvider; // 0x88
    UIGridProvider* mEyebrowsGridProvider; // 0x8c
    Symbol mGender; // gender
    Symbol mOutfit; // outfit
    bool unk98;
    bool unk99;
};