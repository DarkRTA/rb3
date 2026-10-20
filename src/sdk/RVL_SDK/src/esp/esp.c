#include "revolution/esp/esp.h"
#include <revolution/ESP.h>

static s32 __esFd = -1;

// Thank you Wii Menu Decomp
#define DECLARE_ES_WORK u8 __esBuf[256] ALIGN(32)
#define AT_ES_WORK(x) (__esBuf + x)

#define IS_ALIGNED(x) (((u32)(x) & 31) == 0)
#define IS_ALIGNED64(x) (((u32)(x) & 63) == 0)

enum {
    ES_IOCTLV_IMPORT_TICKET = 1,
    ES_IOCTLV_IMPORT_TITLE_INIT = 2,
    ES_IOCTLV_IMPORT_CONTENT_BEGIN = 3,
    ES_IOCTLV_IMPORT_CONTENT_DATA = 4,
    ES_IOCTLV_IMPORT_CONTENT_END = 5,
    ES_IOCTLV_IMPORT_TITLE_DONE = 6,
    ES_IOCTLV_GET_DEVICE_ID = 7,
    ES_IOCTLV_LAUNCH_TITLE = 8,
    ES_IOCTLV_OPEN_CONTENT = 9,
    ES_IOCTLV_READ_CONTENT = 10,
    ES_IOCTLV_CLOSE_CONTENT = 11,
    ES_IOCTLV_LIST_OWNED_TITLES = 12,
    ES_IOCTLV_LIST_OWNED_TITLES_WITH_COUNT = 13,
    ES_IOCTLV_LIST_TITLES_ON_CARD = 14,
    ES_IOCTLV_LIST_TITLES_ON_CARD_WITH_COUNT = 15,
    ES_IOCTLV_LIST_TITLE_CONTENTS = 16,
    ES_IOCTLV_LIST_TITLE_CONTENTS_WITH_COUNT = 17,
    ES_IOCTLV_GET_TICKET_VIEWS = 18,
    ES_IOCTLV_GET_TICKET_VIEWS_WITH_COUNT = 19,
    ES_IOCTLV_GET_TMDVIEW = 20,
    ES_IOCTLV_GET_TMDVIEW_WITH_SIZE = 21,
    ES_IOCTLV_GET_CONSUMPTION = 22,
    ES_IOCTLV_DELETE_TITLE = 23,
    ES_IOCTLV_DELETE_TICKET = 24,
    ES_IOCTLV_GET_DVD_TMDVIEW = 25,
    ES_IOCTLV_GET_DVD_TMDVIEW_WITH_SIZE = 26,
    ES_IOCTLV_GET_DATA_DIR = 29,
    ES_IOCTLV_GET_DVD_TICKET_VIEW = 27,
    ES_IOCTLV_GET_DEVICE_CERT = 30,
    ES_IOCTLV_IMPORT_BOOT = 31,
    ES_IOCTLV_GET_TITLE_ID = 32,
    ES_IOCTLV_SET_UID = 33,
    ES_IOCTLV_DELETE_TITLE_CONTENT = 34,
    ES_IOCTLV_SEEK_CONTENT = 35,
    ES_IOCTLV_OPEN_TITLE_CONTENT_FILE = 36,
    ES_IOCTLV_EXPORT_TITLE_INIT = 38,
    ES_IOCTLV_EXPORT_CONTENT_BEGIN = 39,
    ES_IOCTLV_EXPORT_CONTENT_DATA = 40,
    ES_IOCTLV_EXPORT_CONTENT_END = 41,
    ES_IOCTLV_EXPORT_TITLE_DONE = 42,
    ES_IOCTLV_IMPORT_TITLE_INIT_ALT = 43,
    ES_IOCTLV_ENCRYPT = 44,
    ES_IOCTLV_DECRYPT = 45,
    ES_IOCTLV_GET_BOOT2_VERSION = 46,
    ES_IOCTLV_IMPORT_TITLE_CANCEL = 47,
    ES_IOCTLV_SIGN = 48,
    ES_IOCTLV_VERIFY_SIGN = 49,
    ES_IOCTLV_LIST_TMD_CONTENTS_CARD = 50,
    ES_IOCTLV_LIST_TMD_CONTENTS_CARD_WITH_COUNT = 51,
    ES_IOCTLV_GET_TMD = 52,
    ES_IOCTLV_GET_TMD_WITH_SIZE = 53,
    ES_IOCTLV_LIST_SHARED_CONTENTS = 54,
    ES_IOCTLV_LIST_SHARED_CONTENTS_WITH_COUNT = 55,
    ES_IOCTLV_GET_DVD_TMD = 57,
    ES_IOCTLV_GET_DVD_TMD_WITH_COUNT = 58,
    ES_IOCTLV_DELETE_CONTENT = 62,
    ES_IOCTLV_VERIFY_NEW_COMMON_KEY = 69,
};

