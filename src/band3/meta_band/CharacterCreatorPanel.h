#pragma once
#include "FaceHairProvider.h"
#include "FaceOptionsProvider.h"
#include "OutfitProvider.h"
#include "bandobj/BandCharDesc.h"
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
    void SetOutfit(Symbol);
    void SetEyeColor(int);
    int GetEyeColor();
    void SetGlasses(Symbol);
    Symbol GetGlasses();
    void UpdateOutfitList();
    void SetHair(Symbol);
    Symbol GetHair();
    void SetFaceHair(Symbol);
    Symbol GetFaceHair();
    void SetHeight(int);
    int GetHeight();
    void SetWeight(int);
    int GetWeight();
    void SetBuild(int);
    int GetBuild();
    void SetSkinTone(int);
    int GetSkinTone();
    void RandomizeFace();
    Symbol GetRandomEyebrows();
    void SetFaceType(Symbol);
    void SetFaceOption(int);
    void SetEyebrows(Symbol);
    Symbol GetEyebrows();
    int GetFeatureIndex(Symbol);
    void ModifyFeature(Symbol, float);
    void RefreshFaceOptionsList();
    void FinalizeCharacter();
    void CheckCharacterAssets();
    void SetIsWaitingToFinalize(bool);
    void SetFocusComponent(CharCreatorState, Symbol);
    void StoreFocusComponent();
    UIComponent* GetFocusComponent();
    Symbol GetGender() const { return mGender; }
    Symbol GetOutfit(){ return mOutfit; }
    CharCreatorState GetCharCreatorState() const { return mCharCreatorState; }

    DataNode OnMsg(const ButtonDownMsg&);
    DataNode LeaveState();

    static CharCreatorState sCancelStates[18];

    CharCreatorState mCharCreatorState; // 0x4C
    std::map<int, UIComponent*> unk50; // 0x50
    ClosetMgr* mClosetMgr; // 0x68
    TourCharLocal* mCharacter; // 0x6c
    BandCharDesc* mPreviewDesc; // 0x70
    FaceTypeProvider* mFaceTypeProvider; // 0x74
    OutfitProvider* mOutfitProvider; // 0x78
    FaceHairProvider* mFaceHairProvider; // 0x7c
    FaceOptionsProvider* mFaceOptionsProvider; // 0x80
    UIGridProvider* mFaceOptionsGridProvider; // 0x84
    EyebrowsProvider* mEyebrowsProvider; // 0x88
    UIGridProvider* mEyebrowsGridProvider; // 0x8c
    Symbol mGender; // 0x90
    Symbol mOutfit; // 0x94
    bool unk98; // 0x98
    bool mWaitingToFinalize; // 0x99
};