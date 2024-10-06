#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class LocalBandUser;

class CharProvider : public UIListProvider, public Hmx::Object {
public:
    class CharacterEntry {
    public:
        int unk0;
        int unk4;
        Symbol unk8;
        int unkc;
        int unk10;
    };

    CharProvider(LocalBandUser*, bool, bool);
    virtual ~CharProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const { return mCharacters.size(); }
    virtual bool IsActive(int) const;
    virtual DataNode Handle(DataArray*, bool);

    void Clear();
    bool IsIndexNewChar(int);
    
    LocalBandUser* unk20; // 0x20
    std::vector<CharacterEntry> mCharacters; // 0x24
    bool unk2c; // 0x2c
    bool unk2d; // 0x2d
    int unk30; // 0x30
};