inline ESError ES_GetTmdSize(ESTitleMeta* tmd, u32* tmdSize) {
    ESError ret = ES_ERR_OK;

    if (tmd == NULL) {
        ret = ES_ERR_INVALID;
        goto out;
    }

    *tmdSize = tmd->head.numContents * 0x24 + 0x1E4 /* todo: figure these out. */;

out:
    return ret;
}

ESError ESP_InitLib() {
    ESError ret = ES_ERR_OK;

    // Already initialized? Get out.
    if (__esFd >= 0) {
        goto out;
    }

    __esFd = IOS_Open("/dev/es", 0);

    // Failed? Return error code
    if (__esFd < ES_ERR_OK) {
        ret = __esFd;
    }

out:
    return ret;
}

ESError ESP_CloseLib(void) {
    s32 ret = 0;

    if (__esFd >= 0) {
        ret = IOS_Close(__esFd);
        if (ret == 0) {
            __esFd = -1;
        }
    }

    return ret;
}

ESError ESP_ImportTicket(ESTicket* ticket, void* certs, u32 certSize, void* crls, u32 crlSize, int unknown) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret = ES_ERR_OK;

    if (ticket == NULL || certs == NULL || certSize == 0) {
        ret = ES_ERR_INVALID;
        goto out;
    }

    if (!IS_ALIGNED(ticket) || !IS_ALIGNED(certs) || !IS_ALIGNED(crls)) {
        ret = ES_ERR_INVALID;
        goto out;
    }

    if (__esFd < 0) {
        ret = ES_ERR_INVALID;
        goto out;
    }

    vec[0].base = ticket;
    vec[0].length = sizeof(ESTicket);

    vec[1].base = certs;
    vec[1].length = certSize;

    vec[2].base = crls;
    vec[2].length = crlSize;

    if (unknown == 0) {
        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_TICKET, 3, 0, vec);
        goto out;
    }

    ret = ES_ERR_INVALID_UNKNOWN;

out:
    return ret;
}

ESError ESP_ImportTitleInit(void* tmd, u32 tmdSize, void* certs, u32 certSize, void* crls, u32 crlSize, int unknown0, int unknown1) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    int* pUnknown = (int*)AT_ES_WORK(0x00);

    ESError ret;

    if (!IS_ALIGNED(tmd) || !IS_ALIGNED(certs) || !IS_ALIGNED(crls)) {
        return ES_ERR_INVALID;
    }

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    switch (unknown0) {
        case 0: {
            if (tmd == NULL || tmdSize == 0 || certs == NULL || certSize == 0) {
                return ES_ERR_INVALID;
            }
            *pUnknown = unknown1;

            vec[0].base = tmd;
            vec[0].length = tmdSize;

            vec[1].base = certs;
            vec[1].length = certSize;

            vec[2].base = crls;
            vec[2].length = crlSize;

            vec[3].base = pUnknown;
            vec[3].length = sizeof(*pUnknown);

            ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_TITLE_INIT, 4, 0, vec);
            return ret;
        }
        case 2: {
            u32 size;
            uint unk = 0;
            if (tmd == NULL) {
                return ES_ERR_INVALID;
            }
            ES_GetTmdSize(tmd, &size);
            if (tmdSize != size) {
                return ES_ERR_INVALID;
            }

            vec[0].base = tmd;
            vec[0].length = tmdSize;
            ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_TITLE_INIT_ALT, 1, 0, vec);
            return ret;
        }
        default: {
            return ES_ERR_INVALID_UNKNOWN;
        }
    }
}

ESFd ESP_ImportContentBegin(ESTitleId titleId, ESContentId contentId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    ESContentId* pContentId = (ESContentId*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    *pContentId = contentId;
    vec[1].base = pContentId;
    vec[1].length = sizeof(*pContentId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_CONTENT_BEGIN, 2, 0, vec);
    return ret;
}

ESError ESP_ImportContentData(ESFd fd, void* data, u32 dataSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESFd* pFd = (ESFd*)AT_ES_WORK(0x00);

    ESError ret;

    if (fd < 0 || data == NULL || dataSize == 0) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(data)) {
        return ES_ERR_INVALID;
    }

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    vec[1].base = data;
    vec[1].length = dataSize;

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_CONTENT_DATA, 2, 0, vec);
    return ret;
}

