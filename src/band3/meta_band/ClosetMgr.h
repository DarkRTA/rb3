#pragma once
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "game/BandUser.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/ClosetPanel.h"
#include "os/ProfileSwappedMsg.h"
#include "obj/MsgSource.h"

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

    DataNode OnMsg(const ProfileSwappedMsg&);

    static void Init();
    static ClosetMgr* GetClosetMgr();

    LocalBandUser* mUser; // 0x1c
    int mSlot; // 0x20
    bool mNoUserMode; // 0x24
    BandProfile* unk28; // 0x28
    CharData* mCurrentCharacter; // 0x2c
    CharData* unk30; // 0x30
    BandCharacter* mBandCharacter; // 0x34
    BandCharDesc* mBandCharDesc; // 0x38
    BandCharDesc* unk3c;
    ClosetPanel* unk40;
    Symbol unk44;
    int unk48;
    int unk4c;
    int unk50;
    int unk54;
    Symbol unk58;
    Symbol unk5c;
    bool unk60;
    bool unk61;
};