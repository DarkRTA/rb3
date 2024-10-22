#pragma once
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "obj/Dir.h"
#include "obj/Object.h"

class CharCache : public Hmx::Object {
public:
    CharCache();
    virtual ~CharCache();
    virtual DataNode Handle(DataArray*, bool);

    void InitMe();
    void Request(int, const std::vector<BandCharDesc*>&, bool, bool);
    BandCharacter* GetCharacter(int);
    void RecomposePatches(int, BandCharDesc*, int);
    void RecomposeCharsWithPatchIx(int);
    int FindSlot(BandCharacter*);
    bool CharactersAreLoading();
    void Lock(bool, bool);

    DataNode OnGetPatchTex(DataArray*);

    static void Init();

    ObjDirPtr<ObjectDir> unk1c; // 0x1c
    bool unk28; // 0x28
};

extern CharCache* TheCharCache;