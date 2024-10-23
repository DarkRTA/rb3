#pragma once
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/OutfitConfig.h"
#include "game/BandUser.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "os/ProfileSwappedMsg.h"
#include "obj/MsgSource.h"
#include "utl/Symbol.h"
#include "world/CameraShot.h"

class ClosetPanel;

class ClosetMgr : public MsgSource {
public:
    ClosetMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ClosetMgr();

    void Poll();
    void PreviewCharacter(bool, bool);
    bool IsCurrentCharacterFinalized();
    void UpdateCurrentCharacter();
    void SetCurrentOutfitPiece(Symbol);
    void UpdateBandCharDesc(BandCharDesc*);
    void FinalizeCharCreatorChanges();
    void FinalizeChanges(bool, bool);
    void ResetCharacterPreview();
    void ForceClosetPoll();
    int GetUserSlot() const;
    void CharacterFinishedLoading();
    bool InNoUserMode() const;
    void SetNoUserMode(bool);
    void SetUser(LocalBandUser*);
    void UpdatePreviousCharacter();
    void ClearUser();
    Symbol GetAssetFromAssetType(AssetType);
    void SetCurrentClosetPanel(ClosetPanel*);
    void ClearCurrentClosetPanel();
    void ResetNewCharacterPreview(Symbol);
    void FinalizeBodyChanges(Symbol);
    void PlayFinalizedSound(bool);
    void MakeProfileDirty();
    void TakePortrait();
    void UpdateCurrentOutfitConfig();
    void FinalizedColors();
    void SetCurrentCharacterPatch(BandCharDesc::Patch::Category, const char*);
    void UpdateCharacterPatch(BandCharDesc::Patch::Category, const char*);
    void RecomposePatches(int);
    void SetPatches();
    void ResetPatches();
    bool IsAlreadyLoaded();
    void SetDefaultColors();
    void HideClothes();
    void ShowClothes();
    CamShot* GetCurrentShot();
    void CycleCamera();
    void GotoArtMakerShot();
    void LeaveArtMakerShot();
    void SetInstrumentType(Symbol);
    void ClearInstrument();
    void SetReturnScreen(Symbol);
    bool IsCharacterLoading(){ return mCharacterLoading; }
    Symbol GetReturnScreen() const { return mReturnScreen; }
    LocalBandUser* GetUser() const { return mUser; }

    DataNode OnMsg(const ProfileSwappedMsg&);

    static void Init();
    static ClosetMgr* GetClosetMgr();

    LocalBandUser* mUser; // 0x1c
    int mSlot; // 0x20
    bool mNoUserMode; // 0x24
    BandProfile* unk28; // 0x28
    CharData* mCurrentCharacter; // 0x2c
    CharData* mPreviousCharacter; // 0x30
    BandCharacter* mBandCharacter; // 0x34
    BandCharDesc* mBandCharDesc; // 0x38
    BandCharDesc* unk3c; // 0x3c
    ClosetPanel* mCurrentClosetPanel; // 0x40
    Symbol unk44;
    BandCharDesc::OutfitPiece* mCurrentOutfitPiece; // 0x48
    OutfitConfig* unk4c;
    int unk50;
    int unk54;
    Symbol mReturnScreen; // 0x58
    Symbol mGender; // 0x5c
    bool mCharacterLoading; // 0x60
    bool unk61;
};