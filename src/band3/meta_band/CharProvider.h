#pragma once
#include "BandProfile.h"
#include "meta_band/CharData.h"
#include "ui/UIListProvider.h"
#include "obj/Object.h"
#include "utl/Locale.h"

class LocalBandUser;

class CharProvider : public UIListProvider, public Hmx::Object {
public:
    enum CharacterEntryType {
        kCharacterEntryNone = 0,
        kCharacterEntryNew = 1,
        kCharacterEntryPrefab = 2,
        kCharacterEntryCustom = 3,
        kCharacterEntryHeader = 4
    };

    class CharacterEntry {
    public:
        CharacterEntry(CharacterEntryType i1, Symbol s, CharData* i2, BandProfile* i3, bool b) : unk0(i1), unk4(i2), unk8(s), unkc(i3), unk10(b) {}
        ~CharacterEntry(){}

        CharacterEntryType unk0; // CharEntryType enum?
        CharData* unk4;
        Symbol unk8;
        BandProfile* unkc;
        bool unk10;
    };

    struct CompareCharacters {
        bool operator()(const CharacterEntry& e1, const CharacterEntry& e2) const {

            if(e1.unk0 == e2.unk0 && e1.unk0 - 2 <= 1U){
                return strcmp(Localize(e1.unk8, 0), Localize(e2.unk8, 0)) < 0;
            }
            return false;
        }
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