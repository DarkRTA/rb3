/****************************************************************************
**
** Name:         vendor_api.h
**
** Description:  Vendor specific BTE API function external definitions.
**
** Copyright (c) 2009-2011, BROADCOM Inc., All Rights Reserved.
** Broadcom Bluetooth Core. Proprietary and confidential.
**
******************************************************************************/
#ifndef VENDOR_API_H
#define VENDOR_API_H

#include "bt_types.h"
#include "btm_api.h"


/*************************************
**  VENDOR BLE specific definitions
**************************************/
enum
{
    BTM_BLE_SCAN_COND_ADD,
    BTM_BLE_SCAN_COND_DELETE,
    BTM_BLE_SCAN_COND_CLEAR = 2
};
typedef UINT8 tBTM_BLE_SCAN_COND_OP;

/* filter selection bit index  */
#define BTM_BLE_PF_ADDR_FILTER          0
#define BTM_BLE_PF_SRVC_DATA            1
#define BTM_BLE_PF_SRVC_UUID            2
#define BTM_BLE_PF_SRVC_SOL_UUID        3
#define BTM_BLE_PF_LOCAL_NAME           4
#define BTM_BLE_PF_MANU_DATA            5
#define BTM_BLE_PF_SRVC_DATA_PATTERN    6
#define BTM_BLE_PF_TYPE_ALL             7  /* when passed in payload filter type all, only clear action is applicable */
#define BTM_BLE_PF_TYPE_MAX             8

typedef UINT8   tBTM_BLE_PF_COND_TYPE;

#define BTM_BLE_PF_LOGIC_OR              0
#define BTM_BLE_PF_LOGIC_AND             1
typedef UINT8 tBTM_BLE_PF_LOGIC_TYPE;

/* max number of filter spot for different filter type */
#ifndef BTM_BLE_MAX_UUID_FILTER
#define BTM_BLE_MAX_UUID_FILTER     8
#endif
#ifndef BTM_BLE_MAX_ADDR_FILTER
#define BTM_BLE_MAX_ADDR_FILTER     8
#endif
#ifndef BTM_BLE_PF_STR_COND_MAX
#define BTM_BLE_PF_STR_COND_MAX     4   /* apply to manu data , or local name */
#endif
#ifndef BTM_BLE_PF_STR_LEN_MAX
#define BTM_BLE_PF_STR_LEN_MAX      20  /* match for first 20 bytes */
#endif

#define BTM_BLE_PF_ENABLE       1
#define BTM_BLE_PF_CONFIG       2
typedef UINT8 tBTM_BLE_PF_ACTION;

/* BLE adv payload filtering operation complete callback */
typedef void (tBTM_BLE_PF_CMPL_CBACK)(tBTM_BLE_PF_ACTION action, tBTM_BLE_PF_COND_TYPE cfg_cond, tBTM_STATUS status);

typedef union
{
      UINT16              uuid16_mask;
      UINT32              uuid32_mask;
      UINT8               uuid128_mask[LEN_UUID_128];
}tBTM_BLE_PF_COND_MASK;

typedef struct
{
    tBLE_BD_ADDR            *p_target_addr;     /* target address, if NULL, generic UUID filter */
    tBT_UUID                uuid;           /* UUID condition */
    tBTM_BLE_PF_LOGIC_TYPE  cond_logic;    /* AND/OR */
    tBTM_BLE_PF_COND_MASK   *p_uuid_mask;           /* UUID mask */
}tBTM_BLE_PF_UUID_COND;

typedef struct
{
    UINT8                   data_len;       /* <= 20 bytes */
    UINT8                   *p_data;
}tBTM_BLE_PF_LOCAL_NAME_COND;

typedef struct
{
    UINT16                  company_id;     /* company ID */
    UINT8                   data_len;       /* <= 20 bytes */
    UINT8                   *p_pattern;
    UINT16                  company_id_mask; /* UUID value mask */
    UINT8                   *p_pattern_mask; /* Manufactuer data matching mask, same length as data pattern,
                                                set to all 0xff, match exact data */
}tBTM_BLE_PF_MANU_COND;

typedef struct
{
    UINT16                  uuid;     /* service ID */
    UINT8                   data_len;       /* <= 20 bytes */
    UINT8                   *p_pattern;
}tBTM_BLE_PF_SRVC_PATTERN_COND;


typedef union
{
    tBLE_BD_ADDR                            target_addr;
    tBTM_BLE_PF_LOCAL_NAME_COND             local_name; /* lcoal name filtering */
    tBTM_BLE_PF_MANU_COND                   manu_data;  /* manufactuer data filtering */
    tBTM_BLE_PF_UUID_COND                   srvc_uuid;  /* service UUID filtering */
    tBTM_BLE_PF_UUID_COND                   solicitate_uuid;   /* solicitated service UUID filtering */
    tBTM_BLE_PF_SRVC_PATTERN_COND           srvc_data;      /* service data pattern */
}tBTM_BLE_PF_COND_PARAM;


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**              VENDOR SPECIFIC BLE FEATURE FUNCTIONS
******************************************************************************/
#if BLE_ANDROID_CONTROLLER_SCAN_FILTER == TRUE

/*******************************************************************************
**
** Function         BTM_BleEnableFilterCondition
**
** Description      This function is called to enable the adv data payload filter
**                  condition.
**
** Parameters       p_target: enabble the filter condition on a target device; if NULL
**                            enable the generic scan condition.
**                  enable: enable or disable the filter condition
**
** Returns          void
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleEnableFilterCondition(BOOLEAN enable,
                                                        tBLE_BD_ADDR *p_target,
                                                        tBTM_BLE_PF_CMPL_CBACK *p_cmpl_cback);

/*******************************************************************************
**
** Function         BTM_BleCfgFilterCondition
**
** Description      This function is called to configure the adv data payload filter
**                  condition.
**
** Parameters       action: to read/write/clear
**                  cond_type: filter condition type.
**                  p_cond: filter condition paramter
**
** Returns          tBTM_STATUS
**
*******************************************************************************/
BTM_API extern tBTM_STATUS BTM_BleCfgFilterCondition(tBTM_BLE_SCAN_COND_OP action,
                                      tBTM_BLE_PF_COND_TYPE cond_type,
                                      tBTM_BLE_PF_COND_PARAM *p_cond,
                                      tBTM_BLE_PF_CMPL_CBACK *p_cmpl_cback);


#endif

#ifdef __cplusplus
}
#endif

#endif
