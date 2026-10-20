#ifndef RVL_SDK_ESP_H
#define RVL_SDK_ESP_H
#include "types.h"
#include "revolution/ARC.h"
#include "revolution/IPC.h"
#include "private/iostypes.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef s32 ESFd;

typedef u32 ESId;
typedef u32 ESContentId;
typedef u64 ESTitleId;
typedef u64 ESTicketId;
typedef u8 ESVersion;
typedef u16 ESTitleVersion;
typedef ESTitleId ESSysVersion;
typedef u32 ESTitleType;
typedef u16 ESContentType;
typedef u8 ESTmdReserved[62];
typedef u8 ESTicketReserved[48];
typedef u8 ESSysAccessMask[2];
typedef u8 ESCidxMask[64];

typedef u8 ESHash[20];
typedef u8 ESSignature[60];

#pragma pack(push, 4)

typedef struct {
    ESVersion version;
    ESSysVersion sysVersion;
    ESTitleId titleId;
    ESTitleType type;
    u16 groupId;
    ESTmdReserved reserved;
    ESTitleVersion titleVersion;
    u16 numContents;
} ESTmdViewHeader;

typedef struct {
    ESContentId cid;
    u16 index;
    ESContentType type;
    u64 size;
} ESCmdView;

typedef struct {
    u32 code;
    u32 limit;
} ESLpEntry;

typedef struct {
    ESVersion version;
    ESTicketId ticketID;
    ESId devID;
    ESTitleId titleID;
    ESSysAccessMask sysAccessMask;
    u16 ticketVer;
    u32 accTitleID;
    u32 accTitleMask;
    u8 license;
    ESTicketReserved reserved;
    u8 audit;
    ESCidxMask cidxMask;
    ESLpEntry limits[8];
} ESTicketView;

typedef struct {
    ESTmdViewHeader head;
    ESCmdView contents[512];
} ESTmdView;

typedef struct {
    ESContentId cid;
    u16 index;
    ESContentType type;
    u64 size;
    IOSCHash hash;
} ESContentMeta;

typedef struct {
    ESVersion version;
    ESVersion caCrlVersion;
    ESVersion signerCrlVersion;
    ESSysVersion sysVersion;
    ESTitleId titleId;
    ESTitleType type;
    u16 groupId;
    ESTmdReserved reserved;
    u32 accessRights;
    ESTitleVersion titleVersion;
    u16 numContents;
    u16 bootIndex;
} ESTitleMetaHeader;

typedef struct {
    IOSCSigRsa2048 sig;
    ESTitleMetaHeader head;
    ESContentMeta contents[512];
} ESTitleMeta;

typedef struct {
    IOSCSigRsa2048 sig; 
    IOSCEccPublicKey serverPubKey;
    ESVersion version;
    ESVersion caCrlVersion;
    ESVersion signerCrlVersion;
    IOSCAesKey titleKey;
    ESTicketId ticketId;
    ESId deviceId;
    ESTitleId titleId;
    ESSysAccessMask sysAccessMask;
    u16 ticketVersion;
    u32 accessTitleId;
    u32 accessTitleMask;
    u8 licenseType;
    ESTicketReserved reserved;
    u8 audit;
    ESCidxMask cidxMask;
    ESLpEntry limits[8];
} ESTicket;

typedef enum ESCertSigType {
    ES_SIG_RSA4096 = 0x00010000,
    ES_SIG_RSA2048,
    ES_SIG_ECC,
} ESCertSigType;

typedef struct ESCertSignature {
    ESCertSigType sigType;  // 0x00
    u8 sig[256];            // 0x04
    u8 reserved[60];        // 0x104
    u8 issuer[64];          // 0x140
} ESCertSignature;

typedef s32 ESError;

#define ES_ERR_OK 0
#define ES_ERR_DONT_EXISTS -106
#define ES_ERR_1001 -1001
#define ES_ERR_1002 -1002
#define ES_ERR_1003 -1003
#define ES_ERR_1004 -1004
#define ES_ERR_INVALID_PUB_KEY_TYPE -1005
#define ES_ERR_1006 -1006
#define ES_ERR_1007 -1007
#define ES_ERR_1008 -1008
#define ES_ERR_FILE_READ_FAILED -1009
#define ES_ERR_FILE_WRITE_FAILED -1010
#define ES_ERR_1011 -1011
#define ES_ERR_INVALID_SIGNATURE -1012
#define ES_ERR_1013 -1013
#define ES_ERR_1014 -1014
#define ES_ERR_1015 -1015
#define ES_ERR_TMD_MAXFD -1016
#define ES_ERR_INVALID -1017
#define ES_ERR_1018 -1018
#define ES_ERR_INVALID_UNKNOWN -1019
#define ES_ERR_INVALID_DEVICE_ID -1020
#define ES_ERR_1021 -1021
#define ES_ERR_INVALID_CONTENT_HASH -1022
#define ES_ERR_1023 -1023
#define ES_ERR_NO_MEMORY -1024
#define ES_ERR_NO_TMD_FILE -1025
#define ES_ERR_NO_RIGHT -1026
#define ES_ERR_ISSUER_NOT_FOUND -1027
#define ES_ERR_TICKET_NOT_FOUND -1028
#define ES_ERR_INVALID_TICKET -1029
#define ES_ERR_1030 -1030
#define ES_ERR_INVALID_BOOT2 -1031
#define ES_ERR_UNKNOWN_FATAL -1032
#define ES_ERR_TICKET_EXPIRED -1033
#define ES_ERR_NO_NEW_COMMON_KEY -1034
#define ES_ERR_INVALID_TITLE_VER -1035
#define ES_ERR_BAD_SYSMENU_TICKET -1036
#define ES_ERR_BAD_SYSMENU_CONTENTS -1037
#define ES_ERR_1038 -1038
#define ES_ERR_NO_DISC_NAND_TMD -1039

#pragma pack(pop)

s32 ESP_InitLib(void);
s32 ESP_CloseLib(void);
s32 ESP_LaunchTitle(u64, ESTicketView *);
s32 ESP_GetTicketViews(ESTitleId, ESTicketView *, u32 *);
s32 ESP_DiGetTicketView(const void *, ESTicketView *);
s32 ESP_DiGetTmd(ESTitleMeta *, u32 *);
s32 ESP_GetTmdView(ESTitleId, ESTmdView *, u32 *);
s32 ESP_GetDataDir(ESTitleId, char *);
s32 ESP_GetTitleId(ESTitleId *);
s32 ESP_GetConsumption(ESTicketId, ESLpEntry *, u32 *);

#ifdef __cplusplus
}
#endif
#endif
