#pragma once
#include "meta_band/CharData.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/TourSavable.h"

class TourChar : public CharData, public FixedSizeSaveable, public TourSavable {
public:
    TourChar();
    virtual DataNode Handle(DataArray*, bool);
    virtual const char* GetCharacterName() const;
    virtual BandCharDesc* GetBandCharDesc() const;
    virtual RndTex* GetPortraitTex() const;
    virtual void CachePortraitTex(RndTex*);
    virtual bool IsFinalized() const;
    virtual bool IsCustomizable() const;
    virtual RndTex* GetTexAtPatchIndex(int, bool) const = 0;
    virtual ~TourChar();
    virtual int SecBetweenUploads() const { return 0x2D; }
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void SyncSave(BinStream&) const;

    static int SaveSize(int);

    String mName; // 0x34
    bool mIsFinalized; // 0x40
    bool unk41;
    BandCharDesc* mBandCharDesc; // 0x44
    RndTex* mPortraitTex; // 0x48
};