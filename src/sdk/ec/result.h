#ifndef EC_RESULT_H
#define EC_RESULT_H

enum ECResult {
    ECResult_Success = 0,

    ECResult_Failure = -1,

    ECResult_ECFail               = -4001,  /* Generic error */
    ECResult_NotSupported         = -4002,  /* Feature not implemented */
    ECResult_InsufficientResource = -4003,
    ECResult_InvalidBufHeap       = -4004,
    ECResult_NoMemory             = -4005,
    ECResult_NotFound             = -4006,
    ECResult_NotBusy              = -4007,  /* no active async operation */
    ECResult_Busy                 = -4008,
    ECResult_NotDone              = -4009,

    ECResult_NetNotAvailable      = -4013,  /* Internet access not available */
    ECResult_WebServiceError      = -4015,  /* Server reports a problem */
    ECResult_InvalidECard         = -4017,  /* Invalid eCard */
    ECResult_Overflow             = -4018,  /* Output too big for buf provided */
                                            /* Should never see EC_E~~RROR_OVERFLOW */                                  
    ECResult_ContentRecvErr       = -4019,  /* Error getting content from server */
    ECResult_ContentSizeMismatch  = -4020,  /* Downloaded content size doesn't match tmd */

    ECResult_WebServiceResError   = -4034,  /* invalid web service response */
    ECResult_TicketImportErr      = -4035,  /* problem importing ticket */
    ECResult_TMDImportErr         = -4036,  /* problem importing title */
    ECResult_ContentImportErr     = -4037,  /* problem importing title content */
    ECResult_Canceled             = -4038,  /* an extended operation was canceled */
    ECResult_AlreadyInitialized   = -4039,  /* one time only action was previously done */
    ECResult_Init                 = -4041,  /* library has not been initialized */
    ECResult_NotRegistered        = -4042,  /* device is not registered */
    ECResult_RecvWSErr            = -4043,  /* recv error on web service response */
    ECResult_NotActive            = -4044,  /* expected operation is not active op */
    ECResult_FileRead             = -4045,
    ECResult_FileWrite            = -4046,
    ECResult_TitleNotOwned        = -4050,  /* Title is not owned */
    ECResult_BadHeap              = -4051,  /* Bad heap */
    ECResult_HeaderParseErr       = -4052,  /* Could not parse http header */
    ECResult_ConfigErr            = -4053,  /* Invalid configuration (e.g. url is invalid) */
    ECResult_CancelFailed         = -4054,  /* Could not cancel asynchronous operaton */
    ECResult_UserINodes           = -4055,  /* Operation would exceed max user inodes */
    ECResult_UserBlocks           = -4056,  /* Operation would exceed max user blocks */
    ECResult_SystemINodes         = -4057,  /* Operation would exceed max sys inodes */
    ECResult_SystemBlocks         = -4058,  /* Operation would exceed max sys blocks */
    ECResult_NoDeviceCode         = -4065,  /* Operation requires device code */
    ECResult_NeedTicketSync       = -4066,  /* Operation requres ticket sync */
    ECResult_NeedECConnect        = -4069,  /* Operation requires EC_Connect() */
    ECResult_NoTMD                = -4070,  /* Title TMD is not on device */
    ECResult_NeedFirmwareUpdate   = -4071,  /* Title requires updated firmware */
    ECResult_PCPassIncorrect      = -4074,  /* Parental control password doesn't match */
    ECResult_NoPC                 = -4075,  /* Parental control is not enabled */
    ECResult_NeedEULA             = -4076,  /* Customer has not agreed to EULA */
    ECResult_AgeRestricted       = -4077,  /* Opration requires parental control password */
    ECResult_PointsRestricted    = -4078,  /* Opration requires parental control password */
    ECResult_TitleOwned          = -4079,  /* Attempt purchase already owned item */
    ECResult_InsufficientFunds   = -4081,  /* Not enough funds to purchase the item */
    
};

#define EC_SUCCESS(expr) ((expr) >= 0)
#define EC_FAIL(expr) ((expr) < 0)

#endif
