#pragma once
#include "meta_band/SavedSetlist.h"
#include "net_band/DataResults.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "tour/TourCharLocal.h"
#include "tour/TourSavable.h"

class EntityData {
public:
    EntityData() {}
    virtual ~EntityData() {}

    int mOpID; // 0x4
    int mOpType; // 0x8
    int mRetCode; // 0xc
    bool mOpFinished; // 0x10
    String mString; // 0x14
    TourSavable *mSavableObject; // 0x20
    DataResultList mDataResultList; // 0x24
};

class EntityUploader : public Hmx::Object {
public:
    EntityUploader();
    virtual ~EntityUploader() {}
    virtual DataNode Handle(DataArray *, bool);
    virtual void Init();
    virtual void Terminate() {}
    virtual bool VerifyBandName(char const *, TourSavable *, Hmx::Object *);
    virtual bool VerifyCharName(char const *, TourSavable *, Hmx::Object *);
    virtual bool UpdateChar(TourCharLocal *, Hmx::Object *);
    virtual bool UpdateSetlist(LocalSavedSetlist *, Hmx::Object *);
    virtual bool UpdateFromProfile(BandProfile *, Hmx::Object *);
    virtual void Poll();

    int BuildStringCheckOp(EntityData **&, const char *, int, TourSavable *);
    int BeginRockCentralOps(int);
    void RecordSubmissionTime();
    int BuildUpdateCharOp(EntityData **&, TourCharLocal *);
    int BuildUpdateSetlistOp(EntityData **&, LocalSavedSetlist *);
    int BuildProfileUploadOps(EntityData **&, BandProfile *);
    int GetNumUpdates(BandProfile *);
    void RockCentralOpComplete(bool, int, int);
    void Abort();
    bool HasServerTimedOut();
    void ReturnProfileResults(Hmx::Object *);

    DataNode OnVerifyBandName(DataArray *);
    DataNode OnVerifyCharName(DataArray *);
    DataNode OnUpdateFromProfile(DataArray *);
    DataNode OnRockCentralOpComplete(DataArray *);

    int GenerateOpID() { return ++mOpIdGenerator; }

    int mCallType; // 0x1c
    int mState; // 0x20
    EntityData **mUploadOps; // 0x24
    int mNumUploadOps; // 0x28
    DataArray *mEmptyArray; // 0x2c
    Hmx::Object *mCallbackObj; // 0x30
    bool unk34; // 0x34
    DateTime mSubmittedTime; // 0x35
    int mOpIdGenerator; // 0x3c
};

extern EntityUploader *TheEntityUploader;