ESError ESP_ImportContentEnd(ESFd fd) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESFd* pFd = (ESFd*)AT_ES_WORK(0x00);

    ESError ret;

    if (fd < 0 || __esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_CONTENT_END, 1, 0, vec);
    return ret;
}

ESError ESP_ImportTitleDone() {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_TITLE_DONE, 0, 0, vec);
    return ret;
}

ESError ESP_ImportTitleCancel() {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_IMPORT_TITLE_CANCEL, 0, 0, vec);
    return ret;
}

ESError ESP_LaunchTitle(ESTitleId titleId, ESTicketView* ticket) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(ticket)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    vec[1].base = ticket;
    vec[1].length = sizeof(*ticket);

    ret = IOS_IoctlvReboot(__esFd, ES_IOCTLV_LAUNCH_TITLE, 2, 0, vec);

    // About to launch. Immediately abort file descriptor!!
    __esFd = -1;

    return ret;
}

ESFd ESP_OpenTitleContentFile(ESTitleId titleId, ESTicketView* ticketView, ESContentId contentIndex) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    ESContentId* pContentId = (ESContentId*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0 || !IS_ALIGNED(ticketView)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    *pContentId = contentIndex;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    vec[1].base = ticketView;
    vec[1].length = sizeof(*ticketView);

    vec[2].base = pContentId;
    vec[2].length = sizeof(*pContentId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_OPEN_TITLE_CONTENT_FILE, 3, 0, vec);
    return ret;
}

ESError ESP_ReadContentFile(ESFd fd, void* buffer, u32 size) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESFd* cFd = (ESFd*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || fd < 0 || buffer == NULL || size == 0) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(buffer)) {
        return ES_ERR_INVALID;
    }

    *cFd = fd;
    vec[0].base = cFd;
    vec[0].length = sizeof(*cFd);

    vec[1].base = buffer;
    vec[1].length = size;

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_READ_CONTENT, 1, 1, vec);
    return ret;
}

ESError ESP_SeekContentFile(ESFd fd, s32 offset, u32 whence) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    s32* pFd = (s32*)AT_ES_WORK(0x00);
    s32* pOffset = (s32*)AT_ES_WORK(0x20);
    u32* pWhence = (u32*)AT_ES_WORK(0x40);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    *pOffset = offset;
    vec[1].base = pOffset;
    vec[1].length = sizeof(*pOffset);

    *pWhence = whence;
    vec[2].base = pWhence;
    vec[2].length = sizeof(*pWhence);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_SEEK_CONTENT, 3, 0, vec);
    return ret;
}

ESError ESP_CloseContentFile(ESFd fd) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    s32* pFd = (s32*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || fd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_CLOSE_CONTENT, 1, 0, vec);
    return ret;
}

ESError ESP_ListOwnedTitles(ESTitleId* titleIds, u32* numTitles) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    u32* pNumTitles = (u32*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || numTitles == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(titleIds)) {
        return ES_ERR_INVALID;
    }

    if (titleIds == NULL) {
        vec[0].base = pNumTitles;
        vec[0].length = sizeof(*pNumTitles);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_OWNED_TITLES, 0, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *numTitles = *pNumTitles;
        }
        return ret;
    } else if (*numTitles == 0) {
        return ES_ERR_INVALID;
    } else {
        *pNumTitles = *numTitles;

        vec[0].base = pNumTitles;
        vec[0].length = sizeof(*pNumTitles);

        vec[1].base = titleIds;
        vec[1].length = *numTitles * sizeof(*titleIds);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_OWNED_TITLES_WITH_COUNT, 1, 1, vec);
        return ret;
    }
}

