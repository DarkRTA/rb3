#include "net_band/EntityUploader_Wii.h"
#include "meta_band/SavedSetlist.h"
#include "net_band/EntityUploader.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "tour/TourBand.h"
#include "tour/TourCharLocal.h"
#include "tour/TourSavable.h"
#include "utl/UTF8.h"

WiiEntityUploader gEntityUploader;
EntityUploader &TheEntityUploader = gEntityUploader;

void WiiEntityUploader::Init() {
    unk40 = 0;
    unk50 = 0;
    mbCheckInProgress = 0;
    unk44 = 0;
    mNumStringsEnroute = 0;
    unk4c = 0;
    unk54 = 0;
    EntityUploader::Init();
}

void WiiEntityUploader::Terminate() { CleanupCall(true); }

void WiiEntityUploader::CleanupCall(bool b1) {
    if (unk40) {
        for (int i = 0; i < mNumStringsEnroute; i++) {
            delete[] unk40[i];
        }
        delete[] unk40;
        unk40 = 0;
    }
    mNumStringsEnroute = 0;
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
        if (!mbCheckInProgress && !ThePlatformMgr.IsCheckingProfanity()) {
            BeginStringVerification();
        }
        if (HasServerTimedOut()) {
            mState = 4;
            mbCheckInProgress = false;
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
                    TourCharLocal *tour = (TourCharLocal *)curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 1;
                    arr->Node(2) = tour->GetCharacterName();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                } else if (opType == 3) {
                    TourBand *tour = (TourBand *)curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 2;
                    arr->Node(2) = tour->GetName();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                } else if (opType == 4) {
                    LocalSavedSetlist *setlist =
                        (LocalSavedSetlist *)curData->mSavableObject;
                    DataArray *arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 7;
                    arr->Node(2) = setlist->GetTitle();
                    arr->Node(3) = 0;
                    unk54->Node(i12++) = DataNode(arr, kDataArray);
                    arr->Release();
                    unk54->Resize(unk54->Size() + 1);

                    arr = new DataArray(4);
                    arr->Node(0) = mUploadOps[i]->mOpID;
                    arr->Node(1) = 8;
                    arr->Node(2) = setlist->GetDescription();
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

void WiiEntityUploader::BeginStringVerification() {
    MILO_ASSERT((mState == kInactive || mState == kPlatformChecking) && !mbCheckInProgress, 0x174);
    mState = kPlatformChecking;
    if (!ThePlatformMgr.IsCheckingProfanity()) {
        unk44 = unk54->Size();
        int i5 = unk44 - unk4c;
        int i10 = 0x32;
        if (i5 <= 0x32)
            i10 = i5;
        mNumStringsEnroute = i10;
        MILO_ASSERT(mNumStringsEnroute > 0, 0x18A);
        unk40 = new const unsigned short *[mNumStringsEnroute];

        for (int i = unk4c; i < unk4c + mNumStringsEnroute; i++) {
            unsigned short *u9 = new unsigned short[strlen(unk54->Array(i)->Str(2)) + 1];
            const char *c4 = unk54->Array(i)->Str(2);
            UTF8toUTF16(u9, c4);
            unk40[i - unk4c] = u9;
        }

        unk50 = new char[mNumStringsEnroute];
        memset(unk50, 0, mNumStringsEnroute);
        if (!ThePlatformMgr.StartProfanity(unk40, mNumStringsEnroute, unk50, this)) {
            mState = 4;
            CleanupCall(true);
        } else {
            mbCheckInProgress = true;
            RecordSubmissionTime();
        }
    }
}

void WiiEntityUploader::SetStringPassedStatus(TourSavable *s, int i2, int i3, bool b4) {
    bool dirty = !b4;
    if (i2 <= 2U) {
        s->SetDirty(dirty, 4);
    } else if (i2 != 3)
        return;
    else if (i3 != 2)
        return;
    else {
        s->SetDirty(dirty, 4);
    }
}

void WiiEntityUploader::ProcessStringResponses() {
    for (int i = 0; i < unk54->Size(); i++) {
        int i2 = unk54->Array(i)->Int(0);
        int i1 = unk54->Array(i)->Int(1);
        int i4 = unk54->Array(i)->Int(3);
        for (int j = 0; j < mNumUploadOps; j++) {
            EntityData *curData = mUploadOps[j];
            if (i2 == curData->mOpID) {
                int opType = curData->mOpType;
                bool u3 = true;
                if (i4 != 0) {
                    u3 = false;
                    if (curData->mRetCode == 0) {
                        curData->mRetCode = i4;
                        if (curData->mRetCode != 1) {
                            switch (opType) {
                            case 3:
                                TourBand *band =
                                    (TourBand *)mUploadOps[j]->mSavableObject;
                                band->ProcessRetCode(curData->mRetCode);
                                band->UploadComplete();
                                break;
                            case 4:
                                LocalSavedSetlist *setlist =
                                    (LocalSavedSetlist *)mUploadOps[j]->mSavableObject;
                                setlist->ProcessRetCode(curData->mRetCode);
                                setlist->UploadComplete();
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
                TourSavable *e = mUploadOps[j]->mSavableObject;
                MILO_ASSERT(e, 0x1FD);
                SetStringPassedStatus(e, opType, i1, u3);
                break;
            }
        }
    }
}

bool WiiEntityUploader::OnMsg(const DWCProfanityResultMsg &msg) {
    if (mState == 1 && mbCheckInProgress) {
        mbCheckInProgress = false;
        if (msg->Int(2)) {
            int i5;
            for (int i = unk4c; i < unk4c + mNumStringsEnroute; i++) {
                int i7 = 0;
                if (unk50[i]) {
                    i5 = unk54->Array(i)->Int(1);
                    switch (i5) {
                    case 1:
                        i7 = 4;
                        break;
                    case 2:
                        i7 = 2;
                        break;
                    case 7:
                        i7 = 15;
                        break;
                    case 8:
                        i7 = 16;
                        break;
                    default:
                        MILO_FAIL("Bad check type %d for string\n", i5);
                        break;
                    }
                }
                unk54->Array(i)->Node(3) = i7;
            }
            unk4c = i5;
            if (i5 < unk44) {
                CleanupCall(false);
                RecordSubmissionTime();
                BeginStringVerification();
            } else {
                ProcessStringResponses();
                mState = 2;
                CleanupCall(true);
                unk54->Release();
            }
        } else {
            mState = 4;
            CleanupCall(true);
            unk54->Release();
        }
    }
    return true;
}

BEGIN_HANDLERS(WiiEntityUploader)
    HANDLE_MESSAGE(DWCProfanityResultMsg)
    HANDLE_SUPERCLASS(EntityUploader)
    HANDLE_CHECK(0x256)
END_HANDLERS