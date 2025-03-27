#pragma once
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/BandProfile.h"
#include "bandobj/PatchDir.h"

class TourBand : public TourSavable, public FixedSizeSaveable {
public:
    TourBand(BandProfile *);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~TourBand();
    virtual bool IsUploadNeeded() const;
    virtual int SecBetweenUploads() const { return 5; }
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void SetBandName(const char *);
    void ChooseBandLogo(int, int);
    int GetBandID() const;
    void ProcessRetCode(int);
    const char *GetName() const { return mBandName.c_str(); }
    PatchDescriptor *GetLogo() const { return mBandLogo; }

    static int SaveSize(int);

    BandProfile *unk1c; // 0x1c
    String mBandName; // 0x20
    PatchDescriptor *mBandLogo; // 0x2c
    int unk30; // 0x30
};