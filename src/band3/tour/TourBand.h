#pragma once
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/BandProfile.h"
#include "bandobj/PatchDir.h"

class TourBand : public TourSavable, public FixedSizeSaveable {
public:
    TourBand(BandProfile*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourBand();
    virtual bool IsUploadNeeded() const;
    virtual int SecBetweenUploads() const { return 5; }
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void SetBandName(const char*);
    void ChooseBandLogo(int, int);

    static int SaveSize(int);

    BandProfile* unk1c; // 0x1c
    String unk20; // 0x20
    PatchDescriptor* unk2c; // ptr to some struct
    int unk30; // 0x30
};