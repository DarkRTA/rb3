#pragma once
#include "net_band/EntityUploader.h"
#include "obj/Data.h"
#include "os/PlatformMgr.h"

class WiiEntityUploader : public EntityUploader {
public:
    WiiEntityUploader() {}
    virtual ~WiiEntityUploader() {}
    virtual DataNode Handle(DataArray *, bool);
    virtual void Init();
    virtual void Terminate();
    virtual bool VerifyBandName(char const *, TourSavable *, Hmx::Object *);
    virtual bool VerifyCharName(char const *, TourSavable *, Hmx::Object *);
    virtual bool UpdateChar(TourCharLocal *, Hmx::Object *);
    virtual bool UpdateFromProfile(BandProfile *, Hmx::Object *);
    virtual void Poll();

    void CleanupCall(bool);
    void BeginStringVerification();
    void SetStringPassedStatus(TourSavable *, int, int, bool);
    void ProcessStringResponses();
    bool OnMsg(const DWCProfanityResultMsg &);

    const unsigned short **unk40; // 0x40
    int unk44; // 0x44
    int mNumStringsEnroute; // 0x48
    int unk4c; // 0x4c
    char *unk50; // 0x50
    DataArray *unk54; // 0x54
    bool mbCheckInProgress; // 0x58
};