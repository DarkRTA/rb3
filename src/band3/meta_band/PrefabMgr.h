#pragma once
#include "game/BandUserMgr.h"
#include "obj/Data.h"
#include "obj/Object.h"

class PrefabMgr : public Hmx::Object {
public:
    class CharCreatorPrefab {
    public:
    };

    PrefabMgr();
    virtual ~PrefabMgr();
    virtual DataNode Handle(DataArray*, bool);

    void Poll();
    void PollPortraits();

    static PrefabMgr* GetPrefabMgr();
    static bool PrefabIsCustomizable();
    static DataNode OnPrefabIsCustomizable(DataArray*);
    static DataNode OnPrefabToggleCustomizable(DataArray*);
    static bool PrefabUsesProfilePatches();
    static DataNode OnPrefabUsesProfilePatches(DataArray*);
    static DataNode OnPrefabToggleUsesProfilePatches(DataArray*);
    static void Init(BandUserMgr*);

    std::vector<int> mPrefabs; // 0x1c
    std::vector<int> unk24; // 0x24
    std::vector<int> unk2c; // 0x2c
    std::vector<int> unk34; // 0x34
    std::vector<int> unk3c; // 0x3c
    std::set<Symbol> unk44; // 0x64
    BandUserMgr* unk5c; // 0x5c
    bool unk60; // 0x60
    std::vector<int> unk64; // 0x64
    std::vector<int> unk6c; // 0x6c
};