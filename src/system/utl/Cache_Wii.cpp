#include "Cache_Wii.h"
#include "VF.h"
#include "system/os/ThreadCall.h"


CacheIDWii::CacheIDWii() {
}

CacheIDWii::~CacheIDWii() {}

const char* CacheIDWii::GetCachePath(const char* param_1) {
    if (mStrCacheName.empty()) {
        TheDebug.Fail(FormatString("CacheID::GetCachePath() - mStrCacheName is empty.").Str());
    }

    if (param_1 == NULL) {
        return MakeString("%s/", mStrCacheName.c_str());
    } else {
        String a = param_1;
        a.ReplaceAll('\\','/');
        if (a[0] == '/') {
            a.erase(0, 1);
        }
        return a.c_str();
    }
}

const char* CacheIDWii::GetCacheSearchPath(const char* param_1) {
    if (mStrCacheName.c_str() == '\0') {
        TheDebug.Fail(FormatString("CacheID::GetCacheSearchPath() - mStrCacheName is empty.\n").Str());
    }
    if (param_1 == 0x0) {
        return MakeString("%s", param_1);
    } else {
        return GetCachePath(param_1);
    }
}

CacheWii::CacheWii(const CacheIDWii& param_1) {
    m0x14 = String(param_1.mStrCacheName);
    m0x20 = String(param_1.m0x10);
    m0x2c = String(param_1.m0x1c);
    m0x38 = param_1.m0x28;
    // m0x3c = String();
    // m0x48 = String();
    m0x54 = 0;
    m0x58 = 0;
    m0x5c = 0;
    m0x60 = 0;
    m0x64 = "A:/DLC";
    m0x68 = "MSTORE.vff";
    m0x6c = "A";

    bool result = VFMountDriveNANDFlash();
    if (result != 0) {
        TheDebug.Notify(FormatString("Can't mount nand drive.").Str());
    } else {
        int dirResult = VFCreateDir(m0x64);
        if (dirResult != 0 && dirResult != 0x11) {
            const char* error = VFGetApiErrorString();
            OSReport("VFCreateDir vfErr %s Line %d\n", error, 0x5d);
        }
        dirResult = VFChangeDir(m0x64);
        if (dirResult != 0) {
            const char* error = VFGetApiErrorString();
            OSReport("VFChangeDir vfErr %s Line %d\n", error, 0x67);
        }
    }
}

CacheWii::~CacheWii() {
    int result = VFUnmountDrive(drive);
    if (result == 0) {

    } else {
        TheDebug.Notify(FormatString("Can't unmount nand drive.").Str());
    }
}

const char* CacheWii::GetCacheName() {
    return m0x14.c_str();
}

void CacheWii::Poll() {}

bool CacheWii::IsConnectedSync() {
    return true;
}

int CacheWii::GetFreeSpaceSync(unsigned long long* param_1) {
    *param_1 = VFGetDriveFreeSize(m0x6c);
    mLastResult = kCache_NoError;
    return true;
}

bool CacheWii::DeleteSync(const char* param_1) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (!param_1) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    }
    m0x20 = String(m0x64) + "/" + m0x2c;
    int iVar1 = VFDeleteFile(m0x20.c_str());
    if (iVar1 != 0 && iVar1 != 2) {
        TheDebug.Notify(MakeString("Couldn't delete file %s", m0x20.c_str()));
    }
    mOpCur = kOpNone;
    return true;
}

bool CacheWii::GetDirectoryAsync(const char*, std::vector<CacheDirEntry>* param_2, Hmx::Object*) {
    bool isDone = IsDone();
    if (!isDone) {
        return false;
    } else if (param_2 == NULL) {
        return false;
    } else {
        MILO_ASSERT(s_mThreadStr.empty(), 0xc2);

        MILO_ASSERT(s_mCacheDirList == NULL, 0xc5);

        s_mCacheDirList = param_2;
        mLastResult = kCache_NoError;
        mOpCur = kOpDirectory;
        return true;
    }
}

bool CacheWii::GetFileSizeAsync(const char* param_1, unsigned int* param_2, Hmx::Object*) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (param_2 == 0) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    } else {
        s_mThreadStr = m0x10->GetCachePath(param_1);
        m0x54 = param_2;
        mLastResult = kCache_NoError;
        mOpCur = kOpFileSize;
        return true;
    }
}

bool CacheWii::ReadAsync(const char* param_1, void* param_2, uint param_3, Hmx::Object* param_4) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (param_1 == NULL || param_2 == NULL || param_3 == NULL) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    } else {
        s_mThreadStr = m0x10->GetCachePath(param_1);
        m0x54 = param_2;
        m0x58 = param_3;
        mLastResult = kCache_NoError;
        mOpCur = kOpFileSize;
        return true;
    }
}