ESError ESP_ListTitlesOnCard(ESTitleId* titleIds, u32* numTitles) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    u32* pNumTitles = (u32*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || numTitles == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(titleIds)) {
        return ES_ERR_INVALID;
    }

    if (titleIds == NULL) {
        vec[0].base = pNumTitles;
        vec[0].length = sizeof(*pNumTitles);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TITLES_ON_CARD, 0, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *numTitles = *pNumTitles;
        }
        return ret;
    } else if (*numTitles == 0) {
        return ES_ERR_INVALID;
    } else {
        *pNumTitles = *numTitles;

        vec[0].base = pNumTitles;
        vec[0].length = sizeof(*pNumTitles);

        vec[1].base = titleIds;
        vec[1].length = *numTitles * sizeof(*titleIds);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TITLES_ON_CARD_WITH_COUNT, 1, 1, vec);
        return ret;
    }
}

ESError ESP_ListTitleContentsOnCard(ESTitleId titleId, ESContentId* contentIds, u32* numContents) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    u32* pNumContents = (u32*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0 || numContents == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(contentIds)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    if (contentIds == NULL) {
        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pNumContents;
        vec[1].length = sizeof(*pNumContents);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TITLE_CONTENTS, 1, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *numContents = *pNumContents;
        }
        return ret;
    } else if (*numContents == 0) {
        return ES_ERR_INVALID;
    } else {
        *pNumContents = *numContents;

        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pNumContents;
        vec[1].length = sizeof(*pNumContents);

        vec[2].base = contentIds;
        vec[2].length = *numContents * sizeof(*contentIds);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TITLE_CONTENTS_WITH_COUNT, 2, 1, vec);
        return ret;
    }
}

ESError ESP_ListTmdContentsOnCard(ESTitleMeta* tmd, u32 tmdSize, ESContentId* contentIds, u32* numContents) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    u32* pNumContents = (u32*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || tmd == NULL || tmdSize == 0 || tmdSize > sizeof(ESTitleMeta) || numContents == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(tmd) || !IS_ALIGNED(contentIds)) {
        return ES_ERR_INVALID;
    }

    if (contentIds == NULL) {
        vec[0].base = tmd;
        vec[0].length = tmdSize;

        vec[1].base = pNumContents;
        vec[1].length = sizeof(*pNumContents);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TMD_CONTENTS_CARD, 1, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *numContents = *pNumContents;
        }
        return ret;
    } else if (*numContents == 0) {
        return ES_ERR_INVALID;
    } else {
        *pNumContents = *numContents;

        vec[0].base = tmd;
        vec[0].length = tmdSize;

        vec[1].base = pNumContents;
        vec[1].length = sizeof(*pNumContents);

        vec[2].base = contentIds;
        vec[2].length = *numContents * sizeof(*contentIds);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_LIST_TMD_CONTENTS_CARD_WITH_COUNT, 2, 1, vec);
        return ret;
    }
}

ESError ESP_GetTicketViews(ESTitleId titleId, ESTicketView* ticketViewList, u32* numTicketViews) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    u32* pNumTicketViews = (u32*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0 || numTicketViews == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(ticketViewList)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    if (ticketViewList == NULL) {
        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pNumTicketViews;
        vec[1].length = sizeof(*pNumTicketViews);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TICKET_VIEWS, 1, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *numTicketViews = *pNumTicketViews;
        }
        return ret;
    } else if (*numTicketViews == 0) {
        return ES_ERR_INVALID;
    } else {
        *pNumTicketViews = *numTicketViews;

        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pNumTicketViews;
        vec[1].length = sizeof(*pNumTicketViews);

        vec[2].base = ticketViewList;
        vec[2].length = *numTicketViews * sizeof(*ticketViewList);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TICKET_VIEWS_WITH_COUNT, 2, 1, vec);
        return ret;
    }
}

ESError ESP_DiGetTicketView(const void *ticket,  ESTicketView *ticketView) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector *)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0 || ticketView == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(ticket) || !IS_ALIGNED(ticketView)) {
        return ES_ERR_INVALID;
    }

    vec[0].base = (void *)ticket;
    if (ticket == NULL) {
        vec[0].length = 0;
    } else {
        vec[0].length = sizeof(ESTicket);
    }

    vec[1].base = ticketView;
    vec[1].length = sizeof(*ticketView);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DVD_TICKET_VIEW, 1, 1, vec);
    return ret;
}

ESError ESP_DiGetTmd(ESTitleMeta* tmd, u32* tmdSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    u32* pTmdSize = (u32*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || tmdSize == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(tmd)) {
        return ES_ERR_INVALID;
    }

    if (tmd == NULL) {
        vec[0].base = pTmdSize;
        vec[0].length = sizeof(*pTmdSize);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DVD_TMD, 0, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *tmdSize = *pTmdSize;
        }
        return ret;
    } else if (*tmdSize == 0) {
        return ES_ERR_INVALID;
    } else {
        *pTmdSize = *tmdSize;

        vec[0].base = pTmdSize;
        vec[0].length = sizeof(*pTmdSize);

        vec[1].base = tmd;
        vec[1].length = *tmdSize;

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DVD_TMD_WITH_COUNT, 1, 1, vec);
        return ret;
    }
}

