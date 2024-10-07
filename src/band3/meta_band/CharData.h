#pragma once
#include "obj/Object.h"
#include "bandobj/BandCharDesc.h"
#include "rndobj/Tex.h"
#include "utl/HxGuid.h"

class CharData : public virtual Hmx::Object {
public:
    CharData();
    virtual DataNode Handle(DataArray*, bool);
    virtual const char* GetCharacterName() const = 0;
    virtual BandCharDesc* GetBandCharDesc() const = 0;
    virtual RndTex* GetPortraitTex() const = 0;
    virtual void CachePortraitTex(RndTex*) = 0;
    virtual bool IsFinalized() const = 0;
    virtual bool IsCustomizable() const = 0;
    virtual RndTex* GetTexAtPatchIndex(int, bool) const = 0;
    virtual ~CharData();

    HxGuid mGuid; // 0x8
};

class PrefabChar : public CharData {
public:
    PrefabChar(BandCharDesc*);
    virtual const char* GetCharacterName() const;
    virtual BandCharDesc* GetBandCharDesc() const;
    virtual RndTex* GetPortraitTex() const;
    virtual void CachePortraitTex(RndTex*);
    virtual bool IsFinalized() const;
    virtual bool IsCustomizable() const;
    virtual RndTex* GetTexAtPatchIndex(int, bool) const;
    virtual ~PrefabChar();

    BandCharDesc* mBandCharDesc; // 0x18
    RndTex* mPortraitTex; // 0x1c
    FileLoader* unk20; // 0x20
    String unk24; // 0x24
};