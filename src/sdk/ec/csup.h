#include <ec/result.h>

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
    ECResult status; // offset 0x0, size 0x4
    enum ECOperation operation; // offset 0x4, size 0x4
    enum ECOpPhase phase; // offset 0x8, size 0x4
    long isCancelRequested; // offset 0xC, size 0x4
    unsigned long totalSize; // offset 0x10, size 0x4
    unsigned long downloadedSize; // offset 0x14, size 0x4
    long errCode; // offset 0x18, size 0x4
    char errInfo[128]; // offset 0x1C, size 0x80
};

namespace ec {
    unsigned long getExternalErrCode(ECProgress *progress);
}