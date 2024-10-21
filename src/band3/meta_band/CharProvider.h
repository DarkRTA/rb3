#pragma once
#include "BandProfile.h"
#include "meta_band/CharData.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class LocalBandUser;

class CharProvider : public UIListProvider, public Hmx::Object {
public:
    class CharacterEntry {
    public:
        CharacterEntry(int i1, Symbol s, CharData* i2, BandProfile* i3, bool b) : unk0(i1), unk4(i2), unk8(s), unkc(i3), unk10(b) {}

        int unk0;
        CharData* unk4;
        Symbol unk8;
        BandProfile* unkc;
        bool unk10;
    };

    struct CompareCharacters {
        bool operator()(CharacterEntry, CharacterEntry){}
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
    void Reload(LocalBandUser*);
    void AddCharactersFromProfile(BandProfile*);

    LocalBandUser* unk20; // 0x20
    std::vector<CharacterEntry> mCharacters; // 0x24
    bool unk2c; // 0x2c
    bool unk2d; // 0x2d
    int unk30; // 0x30
};