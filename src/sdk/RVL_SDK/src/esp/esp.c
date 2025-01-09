#include <revolution/ESP.h>

static s32 __esFd = -1;

s32 ESP_InitLib(void) {
    s32 ret = 0;

    if (__esFd < 0) {
        __esFd = IOS_Open("/dev/es", 0);

        if (__esFd < 0) {
            ret = __esFd;
        }
    }

    return ret;
}

s32 ESP_CloseLib(void) {
    s32 ret = 0;

    if (__esFd >= 0) {
        ret = IOS_Close(__esFd);
        if (ret == 0) {
            __esFd = -1;
        }
    }

    return ret;
}

//unused
void ESP_ImportTicket(){
}

//unused
void ESP_ImportTitleInit(){
}

//unused
void ESP_ImportContentBegin(){
}

//unused
void ESP_ImportContentData(){
}

//unused
void ESP_ImportContentEnd(){
}

//unused
void ESP_ImportTitleDone(){
}

//unused
void ESP_ImportTitleCancel(){
}

s32 ESP_LaunchTitle(u64 titleID, ESTicketView *pTicketView) {
    s32 ret = 0;
    // buffer being aligned is required for codegen
    u8 buf[256] ALIGN(32);
    IPCIOVector* vec = (IPCIOVector *)(buf + 208);
    u64* id = (u64*)buf;

    if (__esFd < 0) {
        return -0x3F9;
    }
    
    // check if ptr is aligned to 0x20
    if ((u32)pTicketView & 31) {
        return -0x3F9;
    }

    *id = titleID;
    // this seems to be two vector instances in an array, considering they are accessed via stack at 0xF0, 0xF4, 0xF8, and 0xFC
    vec[0].base = (u8*)id;
    vec[0].length = 8;
    vec[1].base = (u8*)pTicketView;
    vec[1].length = 0xD8;

    ret = IOS_IoctlvReboot(__esFd, 8, 2, 0, vec);
    __esFd = -1;
    return ret;
}

//unused
void ESP_OpenContentFile(){
}

//unused
void ESP_OpenTitleContentFile(){
}

//unused
void ESP_ReadContentFile(){
}

//unused
void ESP_SeekContentFile(){
}

//unused
void ESP_CloseContentFile(){
}

//unused
void ESP_ListOwnedTitles(){
}

//unused
void ESP_ListTitlesOnCard(){
}

//unused
void ESP_ListTitleContentsOnCard(){
}

//unused
void ESP_ListTmdContentsOnCard(){
}

s32 ESP_GetTicketViews(ESTitleId titleId, ESTicketView* ticketViewList, u32* ticketViewCnt) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));
    ESTitleId* p1 = (ESTitleId*)__esBuf;
    u32* p2 = (u32*)(__esBuf + 32);

    if (__esFd < 0 || ticketViewCnt == (u32*)NULL) {
        rv = -1017;
        goto out;
    }

    if (((u32)ticketViewList & 31)) {
        rv = -1017;
        goto out;
    }

    *p1 = titleId;
    if (ticketViewList == (ESTicketView*)NULL) {
        v[0].base = (u8*)p1;
        v[0].length = sizeof(ESTitleId);
        v[1].base = (u8*)p2;
        v[1].length = 4;
        rv = IOS_Ioctlv(__esFd, 18, 1, 1, v);

        if (rv == 0) {
            *ticketViewCnt = *p2;
        }
    } else {
        if (*ticketViewCnt == 0) {
            rv = -1017;
            goto out;
        }

        *p2 = *ticketViewCnt;
        v[0].base = (u8*)p1;
        v[0].length = sizeof(ESTitleId);
        v[1].base = (u8*)p2;
        v[1].length = 4;
        v[2].base = (u8*)ticketViewList;
        v[2].length = sizeof(ESTicketView)*(*ticketViewCnt);
        rv = IOS_Ioctlv(__esFd, 19, 2, 1, v);
    }

out:
    return rv;
}

s32 ESP_DiGetTicketView(const void* ticket, ESTicketView* ticketView) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));

    if (__esFd < 0 || ticketView == (ESTicketView*)NULL) {
        rv = -1017;
        goto out;
    }

    if (((u32)ticket & 31) || ((u32)ticketView & 31)) {
        rv = -1017;
        goto out;
    }

    v[0].base = (u8*)ticket;

    if (ticket == (ESTicketView*)NULL) {
        v[0].length = 0;
    } else {
        v[0].length = sizeof(ESTicket);
    }

    v[1].base = (u8*)ticketView;
    v[1].length = sizeof(ESTicketView);
    rv = IOS_Ioctlv(__esFd, 27, 1, 1, v);