bool CacheWii::WriteAsync(const char*, void*, uint, Hmx::Object*) {

}

bool CacheWii::DeleteAsync(const char* param_1, Hmx::Object*) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (param_1 == NULL) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    } else {
        s_mThreadStr = m0x10->GetCachePath(param_1);
        mLastResult = kCache_NoError;
        mOpCur = kOpDelete;
        return true;
    }
}

int CacheWii::ThreadStart() {
    MILO_ASSERT(!IsDone(), 0x14b);

    switch (mOpCur) {
        case kOpDirectory: {
            m0x2c = m0x64;
            m0x2c = m0x2c + "/" + m0x2c;
            return ThreadGetDir(m0x2c);
        }
        case kOpFileSize:
            return ThreadGetFileSize();
        case kOpWrite:
            return ThreadWrite();
        case kOpRead:
            return ThreadRead();
        case kOpDelete:
            return ThreadDelete();
        default:
            MILO_ASSERT(false, 0x00);
            return 0;
    }
}

void CacheWii::ThreadDone(int param_1) {
    MILO_ASSERT(!IsDone(), 0x00);

    switch (mOpCur) {
        case kOpDirectory: {
            mLastResult = (CacheResult)param_1;
            s_mThreadStr = gNullStr;
            m0x5c = 0;
            m0x60 = 0;
            break;
        }
        case kOpFileSize: {
            mLastResult = (CacheResult)param_1;
            s_mThreadStr = gNullStr;
            m0x54 = 0;
            m0x60 = 0;
            break;
        }
        case kOpRead: {
            mLastResult = (CacheResult)param_1;
            s_mThreadStr = gNullStr;
            m0x54 = 0;
            m0x58 = 0;
            m0x60 = 0;
            break;
        }
        case kOpWrite: {
            mLastResult = (CacheResult)param_1;
            s_mThreadStr = gNullStr;
            m0x54 = 0;
            m0x58 = 0;
            if (m0x60 != 0) {
            }
            break;
        }
        case kOpDelete: {
            mLastResult = (CacheResult)param_1;
            s_mThreadStr = gNullStr;
            m0x60 = 0;
            break;
        }
        default: {
            MILO_ASSERT(false, 0x110);
        }
    }
    mOpCur = kOpNone;
}

int CacheWii::ThreadGetDir(String) {}

int CacheWii::ThreadGetFileSize() {
    m0x20 = m0x64;
    m0x20 = m0x20 + "/" + m0x2c;
    int result = VFGetFileSize(m0x20.c_str());
    if (result == -1) {
        return -1;
    } else {
        return 0;
    }
}

int CacheWii::ThreadRead() {
    char* fileName = "";
    void* file = VFOpenFile(fileName, "", 0);
    if (file == NULL) {
        TheDebug.Notify(MakeString("Couldn't open file %s", fileName));
        return -1;
    } else {
        int fileSize = VFGetFileSizeByFd(NULL);
        if (fileSize == -1 || (fileSize = VFReadFile(file, m0x54, fileSize, 0))) {
            if (fileSize == 0) {
                TheDebug.Notify(MakeString("Couldn't close the file pointer %s", fileName));
            }
            return 0;
        } else {
            TheDebug.Notify(MakeString("Couldn't read file %s", fileName));
            VFCloseFile(file);
            return -1;
        }
    }
}

int CacheWii::ThreadWrite() {
    String fileName = m0x100 + "1" + "2";
    void* file = VFOpenFile(fileName.c_str(), "", 0);
    if (file == 0 && (file = VFCreateFile(fileName.c_str(), 0), file == 0)) {

    } else {
        int returnValue = 0;
        int result = VFWriteFile(file, m0x54, m0x58);
        if (result != 0) {
            TheDebug.Notify(MakeString("Couldn't write file %s\n", fileName));
            returnValue = -1;
        }
        result = VFFileSync(file);
        if (result != 0) {
            TheDebug.Notify(MakeString("Can't sync file", fileName));
            returnValue = -1;
        }
        result = VFCloseFile(file);
        if (result != 0) {
            TheDebug.Notify(MakeString("Couldn't close the file pointer to file %s\n", fileName));
        }
    }
}

int CacheWii::ThreadDelete() {
    const char* file = (m0x20 + m0x38 + m0x2c + m0x64).c_str();

    int result = VFDeleteFile(file);
    if ((result == 0) || (result == 2)) {
        return 0;
    } else {
        TheDebug.Notify(MakeString("Couldn't delete file %s", file));
        return -1;
    }
}
