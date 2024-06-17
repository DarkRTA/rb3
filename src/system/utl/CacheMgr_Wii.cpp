#include "CacheMgr_Wii.h"
#include "Cache_Wii.h"
#include "VF.h"

const char* unusedStrings[] = {
    "A", 
    "Can't delete system file.", 
    "Not enough NAND available for VF.", 
    "Can't create sytem file.", // Intentional typo
    "Can't mount nand drive.", 
    "Can't format nand drive", 
    "Can't unmount nand drive.", 
};

CacheMgrWii::CacheMgrWii() : mVar1(), mVar2(0), mVar3(0), mVar4(0), mVar5(0) {
    CreateVFCache();
}

void CacheMgrWii::CreateVFCache() {
    VFInitEx();
    bool result = VFMountDriveNANDFlashEx("", "");
    
}

CacheMgrWii::~CacheMgrWii() {
    
}

void CacheMgrWii::Poll() {
    CacheMgr::OpType op = GetOp();
    if (op != 0) {
        switch(op) {
            case 1:
            PollSearch();
            break;
            case 3:
            PollMount();
            break;
            case 4:
            PollUnmount();
            break;
            default:
            TheDebug.Fail(FormatString("Unknown OpType encountered in CacheMgr::Poll()\n").Str());
            break;
        }
    }
}

const char* unusedStrings2[] = {
    "\n"
    
};

bool CacheMgrWii::SearchAsync(const char* param_1, CacheID** param_2) {
    if (!IsDone()) {
        SetLastResult(kCache_ErrorBusy);
    } else {
        if (param_2 != NULL && (*param_2) != NULL) {
            SetLastResult(kCache_ErrorBadParam);
            return true;
        }
        TheDebug << "SearchAsync BAD PARAM: mStrCacheName is empty\n";

        if (param_2 != NULL) {
            TheDebug << MakeString(", *ppCacheID = 0x%X", param_2);
        }
        TheDebug << "";
        SetLastResult(kCache_NoError);
        return true;
    }
    TheDebug << MakeString("SearchAsync BAD PARAM: ppCacheID = 0x%X", param_2);
    if (param_2 != NULL) {
        TheDebug << MakeString(", *ppCacheID = 0x%X", param_2);
    }
    SetLastResult(kCache_ErrorBadParam);

    return false;
}

bool CacheMgrWii::CreateCacheID(const char* param_1, const char* param_2, const char* param_3, const char* param_4, const char* param_5, int param_6, CacheID** param_7) {
    if (param_2 == 0 || param_4 == 0) {
        SetLastResult(kCache_ErrorBadParam);
        return false;
    } else  {
        CacheIDWii* id = new CacheIDWii();
        id->unk2 = param_2;
        id->unk3 = param_4;
        id->unk4 = param_6;
        return true;
    }
}

bool CacheMgrWii::MountAsync(CacheID*, Cache*, Hmx::Object*) {}
bool CacheMgrWii::UnmountAsync(Cache**, Hmx::Object*) {}
bool CacheMgrWii::DeleteAsync(CacheID*) {}
void CacheMgrWii::PollSearch() {}
void CacheMgrWii::EndSearch(CacheResult) {}

void CacheMgrWii::PollMount() {

}

void CacheMgrWii::PollUnmount() {

}
