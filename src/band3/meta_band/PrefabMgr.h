#pragma once
#include "bandobj/BandCharDesc.h"
#include "game/BandUserMgr.h"
#include "meta_band/CharData.h"
#include "meta_band/OvershellSlot.h"
#include "obj/Data.h"
#include "obj/Object.h"

class PrefabMgr : public Hmx::Object {
public:
    class CharCreatorPrefab {
    public:
        CharCreatorPrefab(BandCharDesc*, Symbol);
        ~CharCreatorPrefab();

        PrefabChar* unk0;
        Symbol unk4;
    };

    PrefabMgr();
    virtual ~PrefabMgr();
    virtual DataNode Handle(DataArray*, bool);

    void Poll();
    void PollPortraits();
    void AssignPrefabsToSlots();
    void GetPrefabs(std::vector<PrefabChar*>&) const;
    void GetAvailablePrefabs(std::vector<PrefabChar*>&) const;
    PrefabChar* GetPrefab(Symbol);
    void EnableDebugPrefabs();
    PrefabChar* GetDefaultPrefab(int) const;
    CharCreatorPrefab* GetCharCreatorPrefab(Symbol, Symbol) const;
    CharCreatorPrefab* GetRandomCharCreatorPrefab(Symbol) const;
    CharCreatorPrefab* GetCharCreatorPrefabFromOutfit(const std::vector<CharCreatorPrefab*>&, Symbol) const;
    void GetFaceTypes(std::vector<Symbol>&, Symbol) const;
    BandCharDesc* GetFaceType(Symbol);
    void LoadPortraits(OvershellSlot*);
    void UnloadPortraits(OvershellSlot*);

    static PrefabMgr* GetPrefabMgr();
    static bool PrefabIsCustomizable();
    static DataNode OnPrefabIsCustomizable(DataArray*);
    static DataNode OnPrefabToggleCustomizable(DataArray*);
    static bool PrefabUsesProfilePatches();
    static DataNode OnPrefabUsesProfilePatches(DataArray*);
    static DataNode OnPrefabToggleUsesProfilePatches(DataArray*);
    static void Init(BandUserMgr*);

    std::vector<PrefabChar*> mPrefabs; // 0x1c
    std::vector<CharCreatorPrefab*> mCharCreatorMalePrefabs; // 0x24
    std::vector<CharCreatorPrefab*> mCharCreatorFemalePrefabs; // 0x2c
    std::vector<BandCharDesc*> unk34; // 0x34
    std::vector<PrefabChar*> mDefaultPrefabs; // 0x3c
    std::set<Symbol> unk44; // 0x44
    BandUserMgr* unk5c; // 0x5c
    bool unk60; // 0x60
    std::vector<PrefabChar*> unk64; // 0x64
    std::vector<OvershellSlot*> unk6c; // 0x6c
};