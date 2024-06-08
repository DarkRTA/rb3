#include "Cache_Wii.h"
#include "VF.h"

const char* unusedStrings[] = {
    "CacheID::GetCachePath() - mStrCacheName is empty.\n",
    "%s/", 
    "%s"
};

CacheIDWii::CacheIDWii() {
    // unk2 = String().c_str();
}

CacheIDWii::~CacheIDWii() {}

const char* CacheIDWii::GetCachePath(const char* param_1) {
    const char* pcVar1;

    if (param_1 == 0x00) {
        pcVar1 = MakeString("");
    } else {
        String a = String(param_1);
        a.ReplaceAll('\\','/');
        pcVar1 = (char*)a[0];

    }

}

const char* CacheIDWii::GetCacheSearchPath(const char* param_1) {
    if (unk1.c_str() == '\0') {
        TheDebug.Fail(FormatString("CacheID::GetCacheSearchPath() - mStrCacheName is empty.\n").Str());
    }
    if (param_1 == 0x0) {

    } else {
        return unk1.c_str();
    }
}

const char* unusedStrings3[] = {
    "A:/DLC", 
    
    "A", 
    "Can't mount nand drive.", 
     
    
};

CacheWii::CacheWii(const CacheIDWii& param_1) {
    m0x14 = param_1.unk1;
    mCacheName = param_1.unk2;
    m0x2c = param_1.unk3;
    m0x38 = param_1.unk4;
    s_mCacheDirList = new std::vector<CacheDirEntry>();

    m0x68 = "MSTORE.vff";

    bool result = VFMountDriveNANDFlashEx("", "");
    if (!result) {
        int dirResult = VFCreateDir(""); // should be 0x100
        if (dirResult != 0 && dirResult != 0x11) {
            const char* error = VFGetApiErrorString();
            OSReport("VFCreateDir vfErr %s Line %d\n", error, 0x5d);
        }
        dirResult = VFChangeDir(""); 
        if (dirResult != 0) {
            const char* error = VFGetApiErrorString();
            OSReport("VFChangeDir vfErr %s Line %d\n", error, 0x67);
        }
    } else {
        TheDebug.Notify("Can't unmount nand drive.");
    }
}

CacheWii::~CacheWii() {}

const char* CacheWii::GetCacheName() {
    return mCacheName.c_str();
}

void CacheWii::Poll() {}

bool CacheWii::IsConnectedSync() {
    return true;
}

int CacheWii::GetFreeSpaceSync(unsigned long long* param_1) {
    // int iVar1 = VFGetDriveFreeSize(0x6c);
    return 1;
}

bool CacheWii::DeleteSync(const char* param_1) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (param_1) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    } else {
        String file = "";
        file = file + "1" + "2";
        int iVar1 = VFDeleteFile(file.c_str());
        if (iVar1 != 0 && iVar1 != 2) {
            TheDebug.Notify(MakeString("Couldn't delete file %s", file));
        }
        return true;
    }
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

bool CacheWii::GetFileSizeAsync(const char*, unsigned int*, Hmx::Object*) {}

bool CacheWii::ReadAsync(const char*, void*, uint, Hmx::Object*) {}

bool CacheWii::WriteAsync(const char*, void*, uint, Hmx::Object*) {}

bool CacheWii::DeleteAsync(const char* i, Hmx::Object*) {
    bool isDone = IsDone();
    if (!isDone) {
        mLastResult = kCache_ErrorBusy;
        return false;
    } else if (i == NULL) {
        mLastResult = kCache_ErrorBadParam;
        return false;
    } else {
        
        mLastResult = kCache_NoError;
        return true;
    }
}

const char* unusedStrings4[] = {
    "mThreadStr.empty()",
    "mCacheDirList == NULL", 
    "cache_write_result", 
};

int CacheWii::ThreadStart() {
    MILO_ASSERT(!IsDone(), 0x14b);

    switch (mOpCur) {
        case kOpDirectory:
        break;
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

void CacheWii::ThreadDone(int) {
    MILO_ASSERT(!IsDone(), 0x00);

    switch (mOpCur) {
        case kOpDirectory:
        s_mThreadStr = gNullStr;
        break;
        case kOpFileSize:
        s_mThreadStr = gNullStr;
        break;
        case kOpRead:
        s_mThreadStr = gNullStr;
        break;
        case kOpWrite:
        s_mThreadStr = gNullStr;
        break;
        case kOpDelete:
        s_mThreadStr = gNullStr;
        break;
        default:
        MILO_ASSERT(false, 0x110);
    }
    mOpCur = kOpNone;
}

int CacheWii::ThreadGetDir(String) {}
int CacheWii::ThreadGetFileSize() {}
int CacheWii::ThreadRead() {}

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
    char* local_18;
    int result = VFDeleteFile(local_18);
    if ((result == 0) || (result == 2)) {

        return 0;
    } else {
        TheDebug.Notify(MakeString("Couldn't delete file %s", local_18));
        return -1;
    }
}

const char* unusedStrings2[] = {
    "VFFileSearch: %s\n", 
    "VFFileSearch: recurse into %s\n", 
    "VFFileSearch: Adding file %s\n", 
    "VFFileSearch: %d\n", 
    "r", 
    "Couldn't open file %s\n", 
    "Couldn't read file %s\n",
    "r+", 
    "Couldn't create file %s\n", 
    
};