ESError ESP_GetTmd(ESTitleId titleId, ESTitleMeta* tmd, u32* tmdSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    u32* pTmdSize = (u32*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0 || tmdSize == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(tmd)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    if (tmd == NULL) {
        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pTmdSize;
        vec[1].length = sizeof(*pTmdSize);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TMD, 1, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *tmdSize = *pTmdSize;
        }
        return ret;
    } else if (*tmdSize == 0) {
        return ES_ERR_INVALID;
    } else {
        *pTmdSize = *tmdSize;

        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pTmdSize;
        vec[1].length = sizeof(*pTmdSize);

        vec[2].base = tmd;
        vec[2].length = *tmdSize;

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TMD_WITH_SIZE, 2, 1, vec);
        return ret;
    }
}

ESError ESP_GetTmdView(ESTitleId titleId, ESTmdView* tmdView, u32* tmdSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    u32* pTmdSize = (u32*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0 || tmdSize == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(tmdView)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    if (tmdView == NULL) {
        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pTmdSize;
        vec[1].length = sizeof(*pTmdSize);

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TMDVIEW, 1, 1, vec);
        if (ret == IPC_RESULT_OK) {
            *tmdSize = *pTmdSize;
        }
        return ret;
    } else if (*tmdSize == 0) {
        return ES_ERR_INVALID;
    } else {
        *pTmdSize = *tmdSize;

        vec[0].base = pTitleId;
        vec[0].length = sizeof(*pTitleId);

        vec[1].base = pTmdSize;
        vec[1].length = sizeof(*pTmdSize);

        vec[2].base = tmdView;
        vec[2].length = *tmdSize;

        ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TMDVIEW_WITH_SIZE, 2, 1, vec);
        return ret;
    }
}

ESError ESP_GetDataDir(ESTitleId titleId, char* dataDir) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0 || dataDir == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(dataDir)) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    vec[1].base = dataDir;
    vec[1].length = sizeof(*dataDir) * 30;

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DATA_DIR, 1, 1, vec);
    return ret;
}

ESError ESP_GetTitleId(ESTitleId* titleId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0 || titleId == NULL) {
        return ES_ERR_INVALID;
    }

    vec[0].base = AT_ES_WORK(0x00);
    vec[0].length = sizeof(ESTitleId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_TITLE_ID, 0, 1, vec);
    if (ret == IPC_RESULT_OK) {
        *titleId = *(ESTitleId*)AT_ES_WORK(0x00);
    }
    return ret;
}

ESError ESP_GetDeviceId(ESId* deviceId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0 || deviceId == NULL) {
        return ES_ERR_INVALID;
    }

    vec[0].base = AT_ES_WORK(0x00);
    vec[0].length = sizeof(ESId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DEVICE_ID, 0, 1, vec);
    if (ret == IPC_RESULT_OK) {
        *deviceId = *(ESId*)AT_ES_WORK(0x00);
    }
    return ret;
}

ESError ESP_GetConsumption(ESTicketId ticketId, ESLpEntry* limitEntries, u32* numEntries) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTicketId = (ESTitleId*)AT_ES_WORK(0x00);
    u32* pNumEntries = (u32*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(limitEntries)) {
        return ES_ERR_INVALID;
    }

    *pTicketId = ticketId;
    vec[0].base = pTicketId;
    vec[0].length = sizeof(ticketId);

    if (limitEntries == NULL) {
        vec[1].base = NULL;
        vec[1].length = 0;
    } else {
        vec[1].base = limitEntries;
        vec[1].length = *numEntries * sizeof(*limitEntries);
        *pNumEntries = *numEntries;
    }

    vec[2].base = pNumEntries;
    vec[2].length = sizeof(*pNumEntries);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_CONSUMPTION, 1, 2, vec);
    *numEntries = *pNumEntries;
    return ret;
}

ESError ESP_GetDeviceCert(void* deviceCert) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0 || deviceCert == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED64(deviceCert)) {
        return ES_ERR_INVALID;
    }

    vec[0].base = deviceCert;
    vec[0].length = 0x180;

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_GET_DEVICE_CERT, 0, 1, vec);
    return ret;
}