out:
    return rv;
}

s32 ESP_DiGetTmd(ESTitleMeta* tmd, u32* tmdSize) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));
    u32* p1 = (u32*)__esBuf;

    if (__esFd < 0 || tmdSize == (u32*)NULL) {
        rv = -1017;
        goto out;
    }

    if (((u32)tmd & 31)) {
        rv = -1017;
        goto out;
    }

    if (tmd == (ESTitleMeta*)NULL) {
        v[0].base = (u8*)p1;
        v[0].length = 4;
        rv = IOS_Ioctlv(__esFd, 57, 0, 1, v);

        if (rv == 0) {
            *tmdSize = *p1;
        }
    } else {
        if (*tmdSize == 0) {
            rv = -1017;
            goto out;
        }

        *p1 = *tmdSize;
        v[0].base = (u8*)p1;
        v[0].length = 4;
        v[1].base = (u8*)tmd;
        v[1].length = *tmdSize;
        rv = IOS_Ioctlv(__esFd, 58, 1, 1, v);
    }

out:
    return rv;
}

//unused
void ESP_GetTmd(){
}

//unused
void ESP_GetTmdSize(){
}

//unused
s32 ESP_GetTmdView(ESTitleId titleId, ESTmdView* tmdView, u32* size) {
}

s32 ESP_GetDataDir(ESTitleId titleId, char* dataDir) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));
    ESTitleId* p1 = (ESTitleId*)__esBuf;

    if (__esFd < 0 || dataDir == (char*)NULL) {
        rv = -1017;
        goto out;
    }

    if (((u32)dataDir & 31)) {
        rv = -1017;
        goto out;
    }

    *p1 = titleId;
    v[0].base = (u8*)p1;
    v[0].length = sizeof(ESTitleId);
    v[1].base = (u8*)dataDir;
    v[1].length = 0x1E;
    rv = IOS_Ioctlv(__esFd, 29, 1, 1, v);

out:
    return rv;
}

s32 ESP_GetTitleId(ESTitleId* titleId) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));

    if (__esFd < 0 || titleId == (ESTitleId*)NULL) {
        rv = -1017;
        goto out;
    }

    v[0].base = __esBuf;
    v[0].length = sizeof(ESTitleId);

    rv = IOS_Ioctlv(__esFd, 32, 0, 1, v);

    if (rv == 0) {
        *titleId = *(ESTitleId*)__esBuf;
    }

out:
    return rv;
}

//unused
void ESP_GetDeviceId(){
}

s32 ESP_GetConsumption(ESTicketId ticketId, ESLpEntry* entries, u32* nEntries) {
    s32 rv = 0;
    u8 __esBuf[256] ALIGN(32);
    IPCIOVector* v = (IPCIOVector *)(__esBuf + 256 - 6 * sizeof(IPCIOVector));
    ESTicketId* p1 = (ESTicketId*)__esBuf;
    u32* p2 = (u32*)(__esBuf + 32);

    if (__esFd < 0) {
        rv = -1017;
        goto out;
    }

    if (((u32)entries & 31)) {
        rv = -1017;
        goto out;
    }

    *p1 = ticketId;
    v[0].base = (u8*)p1;
    v[0].length = sizeof(ESTicketId);

    if (entries == (ESLpEntry*)NULL) {
        v[1].base = NULL;
        v[1].length = 0;
    } else {
        v[1].base = (u8*)entries;
        v[1].length = sizeof(ESLpEntry) * (*nEntries);
        *p2 = *nEntries;
    }

    v[2].base = (u8*)p2;
    v[2].length = 4;
    rv = IOS_Ioctlv(__esFd, 22, 1, 2, v);
    *nEntries = *p2;
out:
    return rv;
}

//unused
void ESP_GetDeviceCert(){
}

//unused
void ESP_Encrypt(){
}

//unused
void ESP_Decrypt(){
}

//unused
void ESP_Sign(){
}

//unused
void ESP_VerifySign(){
}

//unused
void ESP_DeleteTitleContent(){
}

//unused
void ESP_DeleteContent(){
}

//unused
void ESP_ExportTitleInit(){
}

//unused
void ESP_ExportContentBegin(){
}

//unused
void ESP_ExportContentData(){
}

//unused
void ESP_ExportContentEnd(){
}

//unused
void ESP_ExportTitleDone(){
}

//unused
void ESP_GetTicket(){
}