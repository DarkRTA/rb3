#include "net_band/EntityUploader.h"
#include "meta_band/BandProfile.h"
#include "meta_band/SavedSetlist.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "tour/TourBand.h"
#include "tour/TourCharLocal.h"
#include "tour/TourSavable.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include <cstddef>

EntityUploader::EntityUploader()
    : mCallType(0), mState(0), mNumUploadOps(0), mCallbackObj(0), mOpIdGenerator(1) {}

void EntityUploader::Init() {
    SetName("entity_uploader", ObjectDir::Main());
    GetDateAndTime(mSubmittedTime);
    mEmptyArray = new DataArray(0);
}

bool EntityUploader::VerifyBandName(
    const char *bandName, TourSavable *tour, Hmx::Object *pObjCallback
) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        MILO_ASSERT(bandName != NULL, 0x3C);
        MILO_ASSERT(pObjCallback != NULL, 0x3D);
        mCallbackObj = pObjCallback;
        BuildStringCheckOp(mUploadOps, bandName, 1, tour);
        mCallType = 2;
        mState = 3;
        if (BeginRockCentralOps(3) == 0) {
            mState = 5;
        }
        RecordSubmissionTime();
        return true;
    }
}

bool EntityUploader::VerifyCharName(
    const char *charName, TourSavable *tour, Hmx::Object *pObjCallback
) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        MILO_ASSERT(charName != NULL, 0x5D);
        MILO_ASSERT(pObjCallback != NULL, 0x5E);
        mCallbackObj = pObjCallback;
        BuildStringCheckOp(mUploadOps, charName, 0, tour);
        mCallType = 1;
        mState = 3;
        if (BeginRockCentralOps(3) == 0) {
            mState = 5;
        }
        RecordSubmissionTime();
        return true;
    }
}

bool EntityUploader::UpdateChar(TourCharLocal *c, Hmx::Object *pObjCallback) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        MILO_ASSERT(c != NULL, 0x7E);
        MILO_ASSERT(pObjCallback != NULL, 0x7F);
        mCallbackObj = pObjCallback;
        if (BuildUpdateCharOp(mUploadOps, c) == 0) {
            RockCentralOpCompleteMsg msg(true, 0, DataNode(mEmptyArray, kDataArray));
            mCallbackObj->Handle(msg);
            return true;
        } else {
            mCallType = 3;
            mState = 3;
            if (BeginRockCentralOps(3) == 0) {
                mState = 5;
            }
            RecordSubmissionTime();
            return true;
        }
    }
}

bool EntityUploader::UpdateSetlist(LocalSavedSetlist *s, Hmx::Object *pObjCallback) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        MILO_ASSERT(s != NULL, 0xA6);
        MILO_ASSERT(pObjCallback != NULL, 0xA7);
        mCallbackObj = pObjCallback;
        if (BuildUpdateSetlistOp(mUploadOps, s) == 0) {
            RockCentralOpCompleteMsg msg(true, 0, DataNode(mEmptyArray, kDataArray));
            mCallbackObj->Handle(msg);
            return true;
        } else {
            mCallType = 5;
            mState = 3;
            if (BeginRockCentralOps(7) == 0) {
                mState = 5;
            }
            RecordSubmissionTime();
            return true;
        }
    }
}

bool EntityUploader::UpdateFromProfile(BandProfile *pProfile, Hmx::Object *pObjCallback) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        MILO_ASSERT(pProfile != NULL, 0xCE);
        MILO_ASSERT(pObjCallback != NULL, 0xCF);
        mCallbackObj = pObjCallback;
        if (BuildProfileUploadOps(mUploadOps, pProfile) == 0) {
            RockCentralOpCompleteMsg msg(true, 0, DataNode(mEmptyArray, kDataArray));
            mCallbackObj->Handle(msg);
            return true;
        } else {
            mCallType = 6;
            mState = 3;
            if (BeginRockCentralOps(7) == 0) {
                mState = 5;
            }
            RecordSubmissionTime();
            return true;
        }
    }
}

int EntityUploader::BuildStringCheckOp(
    EntityData **&data, const char *cc, int i3, TourSavable *tour
) {
    int ret = GenerateOpID();
    *data = new EntityData();
    mNumUploadOps = 1;
    (*data)->mOpID = ret;
    (*data)->mOpType = i3;
    (*data)->mString = cc;
    (*data)->mRetCode = 0;
    (*data)->mOpFinished = false;
    (*data)->mSavableObject = tour;
    return ret;
}