ESError ESP_Sign(void* data, u32 length, ESSignature signature, ESCertSignature* sigKeyCert) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0 || data == NULL || signature == NULL || sigKeyCert == NULL) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(data) || !IS_ALIGNED(signature) || !IS_ALIGNED(sigKeyCert)) {
        return ES_ERR_INVALID;
    }

    vec[0].base = data;
    vec[0].length = length;

    vec[1].base = signature;
    vec[1].length = sizeof(ESSignature);

    vec[2].base = sigKeyCert;
    vec[2].length = sizeof(*sigKeyCert);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_SIGN, 1, 2, vec);
    return ret;
}

ESError ESP_DeleteTitleContent(ESTitleId titleId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_DELETE_TITLE_CONTENT, 1, 0, vec);
    return ret;
}

ESError ESP_DeleteContent(ESTitleId titleId, ESContentId contentId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    ESContentId* pContentId = (ESContentId*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    *pContentId = contentId;
    vec[1].base = pContentId;
    vec[1].length = sizeof(*pContentId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_DELETE_CONTENT, 2, 0, vec);
    return ret;
}

ESError ESP_ExportTitleInit(ESTitleId titleId, ESId deviceId, ESTicketId ticketId, void* certs, u32 certSize, void* crls, u32 crlSize,
                           int unknown, void* ticket, void* tmd, u32 tmdSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);

    ESError ret;

    if (!IS_ALIGNED(tmd) || !IS_ALIGNED(ticket) || !IS_ALIGNED(certs) || !IS_ALIGNED(crls)) {
        return ES_ERR_INVALID;
    }

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    switch (unknown) {
        case 2: {
            // @bug: Value is not returned.
            if (tmd == NULL || tmdSize == 0) {
                ret = ES_ERR_INVALID;
            }

            *pTitleId = titleId;
            vec[0].base = pTitleId;
            vec[0].length = sizeof(*pTitleId);

            vec[1].base = tmd;
            vec[1].length = tmdSize;

            ret = IOS_Ioctlv(__esFd, ES_IOCTLV_EXPORT_TITLE_INIT, 1, 1, vec);
            return ret;
        }
        default: {
            ret = ES_ERR_INVALID_UNKNOWN;
            return ret;
        }
    }
}

ESError ESP_ExportContentBegin(ESTitleId titleId, ESContentId contentId) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESTitleId* pTitleId = (ESTitleId*)AT_ES_WORK(0x00);
    ESContentId* pContentId = (ESContentId*)AT_ES_WORK(0x20);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pTitleId = titleId;
    vec[0].base = pTitleId;
    vec[0].length = sizeof(*pTitleId);

    *pContentId = contentId;
    vec[1].base = pContentId;
    vec[1].length = sizeof(*pContentId);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_EXPORT_CONTENT_BEGIN, 2, 0, vec);
    return ret;
}

ESError ESP_ExportContentData(ESFd fd, void* data, u32 dataSize) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESFd* pFd = (ESFd*)AT_ES_WORK(0x00);

    ESError ret;

    if (fd < 0 || data == NULL || dataSize == 0) {
        return ES_ERR_INVALID;
    }

    if (!IS_ALIGNED(data)) {
        return ES_ERR_INVALID;
    }

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    vec[1].base = data;
    vec[1].length = dataSize;

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_EXPORT_CONTENT_DATA, 1, 1, vec);
    return ret;
}

ESError ESP_ExportContentEnd(ESFd fd) {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);
    ESFd* pFd = (ESFd*)AT_ES_WORK(0x00);

    ESError ret;

    if (fd < 0 || __esFd < 0) {
        return ES_ERR_INVALID;
    }

    *pFd = fd;
    vec[0].base = pFd;
    vec[0].length = sizeof(*pFd);

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_EXPORT_CONTENT_END, 1, 0, vec);
    return ret;
}

ESError ESP_ExportTitleDone() {
    DECLARE_ES_WORK;

    IPCIOVector* vec = (IPCIOVector*)AT_ES_WORK(0xD0);

    ESError ret;

    if (__esFd < 0) {
        return ES_ERR_INVALID;
    }

    ret = IOS_Ioctlv(__esFd, ES_IOCTLV_EXPORT_TITLE_DONE, 0, 0, vec);
    return ret;
}



