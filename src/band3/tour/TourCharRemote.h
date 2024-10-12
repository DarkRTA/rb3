#pragma once
#include "tour/TourChar.h"
#include "utl/BinStream.h"

// TODO: rename this once we have a better idea of what this actually is
struct TCRStruct {
    unsigned char index;
    RndTex* patch;
};

class TourCharRemote : public TourChar {
public:
    TourCharRemote();
    virtual DataNode Handle(DataArray*, bool);
    virtual RndTex* GetTexAtPatchIndex(int, bool) const;
    virtual ~TourCharRemote();

    void SyncLoad(BinStream&);

    std::vector<TCRStruct> unk4c; // 0x4c
};