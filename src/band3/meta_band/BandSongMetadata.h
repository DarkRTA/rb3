#pragma once
#include "meta/SongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "os/DateTime.h"

class BandSongMetadata : public SongMetadata {
public:
    BandSongMetadata(BandSongMgr*);
    BandSongMetadata(DataArray*, DataArray*, bool, BandSongMgr*);
    virtual ~BandSongMetadata();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual bool IsVersionOK() const;

    void InitBandSongMetadata();

    String unk40;
    String unk4c;
    String unk58;
    short unk64;
    short unk66;
    DateTime unk68;
    DateTime unk6e;
    Symbol unk74;
    int unk78;
    Symbol unk7c;
    int unk80;
    int unk84;
    std::map<Symbol, float> unk88;
    float unka0;
    int unka4;
    int unka8;
    int unkac;
    float unkb0;
    float unkb4;
    Symbol unkb8;
    Symbol unkbc;
    Symbol unkc0;
    int unkc4[6];
    int unkdc[4];
    std::vector<Symbol> unkec;
    bool unkf4;
    bool unkf5;
    bool unkf6;
    bool unkf7;
    bool unkf8;
    bool unkf9;
    bool unkfa;
    bool unkfb;
    bool unkfc;
    BandSongMgr* unk100;
};