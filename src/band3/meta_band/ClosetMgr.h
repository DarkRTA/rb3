#pragma once
#include "bandobj/BandCharDesc.h"
#include "game/BandUser.h"
#include "meta_band/BandProfile.h"
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

    static ClosetMgr* GetClosetMgr();

    LocalBandUser* mUser; // 0x1c
    int unk20;
    bool unk24;
    BandProfile* unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    BandCharDesc* unk3c;
    int unk40;
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