int EntityUploader::BuildUpdateCharOp(EntityData **&data, TourCharLocal *tour) {
    int ret = 0;
    if (tour->IsUploadNeeded()) {
        ret = GenerateOpID();
        *data = new EntityData();
        mNumUploadOps = 1;
        (*data)->mOpID = ret;
        (*data)->mOpType = 2;
        (*data)->mString = tour->GetCharacterName();
        (*data)->mRetCode = 0;
        (*data)->mOpFinished = false;
        (*data)->mSavableObject = tour;
        tour->UploadAttempted();
    }
    return ret;
}

int EntityUploader::BuildUpdateSetlistOp(EntityData **&data, LocalSavedSetlist *setlist) {
    int ret = 0;
    if (setlist->NeedsUpload()) {
        ret = GenerateOpID();
        *data = new EntityData();
        mNumUploadOps = 1;
        (*data)->mOpID = ret;
        (*data)->mOpType = 4;
        (*data)->mRetCode = 0;
        (*data)->mOpFinished = false;
        (*data)->mSavableObject = setlist;
        (*data)->mString = setlist->GetTitle();
        setlist->UploadAttempted();
    }
    return ret;
}

int EntityUploader::GetNumUpdates(BandProfile *profile) {
    int num = 0;
    for (int i = 0; i < profile->NumChars(); i++) {
        TourCharLocal *cur = profile->CharAt(i);
        if (cur->IsUploadNeeded())
            num++;
    }
    if (profile->GetTourBand()->IsUploadNeeded()) {
        num++;
    }
    const std::vector<LocalSavedSetlist *> &setlists = profile->GetSavedSetlists();
    FOREACH (it, setlists) {
        if ((*it)->NeedsUpload())
            num++;
    }
    return num;
}

int EntityUploader::BuildProfileUploadOps(EntityData **&data, BandProfile *profile) {
    int opCount = GetNumUpdates(profile);
    if (opCount == 0)
        return 0;
    else {
        data = new EntityData *[opCount];
        int curOp = 0;
        mNumUploadOps = opCount;
        for (int i = 0; i < profile->NumChars(); i++) {
            TourCharLocal *cur = profile->CharAt(i);
            if (cur->IsUploadNeeded()) {
                int id = GenerateOpID();
                data[i] = new EntityData();
                data[i]->mOpID = id;
                data[i]->mOpType = 2;
                data[i]->mString = cur->GetCharacterName();
                data[i]->mRetCode = 0;
                data[i]->mOpFinished = false;
                data[i]->mSavableObject = cur;
                curOp++;
                cur->UploadAttempted();
            }
        }
        TourBand *band = profile->GetTourBand();
        if (band->IsUploadNeeded()) {
            int id = GenerateOpID();
            data[curOp] = new EntityData();
            data[curOp]->mOpID = id;
            data[curOp]->mOpType = 3;
            data[curOp]->mString = profile->GetBandName();
            data[curOp]->mRetCode = 0;
            data[curOp]->mOpFinished = false;
            data[curOp]->mSavableObject = band;
            curOp++;
            band->UploadAttempted();
        }
        const std::vector<LocalSavedSetlist *> &setlists = profile->GetSavedSetlists();
        FOREACH (it, setlists) {
            LocalSavedSetlist *cur = *it;
            if (cur->NeedsUpload()) {
                int id = GenerateOpID();
                data[curOp] = new EntityData();
                data[curOp]->mOpID = id;
                data[curOp]->mOpType = 4;
                data[curOp]->mRetCode = 0;
                data[curOp]->mOpFinished = false;
                data[curOp]->mSavableObject = cur;
                data[curOp]->mString = cur->GetTitle();
                curOp++;
                cur->UploadAttempted();
            }
        }
        MILO_ASSERT(curOp == opCount, 0x192);
        return opCount;
    }
}

void EntityUploader::RockCentralOpComplete(bool b1, int i2, int i3) {
    if (mState == 3) {
        bool bvar1 = true;
        for (int i = 0; i < mNumUploadOps; i++) {
            if (i3 == mUploadOps[i]->mOpID) {
                mUploadOps[i]->mDataResultList.Update(nullptr);
                if (mUploadOps[i]->mDataResultList.NumDataResults() > 0) {
                    DataNode codeNode;
                    mUploadOps[i]->mDataResultList.GetDataResult(0)->GetDataResultValue(
                        "ret_code", codeNode
                    );
                    mUploadOps[i]->mRetCode = codeNode.Int();
                    mUploadOps[i]->mOpFinished = true;
                } else {
                    mUploadOps[i]->mRetCode = i2;
                    mUploadOps[i]->mOpFinished = true;
                }
                if (i2 != 1 && i2 != 11) {
                    if (mUploadOps[i]->mOpType == 2) {
                        TourSavable *obj = mUploadOps[i]->mSavableObject;
                        if (obj)
                            obj->UploadComplete();
                    }
                    if (mUploadOps[i]->mOpType == 4) {
                    }
                    if (mUploadOps[i]->mOpType == 3) {
                    }
                }
            }
        }
        if (bvar1) {
            for (int i = 0; i < mNumUploadOps; i++) {
                delete mUploadOps[i];
            }
            delete mUploadOps;
            mNumUploadOps = 0;
            mState = 5;
            Poll();
        }
    }
}

