#include "net_band/EntityUploader_Wii.h"
#include "net_band/EntityUploader.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "os/PlatformMgr.h"
#include "tour/TourSavable.h"

WiiEntityUploader gEntityUploader;
EntityUploader &TheEntityUploader = gEntityUploader;

void WiiEntityUploader::Init() {
    unk40 = 0;
    unk50 = 0;
    unk58 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk54 = 0;
    EntityUploader::Init();
}

void WiiEntityUploader::Terminate() { CleanupCall(true); }

void WiiEntityUploader::CleanupCall(bool b1) {
    if (unk40) {
        for (int i = 0; i < unk48; i++) {
            delete[] unk40[i];
        }
        delete[] unk40;
        unk40 = 0;
    }
    unk48 = 0;
    if (b1) {
        if (unk50) {
            delete[] unk50;
            unk50 = 0;
        }
        unk44 = 0;
        unk4c = 0;
    }
}

void WiiEntityUploader::Poll() {
    if (mState == 1) {
        if (!unk58 && !ThePlatformMgr.IsCheckingProfanity()) {
            BeginStringVerification();
        }
        if (HasServerTimedOut()) {
            mState = 4;
            unk58 = false;
            CleanupCall(true);
        }
    }
    if (mState == 2) {
        mState = 3;
        if (!BeginRockCentralOps(7)) {
            mState = 5;
        }
        RecordSubmissionTime();
    }
    EntityUploader::Poll();
}

bool WiiEntityUploader::VerifyBandName(
    const char *bandName, TourSavable *tour, Hmx::Object *pObjCallback
) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        mCallbackObj = pObjCallback;
        int check = BuildStringCheckOp(mUploadOps, bandName, 1, tour);
        unk54 = new DataArray(1);
        DataArray *arr = new DataArray(4);
        arr->Node(0) = check;
        arr->Node(1) = 2;
        arr->Node(2) = bandName;
        arr->Node(3) = 0;
        unk54->Node(0) = DataNode(arr, kDataArray);
        arr->Release();
        mCallType = 1;
        BeginStringVerification();
        return true;
    }
}

bool WiiEntityUploader::VerifyCharName(
    const char *charName, TourSavable *tour, Hmx::Object *pObjCallback
) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        mCallbackObj = pObjCallback;
        int check = BuildStringCheckOp(mUploadOps, charName, 0, tour);
        unk54 = new DataArray(1);
        DataArray *arr = new DataArray(4);
        arr->Node(0) = check;
        arr->Node(1) = 1;
        arr->Node(2) = charName;
        arr->Node(3) = 0;
        unk54->Node(0) = DataNode(arr, kDataArray);
        arr->Release();
        mCallType = 1;
        BeginStringVerification();
        return true;
    }
}

bool WiiEntityUploader::UpdateChar(TourCharLocal *c, Hmx::Object *pObjCallback) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        mCallbackObj = pObjCallback;
        int check = BuildUpdateCharOp(mUploadOps, c);
        if (check == 0) {
            RockCentralOpCompleteMsg msg(true, 0, DataNode(mEmptyArray, kDataArray));
            mCallbackObj->Handle(msg);
            return true;
        } else {
            unk54 = new DataArray(1);
            DataArray *arr = new DataArray(4);
            arr->Node(0) = check;
            arr->Node(1) = 1;
            arr->Node(2) = c->GetCharacterName();
            arr->Node(3) = 0;
            unk54->Node(0) = DataNode(arr, kDataArray);
            arr->Release();
            mCallType = 3;
            BeginStringVerification();
            return true;
        }
    }
}

bool WiiEntityUploader::UpdateFromProfile(
    BandProfile *pProfile, Hmx::Object *pObjCallback
) {
    if (mState != 0) {
        if (pObjCallback) {
            RockCentralOpCompleteMsg msg(false, 1, DataNode(mEmptyArray, kDataArray));
            pObjCallback->Handle(msg);
        }
        return false;
    } else {
        mCallbackObj = pObjCallback;
        int ops = BuildProfileUploadOps(mUploadOps, pProfile);
        if (ops == 0) {
            RockCentralOpCompleteMsg msg(true, 0, DataNode(mEmptyArray, kDataArray));
            mCallbackObj->Handle(msg);
            return true;
        } else {
            unk54 = new DataArray(ops);
            int i12 = 0;
            for (int i = 0; i < ops; i++) {
                EntityData *curData = mUploadOps[i];
                int opType = curData->mOpType;
                if (opType == 2) {
                    TourSavable *tour = curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 1;
                    arr->Node(2) = tour->Name();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                } else if (opType == 3) {
                    TourSavable *tour = curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 2;
                    arr->Node(2) = tour->Name();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                } else if (opType == 4) {
                    TourSavable *tour = curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 7;
                    arr->Node(2) = tour->Name();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                    unk54->Resize(unk54->Size() + 1);

                    arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 8;
                    arr->Node(2) = tour->Name();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                }
            }
            unk54->Resize(i12);
            mCallType = 6;
            BeginStringVerification();
            return true;
        }
    }
}