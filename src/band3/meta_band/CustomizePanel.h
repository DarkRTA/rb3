#pragma once
#include "bandobj/BandCharDesc.h"
#include "meta_band/AssetProvider.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/CurrentOutfitProvider.h"
#include "meta_band/InstrumentFinishProvider.h"
#include "meta_band/MakeupProvider.h"
#include "meta_band/NewAssetProvider.h"
#include "os/ContentMgr.h"
#include "os/JoypadMsgs.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"

class CustomizePanel : public UIPanel, public ContentMgr::Callback {
public:
    enum CustomizeState {
        kCustomizeState_Invalid = 0,
        // 2 is a preview state, 1, 3 and 4 are not
        kCustomizeState_BrowseTorso = 5,
        kCustomizeState_BrowseLegs = 6,
        kCustomizeState_BrowseFeet = 7,
        kCustomizeState_BrowseHats = 9,
        kCustomizeState_BrowseEarrings = 10,
        kCustomizeState_BrowsePiercings = 11,
        kCustomizeState_BrowseGlassesAndMasks = 12,
        kCustomizeState_BrowseBandanas = 13,
        kCustomizeState_BrowseWrists = 14,
        kCustomizeState_BrowseRings = 15,
        kCustomizeState_BrowseGloves = 16,
        kCustomizeState_HairAndMakeup = 17,
        kCustomizeState_BrowseHair = 18,
        kCustomizeState_BrowseEyebrows = 19,
        kCustomizeState_BrowseFaceHair = 20,
        kCustomizeState_BrowseEyeMakeup = 21,
        kCustomizeState_BrowseLipMakeup = 22,
        kCustomizeState_Instruments = 23,
        kCustomizeState_BrowseGuitars = 24,
        kCustomizeState_BrowseBasses = 25,
        kCustomizeState_BrowseDrums = 26,
        kCustomizeState_BrowseMicrophones = 27,
        kCustomizeState_BrowseKeyboards = 28
    };
    CustomizePanel();
    OBJ_CLASSNAME(CustomizePanel);
    OBJ_SET_TYPE(CustomizePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~CustomizePanel();
    virtual void Enter();
    virtual void Exit();
    virtual bool Unloading() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void ContentStarted();
    virtual void ContentDone();
    virtual const char *ContentDir();

    void EnableFaceHair();
    void DisableFaceHair();
    void SetCustomizeState(CustomizeState);
    void SetPendingState(CustomizeState);
    void SetPatchMenuReturnState(CustomizeState);
    bool InPreviewState() const;
    bool InClothingState() const;
    void UpdateNewAssetProvider();
    void UpdateCurrentOutfitProvider();
    void RefreshNewAssetsList();
    void UpdateAssetProvider();
    AssetType GetAssetTypeFromCurrentState();
    void RefreshAssetsList();
    void UpdateMakeupProvider(Symbol);
    void SetCurrentBoutique(Symbol);
    Symbol GetCurrentBoutique();
    void ClearCurrentBoutique();
    Symbol GetWearing();
    Symbol StripFinish(Symbol);
    void RefreshCurrentOutfitList();
    void PreviewAsset(Symbol);
    void PreviewFinish(Symbol);
    void SelectAsset(Symbol);
    void ShowLockedDialog();
    void ChooseFinish();
    void ChooseColors();
    void GotoCustomizeClothingScreen();
    Symbol GetCurrentMakeup(Symbol);
    void ClearCurrentMakeupIndex();
    void SetCurrentMakeupIndex(int);
    void PreviewMakeup(Symbol);
    bool HasNewAssets();
    bool AssetProviderHasAsset(Symbol);
    void SetupCurrentOutfit(Symbol);
    bool HasPatch();
    void RotatePatch(int);
    bool HasLicense(Symbol);
    Symbol GetAssetShot(Symbol);
    void SetFocusComponent(CustomizeState, Symbol);
    void StoreFocusComponent();
    UIComponent *GetFocusComponent();
    void MovePatch(float, float);
    void ScalePatch(float, float);
    void RefreshPatchEdit();
    void SetIsWaitingToLeave(bool);
    void ClearAssetPatchData();
    bool IsCurrentAssetPatchable();
    const char *GetPlacementMeshFromCurrentCamShot();
    void PreparePatchEdit(BandCharDesc::Patch::Category);
    void PrepareAssetPatchEdit();
    void SetCurrentCharacterPatch();
    void FinishPatchEdit();
    void SavePrefab();
    bool CheatToggleAssetTokens();

    DataNode LeaveState(bool);
    DataNode LeaveCustomizePanel();
    DataNode OnMsg(const SigninChangedMsg &);
    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const UIComponentScrollMsg &);

    static CustomizeState sBackStates[];

    CustomizeState mCustomizeState; // 0x3c
    CustomizeState mPendingState; // 0x40
    CustomizeState mPatchMenuReturnState; // 0x44
    std::map<int, UIComponent *> unk48;
    ClosetMgr *mClosetMgr; // 0x60
    LocalBandUser *mUser; // 0x64
    BandProfile *mProfile; // 0x68
    CharData *mCharData; // 0x6c
    BandCharDesc *mPreviewDesc; // 0x70
    NewAssetProvider *mNewAssetProvider; // 0x74
    CurrentOutfitProvider *mCurrentOutfitProvider; // 0x78
    AssetProvider *mAssetProvider; // 0x7c
    int unk80;
    MakeupProvider *mMakeupProvider; // 0x84
    InstrumentFinishProvider *mInstrumentFinishProvider; // 0x88
    AssetBoutique mCurrentBoutique; // 0x8c
    Symbol unk90;
    int mCurrentMakeupIndex; // 0x94
    bool mUnlockedFacePaint; // 0x98
    bool mUnlockedTattoos; // 0x99
    bool unk9a;
    bool mWaitingToLeave; // 0x9b
    BandCharDesc::Patch::Category mPatchCategory; // 0x9c
    String unka0;
    bool mAssetTokens; // 0xac
};