void EntityUploader::Poll() {
    if (mState == 3 && HasServerTimedOut()) {
        mState = 4;
    }
    if (mState == 5) {
        MILO_ASSERT(mCallbackObj != NULL, 0x1FB);
        int oldCallType = mCallType;
        Hmx::Object *oldCallbackObj = mCallbackObj;
        mState = 0;
        mCallbackObj = nullptr;
        mCallType = 0;
        unk34 = false;
        switch (oldCallType) {
        case 1:
        case 2:
        case 3:
        case 4: {
            RockCentralOpCompleteMsg msg(
                oldCallType != 1, oldCallType, DataNode(mEmptyArray, kDataArray)
            );
            oldCallbackObj->Handle(msg);
        } break;
        case 6:
            ReturnProfileResults(oldCallbackObj);
            break;
        default:
            MILO_WARN("EntityUploader: Unknown call type %d\n", oldCallType);
            break;
        }
    } else if (mState == 4) {
        MILO_ASSERT(mCallbackObj != NULL, 0x21C);
        Hmx::Object *oldCallbackObj = mCallbackObj;
        mState = 0;
        mCallbackObj = nullptr;
        mCallType = 0;
        RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
        oldCallbackObj->Handle(msg);
        unk34 = false;
    }
}

void EntityUploader::Abort() {
    if (mCallbackObj)
        unk34 = true;
}

void EntityUploader::ReturnProfileResults(Hmx::Object *o) {
    bool b4 = true;
    for (int i = 0; i < mNumUploadOps && b4; i++) {
        if (mUploadOps[i]->mRetCode != 1)
            b4 = false;
    }
    if (b4) {
        RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
        o->Handle(msg);
    } else {
        DataArray *arr = new DataArray(mNumUploadOps);
        int i5 = 0;
        for (int i = 0; i < mNumUploadOps; i++) {
            if (mUploadOps[i]->mRetCode != 0) {
                DataArray *arr2 = new DataArray(2);
                arr2->Node(0) = mUploadOps[i]->mRetCode;
                arr2->Node(1) = mUploadOps[i]->mString;
                arr->Node(i5++) = DataNode(arr2, kDataArray);
                arr2->Release();
            }
        }
        arr->Resize(i5);
        RockCentralOpCompleteMsg msg(true, 0, DataNode(arr, kDataArray));
        o->Handle(msg);
        arr->Release();
    }
}

DataNode EntityUploader::OnVerifyBandName(DataArray *arr) {
    const char *bandName = arr->Str(2);
    Hmx::Object *callback = arr->Obj<Hmx::Object>(3);
    TourSavable *tour = arr->Obj<TourSavable>(4);
    VerifyBandName(bandName, tour, callback);
    return 0;
}

DataNode EntityUploader::OnVerifyCharName(DataArray *arr) {
    const char *bandName = arr->Str(2);
    Hmx::Object *callback = arr->Obj<Hmx::Object>(3);
    TourSavable *tour = arr->Obj<TourSavable>(4);
    VerifyCharName(bandName, tour, callback);
    return 0;
}

DataNode EntityUploader::OnUpdateFromProfile(DataArray *arr) {
    BandProfile *profile = arr->Obj<BandProfile>(2);
    Hmx::Object *callback = arr->Obj<Hmx::Object>(3);
    UpdateFromProfile(profile, callback);
    return 0;
}

DataNode EntityUploader::OnRockCentralOpComplete(DataArray *arr) {
    bool success = arr->Int(2);
    int arg1 = arr->Int(3);
    int arg2 = arr->Int(4);
    RockCentralOpComplete(success, arg1, arg2);
    return 0;
}

int EntityUploader::BeginRockCentralOps(int) {
    MILO_WARN("Unknown entity upload op %d\n");
}

void EntityUploader::RecordSubmissionTime() { GetDateAndTime(mSubmittedTime); }

bool EntityUploader::HasServerTimedOut() {
    DateTime dt;
    if (unk34)
        return true;
    else {
        GetDateAndTime(dt);
        return dt.ToCode() >= mSubmittedTime.ToCode();
    }
}

BEGIN_HANDLERS(EntityUploader)
    HANDLE(verify_band_name, OnVerifyBandName)
    HANDLE(verify_char_name, OnVerifyCharName)
    HANDLE(update_from_profile, OnUpdateFromProfile)
    HANDLE(rock_central_op_complete_msg, OnRockCentralOpComplete)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2EC)
END_HANDLERS