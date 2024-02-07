/*
    Compile unit: C:\rockband2\system\src\os\PlatformMgr_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805C0658 -> 0x805C6FA4
*/
class Symbol t; // size: 0x4, address: 0x80A54AF4
class PlatformMgr ThePlatformMgr; // size: 0x21B0, address: 0x80986700
static char freadBuf[256]; // size: 0x100, address: 0x809888B0
static int seekSpot; // size: 0x4, address: 0x80A54AF8
static unsigned char gLastNetStatus; // size: 0x1, address: 0x80A54AFC
class Symbol t; // size: 0x4, address: 0x80A54B00
class Symbol t; // size: 0x4, address: 0x80A54B08
// Range: 0x805C0658 -> 0x805C086C
void * PlatformMgr::PlatformMgr(class PlatformMgr * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q211PlatformMgr31WiiMessagingNotificationHandler;
    // -> struct [anonymous] __vt__11PlatformMgr;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x805C086C -> 0x805C09E0
void * PlatformMgr::~PlatformMgr(class PlatformMgr * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__11PlatformMgr;
}

// Range: 0x805C09E0 -> 0x805C0A18
void PlatformMgr::PreInit(class PlatformMgr * const this /* r31 */) {}

struct NCDIpProfile {
    // total size: 0x14
    unsigned char addr[4]; // offset 0x0, size 0x4
    unsigned char netmask[4]; // offset 0x4, size 0x4
    unsigned char gateway[4]; // offset 0x8, size 0x4
    unsigned char dns1[4]; // offset 0xC, size 0x4
    unsigned char dns2[4]; // offset 0x10, size 0x4
};
struct NCDIpAdjustProfile {
    // total size: 0xC
    long maxTransferUnit; // offset 0x0, size 0x4
    long tcpRetransTimeout; // offset 0x4, size 0x4
    long dhcpRetransCount; // offset 0x8, size 0x4
};
struct NCDProxyServerProfile {
    // total size: 0x148
    unsigned char mode; // offset 0x0, size 0x1
    unsigned char authType; // offset 0x1, size 0x1
    unsigned char reserved[2]; // offset 0x2, size 0x2
    signed char server[256]; // offset 0x4, size 0x100
    unsigned short port; // offset 0x104, size 0x2
    signed char username[33]; // offset 0x106, size 0x21
    signed char password[33]; // offset 0x127, size 0x21
};
struct /* @class$11221PlatformMgr_Wii_cpp */ {
    // total size: 0x404
    unsigned long isEnabled; // offset 0x0, size 0x4
    signed char servers[1024]; // offset 0x4, size 0x400
};
struct /* @class$11222PlatformMgr_Wii_cpp */ {
    // total size: 0x108
    unsigned long isEnabled1_1; // offset 0x0, size 0x4
    unsigned long isAutomaticEnabled; // offset 0x4, size 0x4
    signed char automatic[256]; // offset 0x8, size 0x100
};
struct NCDProxyProfile {
    // total size: 0x79C
    struct NCDProxyServerProfile http; // offset 0x0, size 0x148
    struct NCDProxyServerProfile ssl; // offset 0x148, size 0x148
    struct /* @class$11221PlatformMgr_Wii_cpp */ {
        // total size: 0x404
        unsigned long isEnabled; // offset 0x0, size 0x4
        signed char servers[1024]; // offset 0x4, size 0x400
    } noProxy; // offset 0x290, size 0x404
    struct /* @class$11222PlatformMgr_Wii_cpp */ {
        // total size: 0x108
        unsigned long isEnabled1_1; // offset 0x0, size 0x4
        unsigned long isAutomaticEnabled; // offset 0x4, size 0x4
        signed char automatic[256]; // offset 0x8, size 0x100
    } browser; // offset 0x694, size 0x108
};
struct NCDWiredProfile {
    // total size: 0x4
    unsigned char reserved[4]; // offset 0x0, size 0x4
};
union /* @class$11208PlatformMgr_Wii_cpp */ {
    unsigned short option; // offset 0x0, size 0x2
    unsigned char reserved[2]; // offset 0x0, size 0x2
};
struct /* @class$11207PlatformMgr_Wii_cpp */ {
    // total size: 0x18
    unsigned short keyId; // offset 0x0, size 0x2
    union { // inferred
        union /* @class$11208PlatformMgr_Wii_cpp */ {
            unsigned short option; // offset 0x0, size 0x2
            unsigned char reserved[2]; // offset 0x0, size 0x2
        } __anon$11209; // offset 0x2, size 0x2
        unsigned short option; // offset 0x2, size 0x2
        unsigned char reserved[2]; // offset 0x2, size 0x2
    };
    unsigned char key[4][5]; // offset 0x4, size 0x14
};
union /* @class$11211PlatformMgr_Wii_cpp */ {
    unsigned short option; // offset 0x0, size 0x2
    unsigned char reserved[2]; // offset 0x0, size 0x2
};
struct /* @class$11210PlatformMgr_Wii_cpp */ {
    // total size: 0x38
    unsigned short keyId; // offset 0x0, size 0x2
    union { // inferred
        union /* @class$11211PlatformMgr_Wii_cpp */ {
            unsigned short option; // offset 0x0, size 0x2
            unsigned char reserved[2]; // offset 0x0, size 0x2
        } __anon$11212; // offset 0x2, size 0x2
        unsigned short option; // offset 0x2, size 0x2
        unsigned char reserved[2]; // offset 0x2, size 0x2
    };
    unsigned char key[4][13]; // offset 0x4, size 0x34
};
struct /* @class$11213PlatformMgr_Wii_cpp */ {
    // total size: 0x44
    unsigned short keyLen; // offset 0x0, size 0x2
    unsigned char reserved[2]; // offset 0x2, size 0x2
    unsigned char key[64]; // offset 0x4, size 0x40
};
struct /* @class$11214PlatformMgr_Wii_cpp */ {
    // total size: 0x44
    unsigned short keyLen; // offset 0x0, size 0x2
    unsigned char reserved[2]; // offset 0x2, size 0x2
    unsigned char key[64]; // offset 0x4, size 0x40
};
union /* @class$11206PlatformMgr_Wii_cpp */ {
    struct /* @class$11207PlatformMgr_Wii_cpp */ {
        // total size: 0x18
        unsigned short keyId; // offset 0x0, size 0x2
        union { // inferred
            union /* @class$11208PlatformMgr_Wii_cpp */ {
                unsigned short option; // offset 0x0, size 0x2
                unsigned char reserved[2]; // offset 0x0, size 0x2
            } __anon$11209; // offset 0x2, size 0x2
            unsigned short option; // offset 0x2, size 0x2
            unsigned char reserved[2]; // offset 0x2, size 0x2
        };
        unsigned char key[4][5]; // offset 0x4, size 0x14
    } wep40; // offset 0x0, size 0x18
    struct /* @class$11210PlatformMgr_Wii_cpp */ {
        // total size: 0x38
        unsigned short keyId; // offset 0x0, size 0x2
        union { // inferred
            union /* @class$11211PlatformMgr_Wii_cpp */ {
                unsigned short option; // offset 0x0, size 0x2
                unsigned char reserved[2]; // offset 0x0, size 0x2
            } __anon$11212; // offset 0x2, size 0x2
            unsigned short option; // offset 0x2, size 0x2
            unsigned char reserved[2]; // offset 0x2, size 0x2
        };
        unsigned char key[4][13]; // offset 0x4, size 0x34
    } wep104; // offset 0x0, size 0x38
    struct /* @class$11213PlatformMgr_Wii_cpp */ {
        // total size: 0x44
        unsigned short keyLen; // offset 0x0, size 0x2
        unsigned char reserved[2]; // offset 0x2, size 0x2
        unsigned char key[64]; // offset 0x4, size 0x40
    } tkip; // offset 0x0, size 0x44
    struct /* @class$11214PlatformMgr_Wii_cpp */ {
        // total size: 0x44
        unsigned short keyLen; // offset 0x0, size 0x2
        unsigned char reserved[2]; // offset 0x2, size 0x2
        unsigned char key[64]; // offset 0x4, size 0x40
    } aes; // offset 0x0, size 0x44
};
struct NCDPrivacy {
    // total size: 0x48
    unsigned short mode; // offset 0x0, size 0x2
    unsigned char reserved[2]; // offset 0x2, size 0x2
    union { // inferred
        union /* @class$11206PlatformMgr_Wii_cpp */ {
            struct /* @class$11207PlatformMgr_Wii_cpp */ {
                // total size: 0x18
                unsigned short keyId; // offset 0x0, size 0x2
                union { // inferred
                    union /* @class$11208PlatformMgr_Wii_cpp */ {
                        unsigned short option; // offset 0x0, size 0x2
                        unsigned char reserved[2]; // offset 0x0, size 0x2
                    } __anon$11209; // offset 0x2, size 0x2
                    unsigned short option; // offset 0x2, size 0x2
                    unsigned char reserved[2]; // offset 0x2, size 0x2
                };
                unsigned char key[4][5]; // offset 0x4, size 0x14
            } wep40; // offset 0x0, size 0x18
            struct /* @class$11210PlatformMgr_Wii_cpp */ {
                // total size: 0x38
                unsigned short keyId; // offset 0x0, size 0x2
                union { // inferred
                    union /* @class$11211PlatformMgr_Wii_cpp */ {
                        unsigned short option; // offset 0x0, size 0x2
                        unsigned char reserved[2]; // offset 0x0, size 0x2
                    } __anon$11212; // offset 0x2, size 0x2
                    unsigned short option; // offset 0x2, size 0x2
                    unsigned char reserved[2]; // offset 0x2, size 0x2
                };
                unsigned char key[4][13]; // offset 0x4, size 0x34
            } wep104; // offset 0x0, size 0x38
            struct /* @class$11213PlatformMgr_Wii_cpp */ {
                // total size: 0x44
                unsigned short keyLen; // offset 0x0, size 0x2
                unsigned char reserved[2]; // offset 0x2, size 0x2
                unsigned char key[64]; // offset 0x4, size 0x40
            } tkip; // offset 0x0, size 0x44
            struct /* @class$11214PlatformMgr_Wii_cpp */ {
                // total size: 0x44
                unsigned short keyLen; // offset 0x0, size 0x2
                unsigned char reserved[2]; // offset 0x2, size 0x2
                unsigned char key[64]; // offset 0x4, size 0x40
            } aes; // offset 0x0, size 0x44
        } __anon$11215; // offset 0x4, size 0x44
        struct /* @class$11207PlatformMgr_Wii_cpp */ {
            // total size: 0x18
            unsigned short keyId; // offset 0x0, size 0x2
            union { // inferred
                union /* @class$11208PlatformMgr_Wii_cpp */ {
                    unsigned short option; // offset 0x0, size 0x2
                    unsigned char reserved[2]; // offset 0x0, size 0x2
                } __anon$11209; // offset 0x2, size 0x2
                unsigned short option; // offset 0x2, size 0x2
                unsigned char reserved[2]; // offset 0x2, size 0x2
            };
            unsigned char key[4][5]; // offset 0x4, size 0x14
        } wep40; // offset 0x4, size 0x18
        struct /* @class$11210PlatformMgr_Wii_cpp */ {
            // total size: 0x38
            unsigned short keyId; // offset 0x0, size 0x2
            union { // inferred
                union /* @class$11211PlatformMgr_Wii_cpp */ {
                    unsigned short option; // offset 0x0, size 0x2
                    unsigned char reserved[2]; // offset 0x0, size 0x2
                } __anon$11212; // offset 0x2, size 0x2
                unsigned short option; // offset 0x2, size 0x2
                unsigned char reserved[2]; // offset 0x2, size 0x2
            };
            unsigned char key[4][13]; // offset 0x4, size 0x34
        } wep104; // offset 0x4, size 0x38
        struct /* @class$11213PlatformMgr_Wii_cpp */ {
            // total size: 0x44
            unsigned short keyLen; // offset 0x0, size 0x2
            unsigned char reserved[2]; // offset 0x2, size 0x2
            unsigned char key[64]; // offset 0x4, size 0x40
        } tkip; // offset 0x4, size 0x44
        struct /* @class$11214PlatformMgr_Wii_cpp */ {
            // total size: 0x44
            unsigned short keyLen; // offset 0x0, size 0x2
            unsigned char reserved[2]; // offset 0x2, size 0x2
            unsigned char key[64]; // offset 0x4, size 0x40
        } aes; // offset 0x4, size 0x44
    };
};
struct NCDApConfig {
    // total size: 0x6C
    unsigned char ssid[32]; // offset 0x0, size 0x20
    unsigned short ssidLength; // offset 0x20, size 0x2
    unsigned char reserved[2]; // offset 0x22, size 0x2
    struct NCDPrivacy privacy; // offset 0x24, size 0x48
};
struct NCDUsbapConfig {
    // total size: 0x18
    unsigned short nickname[11]; // offset 0x0, size 0x16
    unsigned char reserved[2]; // offset 0x16, size 0x2
};
struct /* @class$11216PlatformMgr_Wii_cpp */ {
    // total size: 0x38
    unsigned char ssid[32]; // offset 0x0, size 0x20
    unsigned short ssidLength; // offset 0x20, size 0x2
    unsigned short keyId; // offset 0x22, size 0x2
    unsigned char key[4][5]; // offset 0x24, size 0x14
};
struct /* @class$11217PlatformMgr_Wii_cpp */ {
    // total size: 0x58
    unsigned char ssid[32]; // offset 0x0, size 0x20
    unsigned short ssidLength; // offset 0x20, size 0x2
    unsigned short keyId; // offset 0x22, size 0x2
    unsigned char key[4][13]; // offset 0x24, size 0x34
};
struct /* @class$11218PlatformMgr_Wii_cpp */ {
    // total size: 0x64
    unsigned char ssid[32]; // offset 0x0, size 0x20
    unsigned short ssidLength; // offset 0x20, size 0x2
    unsigned short keyLen; // offset 0x22, size 0x2
    unsigned char key[64]; // offset 0x24, size 0x40
};
struct /* @class$11219PlatformMgr_Wii_cpp */ {
    // total size: 0x64
    unsigned char ssid[32]; // offset 0x0, size 0x20
    unsigned short ssidLength; // offset 0x20, size 0x2
    unsigned short keyLen; // offset 0x22, size 0x2
    unsigned char key[64]; // offset 0x24, size 0x40
};
struct NCDAossConfig {
    // total size: 0x158
    struct /* @class$11216PlatformMgr_Wii_cpp */ {
        // total size: 0x38
        unsigned char ssid[32]; // offset 0x0, size 0x20
        unsigned short ssidLength; // offset 0x20, size 0x2
        unsigned short keyId; // offset 0x22, size 0x2
        unsigned char key[4][5]; // offset 0x24, size 0x14
    } wep40; // offset 0x0, size 0x38
    struct /* @class$11217PlatformMgr_Wii_cpp */ {
        // total size: 0x58
        unsigned char ssid[32]; // offset 0x0, size 0x20
        unsigned short ssidLength; // offset 0x20, size 0x2
        unsigned short keyId; // offset 0x22, size 0x2
        unsigned char key[4][13]; // offset 0x24, size 0x34
    } wep104; // offset 0x38, size 0x58
    struct /* @class$11218PlatformMgr_Wii_cpp */ {
        // total size: 0x64
        unsigned char ssid[32]; // offset 0x0, size 0x20
        unsigned short ssidLength; // offset 0x20, size 0x2
        unsigned short keyLen; // offset 0x22, size 0x2
        unsigned char key[64]; // offset 0x24, size 0x40
    } tkip; // offset 0x90, size 0x64
    struct /* @class$11219PlatformMgr_Wii_cpp */ {
        // total size: 0x64
        unsigned char ssid[32]; // offset 0x0, size 0x20
        unsigned short ssidLength; // offset 0x20, size 0x2
        unsigned short keyLen; // offset 0x22, size 0x2
        unsigned char key[64]; // offset 0x24, size 0x40
    } aes; // offset 0xF4, size 0x64
};
union /* @class$11220PlatformMgr_Wii_cpp */ {
    struct NCDApConfig manual; // offset 0x0, size 0x6C
    struct NCDUsbapConfig usbap; // offset 0x0, size 0x18
    struct NCDAossConfig aoss; // offset 0x0, size 0x158
    struct NCDApConfig rakuraku; // offset 0x0, size 0x6C
};
struct NCDWirelessProfile {
    // total size: 0x15C
    unsigned short rateset; // offset 0x0, size 0x2
    unsigned char configMethod; // offset 0x2, size 0x1
    unsigned char retryLimit; // offset 0x3, size 0x1
    union /* @class$11220PlatformMgr_Wii_cpp */ {
        struct NCDApConfig manual; // offset 0x0, size 0x6C
        struct NCDUsbapConfig usbap; // offset 0x0, size 0x18
        struct NCDAossConfig aoss; // offset 0x0, size 0x158
        struct NCDApConfig rakuraku; // offset 0x0, size 0x6C
    } config; // offset 0x4, size 0x158
};
union /* @class$11223PlatformMgr_Wii_cpp */ {
    struct NCDWiredProfile wired; // offset 0x0, size 0x4
    struct NCDWirelessProfile wireless; // offset 0x0, size 0x15C
};
struct NCDProfile {
    // total size: 0x91C
    unsigned char flags; // offset 0x0, size 0x1
    unsigned char reserved[3]; // offset 0x1, size 0x3
    struct NCDIpProfile ip; // offset 0x4, size 0x14
    struct NCDIpAdjustProfile adjust; // offset 0x18, size 0xC
    struct NCDProxyProfile proxy; // offset 0x24, size 0x79C
    union /* @class$11223PlatformMgr_Wii_cpp */ {
        struct NCDWiredProfile wired; // offset 0x0, size 0x4
        struct NCDWirelessProfile wireless; // offset 0x0, size 0x15C
    } netif; // offset 0x7C0, size 0x15C
};
struct NCDConfig {
    // total size: 0x1B5C
    unsigned long version; // offset 0x0, size 0x4
    unsigned char selectedMedia; // offset 0x4, size 0x1
    unsigned char nwc24Permission; // offset 0x5, size 0x1
    unsigned char linkTimeout; // offset 0x6, size 0x1
    unsigned char reserved[1]; // offset 0x7, size 0x1
    struct NCDProfile profiles[3]; // offset 0x8, size 0x1B54
};
// Range: 0x805C0A18 -> 0x805C0B08
void PlatformMgr::Init(class PlatformMgr * const this /* r31 */) {
    // Local variables
    struct NCDConfig config; // r1+0x8
    int ret; // r0

    // References
    // -> class HttpWii TheHttpWii;
    // -> int (* CNTSDIsInsertedRSO)();
    // -> long (* CNTSDInitRSO)(void *, long);
    // -> class ObjectDir * sMainDir;
}

// Range: 0x805C0B08 -> 0x805C0B80
void PlatformMgr::Terminate(class PlatformMgr * const this /* r30 */) {
    // References
    // -> class HttpWii TheHttpWii;
}

static class Symbol setup_overflow; // size: 0x4, address: 0x80A54B10
class WiiControllerOverflowMsg : public Message {
    // total size: 0x8
};
static class WiiControllerOverflowMsg msg; // size: 0x8, address: 0x809889C0
static class PlatformMgrOpCompleteMsg msg; // size: 0x8, address: 0x809889D8
enum ECOperation {
    EC_OP_Invalid = 0,
    EC_OP_PurchaseTitle = 1,
    EC_OP_Unused1 = 2,
    EC_OP_SyncTickets = 3,
    EC_OP_RefreshCachedBalance = 4,
    EC_OP_PurchasePoints = 5,
    EC_OP_GetTitle = 6,
    EC_OP_CheckRegistration = 7,
    EC_OP_Register = 8,
    EC_OP_Unregister = 9,
    EC_OP_Transfer = 10,
    EC_OP_DeleteOwnership = 11,
    EC_OP_PurchaseGiftTitle = 12,
    EC_OP_AcceptGiftTitle = 13,
    EC_OP_CheckDeviceStatus = 14,
    EC_OP_SyncRegistration = 15,
    EC_OP_Connect = 16,
    EC_OP_DownloadContents = 17,
    EC_OP_Subscribe = 18,
    EC_OP_GetChallenge = 19,
    EC_OP_UpdateStatus = 20,
    EC_OP_ListTitles = 21,
    EC_OP_ListContentSets = 22,
    EC_OP_ListSubscriptionPricings = 23,
    EC_OP_ListPointsPricings = 24,
    EC_OP_ListECardItems = 25,
    EC_OP_ListTitleContents = 26,
};
enum ECOpPhase {
    EC_PHASE_NoPhase = 0,
    EC_PHASE_Starting = 1,
    EC_PHASE_Done = 2,
    EC_PHASE_PurchasingTitle = 3,
    EC_PHASE_Unused1 = 4,
    EC_PHASE_DownloadingContent = 5,
    EC_PHASE_GettingTicketsFromServer = 6,
    EC_PHASE_GettingPointsBalance = 7,
    EC_PHASE_PurchasingPoints = 8,
    EC_PHASE_CheckingRegistrationStatus = 9,
    EC_PHASE_Registering = 10,
    EC_PHASE_Unregistering = 11,
    EC_PHASE_Transfer = 12,
    EC_PHASE_DeletingOwnership = 13,
    EC_PHASE_AcceptingGiftTitle = 14,
    EC_PHASE_GettingDeviceStatus = 15,
    EC_PHASE_SyncingRegistration = 16,
    EC_PHASE_Connecting = 17,
    EC_PHASE_UpdatingStatus = 18,
    EC_PHASE_ListingTitles = 19,
    EC_PHASE_ListingContentSets = 20,
    EC_PHASE_ListingSubscriptionPricings = 21,
    EC_PHASE_ListingPointsPricings = 22,
    EC_PHASE_ListingECardItems = 23,
    EC_PHASE_GettingECardBalance = 24,
    EC_PHASE_Subscribing = 25,
    EC_PHASE_GettingChallenge = 26,
    EC_PHASE_ListingTitleContents = 27,
};
struct ECProgress {
    // total size: 0x9C
    long status; // offset 0x0, size 0x4
    enum ECOperation operation; // offset 0x4, size 0x4
    enum ECOpPhase phase; // offset 0x8, size 0x4
    long isCancelRequested; // offset 0xC, size 0x4
    unsigned long totalSize; // offset 0x10, size 0x4
    unsigned long downloadedSize; // offset 0x14, size 0x4
    long errCode; // offset 0x18, size 0x4
    char errInfo[128]; // offset 0x1C, size 0x80
};
// Range: 0x805C0B80 -> 0x805C2698
void PlatformMgr::Poll(class PlatformMgr * const this /* r27 */) {
    // Local variables
    class UIChangedMsg msg; // r1+0x208
    class StorageChangedMsg msg; // r1+0x200
    class ConnectionStatusChangedMsg msg; // r1+0x1F8
    class qList lstIDs; // r1+0x1F0
    struct _List_iterator it; // r1+0xD4
    class TextMessage * wiiMessage; // r1+0xD0
    struct _List_iterator it2; // r1+0xCC
    char * addfriend; // r28
    class Friend * addFriendButton; // r1+0xC8
    int i; // r29
    struct _List_iterator it; // r1+0xC4
    class Friend * newFriend; // r1+0xC0
    long rv; // r29
    struct ECProgress progress; // r1+0x228
    int i; // r28
    int percent; // r26

    // References
    // -> class ContentMgr & TheContentMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__24PlatformMgrOpCompleteMsg;
    // -> class Symbol t;
    // -> static class PlatformMgrOpCompleteMsg msg;
    // -> struct [anonymous] __vt__26ConnectionStatusChangedMsg;
    // -> class Symbol t;
    // -> static unsigned char gLastNetStatus;
    // -> struct [anonymous] __vt__17StorageChangedMsg;
    // -> class Symbol t;
    // -> int (* CNTSDIsInsertedRSO)();
    // -> struct [anonymous] __vt__24WiiControllerOverflowMsg;
    // -> class Symbol t;
    // -> static class WiiControllerOverflowMsg msg;
    // -> static class Symbol setup_overflow;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__12UIChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Net TheNet;
    // -> const char * gNullStr;
}

// Range: 0x805C2698 -> 0x805C26A0
unsigned char PlatformMgr::IsConnected() {}

// Range: 0x805C26A0 -> 0x805C26A4
void PlatformMgr::SetNotifyUILocation() {}

// Range: 0x805C26A4 -> 0x805C26AC
unsigned char PlatformMgr::IsEthernetCableConnected() {}

// Range: 0x805C26AC -> 0x805C26B4
unsigned char PlatformMgr::IsGuideShowing() {}

// Range: 0x805C26B4 -> 0x805C26C4
class DataNode PlatformMgr::OnSignInUsers() {}

// Range: 0x805C26C4 -> 0x805C26CC
unsigned char PlatformMgr::HasOnlinePrivilege() {}

// Range: 0x805C26CC -> 0x805C2708
unsigned char PlatformMgr::PlayerHasOnlinePrivilege(const class PlatformMgr * const this /* r31 */) {}

// Range: 0x805C2708 -> 0x805C2754
unsigned char PlatformMgr::UserHasOnlinePrivilege(const class PlatformMgr * const this /* r31 */) {}

// Range: 0x805C2754 -> 0x805C275C
unsigned char PlatformMgr::CanSeeUserCreatedContent() {}

// Range: 0x805C275C -> 0x805C2760
void PlatformMgr::GetOnlineID() {}

// Range: 0x805C2760 -> 0x805C2764
void PlatformMgr::ShowMarketplaceUI() {}

// Range: 0x805C2764 -> 0x805C2768
void PlatformMgr::ShowFriendsUI() {}

// Range: 0x805C2768 -> 0x805C276C
void PlatformMgr::EnableXMP() {}

// Range: 0x805C276C -> 0x805C2770
void PlatformMgr::DisableXMP() {}

// Range: 0x805C2770 -> 0x805C2774
void PlatformMgr::SetScreenSaver() {}

// Range: 0x805C2774 -> 0x805C27B0
unsigned char PlatformMgr::IsPlayerSignedIn(const class PlatformMgr * const this /* r31 */) {
    // Local variables
    int padNum; // r0
}

// Range: 0x805C27B0 -> 0x805C27EC
unsigned char PlatformMgr::IsUserSignedIn(const class PlatformMgr * const this /* r31 */) {
    // Local variables
    int padNum; // r0
}

// Range: 0x805C27EC -> 0x805C2838
unsigned char PlatformMgr::HasUserSigninChanged(const class PlatformMgr * const this /* r31 */) {
    // Local variables
    int padNum; // r0
}

// Range: 0x805C2838 -> 0x805C2840
unsigned char PlatformMgr::IsSignedIntoLive() {}

// Range: 0x805C2840 -> 0x805C2848
char * PlatformMgr::GetName() {}

// Range: 0x805C2848 -> 0x805C2850
void PlatformMgr::EnumerateFriends() {}

// Range: 0x805C2850 -> 0x805C2998
void PlatformMgr::EnumerateFriends(class PlatformMgr * const this /* r27 */, class vector & friends /* r28 */, class Object * callback /* r29 */, enum FriendType type /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C2998 -> 0x805C2AA8
void PlatformMgr::EnumerateMessages(class PlatformMgr * const this /* r29 */, class vector & messages /* r30 */, class Object * callback /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal11ResultRange;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C2AA8 -> 0x805C2AAC
void PlatformMgr::CheckMailbox() {}

// Range: 0x805C2AAC -> 0x805C2AB0
void PlatformMgr::RunNetStartUtility() {}

// Range: 0x805C2AB0 -> 0x805C2AB8
int PlatformMgr::GetOwnerPlayerOfGuestPlayer() {}

// Range: 0x805C2AB8 -> 0x805C2AC0
unsigned char PlatformMgr::IsPadAGuest() {}

// Range: 0x805C2AC0 -> 0x805C2AC8
unsigned char PlatformMgr::IsPlayerAGuest() {}

// Range: 0x805C2AC8 -> 0x805C2B44
void PlatformMgr::Draw(class PlatformMgr * const this /* r31 */) {}

// Range: 0x805C2B44 -> 0x805C2B90
void PlatformMgr::InitGQR() {}

// Range: 0x805C2B90 -> 0x805C2B94
void PlatformMgr::SetUpDRM() {}

// Range: 0x805C2B94 -> 0x805C2B98
void PlatformMgr::ClearDRM() {}

// Range: 0x805C2B98 -> 0x805C2B9C
void PlatformMgr::AddSongInfo() {}

// Range: 0x805C2B9C -> 0x805C2BA4
int PlatformMgr::SigninMask() {}

// Range: 0x805C2BA4 -> 0x805C2BAC
int PlatformMgr::SigninChangedMask() {}

// Range: 0x805C2BAC -> 0x805C2BCC
unsigned char PlatformMgr::IsSignedIn() {}

// Range: 0x805C2BCC -> 0x805C2CD0
unsigned char PlatformMgr::OnMsg(class PlatformMgr * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {
    // References
    // -> class UIManager TheUI;
}

// Range: 0x805C2CD0 -> 0x805C2D2C
unsigned char PlatformMgr::OnMsg(class PlatformMgr * const this /* r30 */) {}

static class DiskErrorMsg msg; // size: 0x8, address: 0x809889F0
class WiiDiscErrorMsg : public Message {
    // total size: 0x8
};
static class WiiDiscErrorMsg msg; // size: 0x8, address: 0x80988A08
// Range: 0x805C2D2C -> 0x805C3004
void PlatformMgr::SetDiscError(class PlatformMgr * const this /* r30 */, unsigned char error /* r29 */) {
    // References
    // -> struct [anonymous] __vt__15WiiDiscErrorMsg;
    // -> class Symbol t;
    // -> static class WiiDiscErrorMsg msg;
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__12DiskErrorMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class DiskErrorMsg msg;
}

// Range: 0x805C3088 -> 0x805C31B4
void PlatformMgr::AddFriend(class PlatformMgr * const this /* r27 */, const char * key /* r28 */) {
    // Local variables
    unsigned long long friendkey; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
}

// Range: 0x805C31B4 -> 0x805C32BC
void PlatformMgr::RemoveFriend(class PlatformMgr * const this /* r27 */, const char * key /* r28 */) {
    // Local variables
    unsigned long long friendkey; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
}

// Range: 0x805C32BC -> 0x805C33C4
void PlatformMgr::AcceptFriendship(class PlatformMgr * const this /* r27 */, const char * key /* r28 */) {
    // Local variables
    unsigned long long friendkey; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
}

// Range: 0x805C33C4 -> 0x805C34CC
void PlatformMgr::DeclineFriendship(class PlatformMgr * const this /* r27 */, const char * key /* r28 */) {
    // Local variables
    unsigned long long friendkey; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
}

// Range: 0x805C34CC -> 0x805C3558
char * PlatformMgr::GetFriendCode() {
    // Local variables
    unsigned long long friendkey; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C3558 -> 0x805C35CC
char * PlatformMgr::GetUsernameFull() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C35CC -> 0x805C3698
unsigned char PlatformMgr::IsYourKey(const char * key /* r29 */) {
    // Local variables
    unsigned long long yourKey; // r0
    unsigned long long friendkey; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C3698 -> 0x805C3730
unsigned char PlatformMgr::CheckFriendCode(const char * key /* r29 */) {
    // Local variables
    unsigned long long friendkey; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C3730 -> 0x805C3734
void PlatformMgr::ChangeFriendNickname() {}

// Range: 0x805C3734 -> 0x805C373C
void PlatformMgr::SetConnected() {}

static char buffer[256]; // size: 0x100, address: 0x80988A10
// Range: 0x805C373C -> 0x805C3810
char * PlatformMgr::ConvertUsername(const char * username /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static char buffer[256];
}

class NetStartUtilityFinishedMsg : public Message {
    // total size: 0x8
};
static class NetStartUtilityFinishedMsg msg; // size: 0x8, address: 0x80988B20
// Range: 0x805C3810 -> 0x805C3B44
void PlatformMgr::InitNintendoConnection(class PlatformMgr * const this /* r30 */) {
    // Local variables
    int result; // r1+0x10

    // References
    // -> struct [anonymous] __vt__26NetStartUtilityFinishedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class NetStartUtilityFinishedMsg msg;
}

// Range: 0x805C3BC8 -> 0x805C3BD0
unsigned char PlatformMgr::CheckProfane() {}

// Range: 0x805C3BD0 -> 0x805C3C38
int PlatformMgr::FinishProfane() {
    // Local variables
    unsigned char result; // r1+0x9
    unsigned char fail; // r1+0x8
}

static class NetStartUtilityFinishedMsg msg; // size: 0x8, address: 0x80988B38
// Range: 0x805C3C38 -> 0x805C3E60
void PlatformMgr::SendNetStartComplete(class PlatformMgr * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26NetStartUtilityFinishedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class NetStartUtilityFinishedMsg msg;
}

// Range: 0x805C3E60 -> 0x805C4058
void PlatformMgr::CloseNintendoConnection(class PlatformMgr * const this /* r31 */, unsigned char notify /* r30 */) {
    // Local variables
    class ConnectionStatusChangedMsg msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__26ConnectionStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static unsigned char gLastNetStatus;
}

// Range: 0x805C4058 -> 0x805C4098
void * ecAlloc() {
    // Local variables
    void * p; // r0
}

// Range: 0x805C4098 -> 0x805C40A8
void ecFree() {}

// Range: 0x805C40A8 -> 0x805C40F0
static unsigned long long MakeDataTitleId() {
    // Local variables
    unsigned long long dtTitleId; // r1+0x8
}

// Range: 0x805C40F0 -> 0x805C4120
unsigned char PlatformMgr::NeedSync() {
    // Local variables
    int ret; // r0
}

// Range: 0x805C4120 -> 0x805C4378
unsigned char PlatformMgr::InitCommerce(class PlatformMgr * const this /* r31 */, class Object * callback /* r26 */) {
    // Local variables
    long opId; // r0
    char * appId; // r28
    char * tin; // r27
    int retVal; // r0
    enum NHTTPError myError; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C4378 -> 0x805C4428
void PlatformMgr::DestroyCommerce(class PlatformMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C4428 -> 0x805C44C8
unsigned char PlatformMgr::UpdateTitle(class PlatformMgr * const this /* r29 */) {
    // Local variables
    long rv; // r0
    unsigned long long titleId; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C44C8 -> 0x805C45F4
unsigned char PlatformMgr::RequestPurchase(class PlatformMgr * const this /* r28 */, const char * dtCode /* r29 */, const char * storeIndex /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C45F4 -> 0x805C474C
unsigned char PlatformMgr::PurchaseContentUnit(class PlatformMgr * const this /* r28 */) {
    // Local variables
    struct ECContentCatalogInfo * c; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C474C -> 0x805C483C
unsigned char PlatformMgr::DownloadContentUnit(class PlatformMgr * const this /* r27 */) {
    // Local variables
    long opId; // r0
    unsigned long long titleId; // r29
    unsigned short contentIdxs[2]; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C483C -> 0x805C493C
unsigned char PlatformMgr::QueryOffers(class PlatformMgr * const this /* r26 */, const char * dtCode /* r29 */, class map & contents /* r27 */, class Object * callback /* r28 */) {
    // Local variables
    long opId; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C493C -> 0x805C4AB0
unsigned char PlatformMgr::CheckPoints(class PlatformMgr * const this /* r28 */) {
    // Local variables
    long rv; // r0
    long points; // r1+0x8
    long price; // r29
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C4AB0 -> 0x805C4B18
int PlatformMgr::CurrentPoints() {
    // Local variables
    long rv; // r0
    long points; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C4B18 -> 0x805C4D20
int PlatformMgr::CheckContentSize(class PlatformMgr * const this /* r28 */) {
    // Local variables
    long fileSize; // r31
    unsigned long inodes; // r30
    struct ECContentCatalogInfo * c; // r24
    int i; // r29
    int j; // r23
    long round; // r0
    unsigned long ohblocks; // r1+0x10
    unsigned long ohinodes; // r1+0xC
    int ret; // r0
    unsigned long answer; // r1+0x8
    long result; // r0
    unsigned long userblocks; // r3

    // References
    // -> class Debug TheDebug;
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805C4D20 -> 0x805C4E14
int PlatformMgr::GetContentSize(class PlatformMgr * const this /* r25 */) {
    // Local variables
    unsigned long fileSize; // r29
    struct ECContentCatalogInfo * c; // r28
    int i; // r27
    int j; // r26
    unsigned long ohblocks; // r1+0xC
    unsigned long ohinodes; // r1+0x8
    int ret; // r0
    unsigned long userblocks; // r3
}

// Range: 0x805C4E14 -> 0x805C4EC8
unsigned char PlatformMgr::DeleteContent(class PlatformMgr * const this /* r28 */, unsigned char sd /* r29 */) {
    // Local variables
    unsigned char result; // r31
    int i; // r30
    unsigned char ret; // r0

    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x805C4EC8 -> 0x805C4F94
void PlatformMgr::VerifyDisc() {
    // Local variables
    class File * f; // r31
    int size; // r0

    // References
    // -> static char freadBuf[256];
    // -> static int seekSpot;
}

// Range: 0x805C4F94 -> 0x805C4F9C
unsigned char PlatformMgr::DoDNSLookup() {}

// Range: 0x805C4F9C -> 0x805C4FA4
unsigned char PlatformMgr::FinishDNSLookup() {}

// Range: 0x805C4FA4 -> 0x805C4FB8
unsigned char PlatformMgr::InviteReceived(class PlatformMgr * const this /* r4 */) {
    // Local variables
    unsigned char ret; // r0
}

// Range: 0x805C4FB8 -> 0x805C505C
unsigned char PlatformMgr::OnMsg(class PlatformMgr * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x805C505C -> 0x805C5068
void WiiMessagingNotificationHandler::DeliverInstantMessage() {}

// Range: 0x805C5068 -> 0x805C5070
int PlatformMgr::GetLastDWCError() {}

// Range: 0x805C5070 -> 0x805C5120
unsigned char PlatformMgr::SetParentalControlPin(class PlatformMgr * const this /* r30 */, class String & pin /* r31 */) {
    // Local variables
    int rv; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805C5120 -> 0x805C51AC
void PlatformMgr::CheckDPD() {
    // Local variables
    long i; // r31

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A54B1C
static class Symbol _s; // size: 0x4, address: 0x80A54B24
static class Symbol _s; // size: 0x4, address: 0x80A54B2C
static class Symbol _s; // size: 0x4, address: 0x80A54B34
static class Symbol _s; // size: 0x4, address: 0x80A54B3C
static class Symbol _s; // size: 0x4, address: 0x80A54B44
static class Symbol _s; // size: 0x4, address: 0x80A54B4C
static class Symbol _s; // size: 0x4, address: 0x80A54B54
static class Symbol _s; // size: 0x4, address: 0x80A54B5C
static class Symbol _s; // size: 0x4, address: 0x80A54B64
static class Symbol _s; // size: 0x4, address: 0x80A54B6C
static class Symbol _s; // size: 0x4, address: 0x80A54B74
static class Symbol _s; // size: 0x4, address: 0x80A54B7C
static class Symbol _s; // size: 0x4, address: 0x80A54B84
static class Symbol _s; // size: 0x4, address: 0x80A54B8C
static class Symbol _s; // size: 0x4, address: 0x80A54B94
static class Symbol _s; // size: 0x4, address: 0x80A54B9C
static class Symbol _s; // size: 0x4, address: 0x80A54BA4
static class Symbol _s; // size: 0x4, address: 0x80A54BAC
static class Symbol _s; // size: 0x4, address: 0x80A54BB4
static class Symbol _s; // size: 0x4, address: 0x80A54BBC
static class Symbol _s; // size: 0x4, address: 0x80A54BC4
static class Symbol _s; // size: 0x4, address: 0x80A54BCC
static class Symbol _s; // size: 0x4, address: 0x80A54BD4
static class Symbol _s; // size: 0x4, address: 0x80A54BDC
static class Symbol _s; // size: 0x4, address: 0x80A54BE4
static class Symbol _s; // size: 0x4, address: 0x80A54BEC
static class Symbol _s; // size: 0x4, address: 0x80A54BF4
static class Symbol _s; // size: 0x4, address: 0x80A54BFC
static class Symbol _s; // size: 0x4, address: 0x80A54C04
static class Symbol _s; // size: 0x4, address: 0x80A54C0C
static class Symbol _s; // size: 0x4, address: 0x80A54C14
static class Symbol _s; // size: 0x4, address: 0x80A54C1C
static class Symbol _s; // size: 0x4, address: 0x80A54C24
static class Symbol _s; // size: 0x4, address: 0x80A54C2C
static class Symbol _s; // size: 0x4, address: 0x80A54C34
static class Symbol _s; // size: 0x4, address: 0x80A54C3C
static class Symbol _s; // size: 0x4, address: 0x80A54C44
static class Symbol _s; // size: 0x4, address: 0x80A54C4C
static class Symbol _s; // size: 0x4, address: 0x80A54C54
static class Symbol _s; // size: 0x4, address: 0x80A54C5C
static class Symbol _s; // size: 0x4, address: 0x80A54C64
static class Symbol _s; // size: 0x4, address: 0x80A54C6C
static class Symbol _s; // size: 0x4, address: 0x80A54C74
static class Symbol _s; // size: 0x4, address: 0x80A54C7C
static class Symbol _s; // size: 0x4, address: 0x80A54C84
static class Symbol _s; // size: 0x4, address: 0x80A54C8C
static class Symbol _s; // size: 0x4, address: 0x80A54C94
static class Symbol _s; // size: 0x4, address: 0x80A54C9C
static class Symbol _s; // size: 0x4, address: 0x80A54CA4
static class Symbol _s; // size: 0x4, address: 0x80A54CAC
static class Symbol _s; // size: 0x4, address: 0x80A54CB4
static class Symbol _s; // size: 0x4, address: 0x80A54CBC
static class Symbol _s; // size: 0x4, address: 0x80A54CC4
static class Symbol _s; // size: 0x4, address: 0x80A54CCC
static class Symbol _s; // size: 0x4, address: 0x80A54CD4
static class Symbol _s; // size: 0x4, address: 0x80A54CDC
static class Symbol _s; // size: 0x4, address: 0x80A54CE4
static class Symbol _s; // size: 0x4, address: 0x80A54CEC
static class Symbol _s; // size: 0x4, address: 0x80A54CF4
static class Symbol _s; // size: 0x4, address: 0x80A54CFC
static class Symbol _s; // size: 0x4, address: 0x80A54D04
static class Symbol _s; // size: 0x4, address: 0x80A54D0C
static class Symbol _s; // size: 0x4, address: 0x80A54D14
static class Symbol _s; // size: 0x4, address: 0x80A54D1C
static class Symbol _s; // size: 0x4, address: 0x80A54D24
// Range: 0x805C51AC -> 0x805C6F04
class DataNode PlatformMgr::Handle(class PlatformMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xC
} __vt__24WiiControllerOverflowMsg; // size: 0xC, address: 0x80925790
struct {
    // total size: 0x8
} __RTTI__24WiiControllerOverflowMsg; // size: 0x8, address: 0x809257C8
struct {
    // total size: 0xC
} __vt__15WiiDiscErrorMsg; // size: 0xC, address: 0x809257D0
struct {
    // total size: 0x8
} __RTTI__15WiiDiscErrorMsg; // size: 0x8, address: 0x80925800
struct {
    // total size: 0x6C
} __vt__11PlatformMgr; // size: 0x6C, address: 0x80925868
struct {
    // total size: 0x8
} __RTTI__11PlatformMgr; // size: 0x8, address: 0x80925900
struct {
    // total size: 0x10
} __vt__Q211PlatformMgr31WiiMessagingNotificationHandler; // size: 0x10, address: 0x80925908
struct {
    // total size: 0x8
} __RTTI__Q211PlatformMgr31WiiMessagingNotificationHandler; // size: 0x8, address: 0x80925960
struct {
    // total size: 0xC
} __vt__26NetStartUtilityFinishedMsg; // size: 0xC, address: 0x80925A80
struct {
    // total size: 0x8
} __RTTI__26NetStartUtilityFinishedMsg; // size: 0x8, address: 0x80925AB8
struct {
    // total size: 0x24
} __vt__Q26Quazal11TextMessage; // size: 0x24, address: 0x80925AF8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11TextMessage; // size: 0x8, address: 0x80925B68
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16_DDL_TextMessage; // size: 0x8, address: 0x80925BB8
struct {
    // total size: 0xC
} __vt__Q26Quazal40CustomDataHolder<Q26Quazal11UserMessage>; // size: 0xC, address: 0x80925BC0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal40CustomDataHolder<Q26Quazal11UserMessage>; // size: 0x8, address: 0x80925C10
struct {
    // total size: 0x8
} __RTTI__Q26Quazal28MessagingNotificationHandler; // size: 0x8, address: 0x80925C50
struct {
    // total size: 0x24
} __vt__Q26Quazal11UserMessage; // size: 0x24, address: 0x80925C58
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11UserMessage; // size: 0x8, address: 0x80925CB8
struct {
    // total size: 0xC
} __vt__Q26Quazal16MessageRecipient; // size: 0xC, address: 0x80925CC0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16MessageRecipient; // size: 0x8, address: 0x80925D00
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16_DDL_UserMessage; // size: 0x8, address: 0x80925D40
struct {
    // total size: 0xC
} __vt__Q26Quazal21_DDL_MessageRecipient; // size: 0xC, address: 0x80925D48
struct {
    // total size: 0x8
} __RTTI__Q26Quazal21_DDL_MessageRecipient; // size: 0x8, address: 0x80925D80
struct {
    // total size: 0xC
} __vt__Q26Quazal48AnyObjectHolder<Q26Quazal4Data,Q26Quazal6String>; // size: 0xC, address: 0x80925E10
struct {
    // total size: 0x8
} __RTTI__Q26Quazal48AnyObjectHolder<Q26Quazal4Data,Q26Quazal6String>; // size: 0x8, address: 0x80925E60
struct {
    // total size: 0x8
} __RTTI__Q26Quazal22Holder<Q26Quazal4Data>; // size: 0x8, address: 0x80925E88
struct {
    // total size: 0x8
} __RTTI__Q26Quazal4Data; // size: 0x8, address: 0x80925EB8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal9_DDL_Data; // size: 0x8, address: 0x80925EE0
struct {
    // total size: 0x8
} __RTTI__PPQ26Quazal11TextMessage; // size: 0x8, address: 0x80926020
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std43_Rb_tree_node<Q211stlpmtx_std11pair<CUl,b>>; // size: 0x8, address: 0x80926090
// Range: 0x805C6F04 -> 0x805C6F54
static void __sinit_\PlatformMgr_Wii_cpp() {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

struct {
    // total size: 0x24
} __vt__Q26Quazal16_DDL_TextMessage; // size: 0x24, address: 0x80973720
const class DateTime & Never; // size: 0x4, address: 0x80A55EA8
struct {
    // total size: 0x24
} __vt__Q26Quazal16_DDL_UserMessage; // size: 0x24, address: 0x809759B8

