/*****************************************************************/ /**
* @file qosa_ble.h
* @brief BLE operation interface
*
* @copyright Copyright (c) 2023 Quectel Wireless Solution, Co., Ltd.
* All Rights Reserved. Quectel Wireless Solution Proprietary and Confidential.
**********************************************************************/
#ifndef __QOSA_BLE_H__
#define __QOSA_BLE_H__

#include "qosa_def.h"
#include "qosa_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef QOSA_COMPONENT_API_BLE
#define QOSA_COMPONENT_API_BLE 0x8022U
#endif

/** Base value of BLE error codes. */
#define QOSA_BLE_ERRCODE_BASE          (QOSA_COMPONENT_API_BLE << 16)
/** BLE device address length in bytes. */
#define QOSA_BLE_ADDR_LEN              6
/** Maximum GAP device name length in bytes, excluding string terminator. */
#define QOSA_BLE_NAME_MAX_LEN          32
/** Maximum legacy advertising data length in bytes. */
#define QOSA_BLE_ADV_DATA_MAX_LEN      31
/** Maximum extended/periodic advertising data length in bytes. */
#define QOSA_BLE_EXT_ADV_DATA_MAX_LEN  255
/** Maximum number of advertising sets supported by this API. */
#define QOSA_BLE_MAX_ADV_SETS          4
/** Invalid advertising-set handle sentinel. */
#define QOSA_BLE_INVALID_ADV_HANDLE    ((qosa_ble_adv_handle_t)0)
/** Maximum ATT MTU value in bytes. */
#define QOSA_BLE_ATT_MTU_MAX           517
/** Maximum L2CAP CoC MTU used by this API in bytes. */
#define QOSA_BLE_COC_MTU_MAX           512
/** 32-bit UUID length in bytes. */
#define QOSA_BLE_UUID_32_LEN           4
/** 128-bit UUID length in bytes. */
#define QOSA_BLE_UUID_128_LEN          16
/** Common BLE data buffer upper bound in bytes. */
#define QOSA_BLE_DATA_MAX_LEN          512
/** Invalid local GATT attribute ID sentinel. */
#define QOSA_BLE_INVALID_ATTR_ID       0xFFFF
/** Invalid connection handle sentinel. */
#define QOSA_BLE_INVALID_CONN          ((qosa_ble_conn_t)0)
/** Invalid L2CAP CoC channel handle sentinel. */
#define QOSA_BLE_COC_INVALID_CHAN      ((qosa_ble_coc_chan_t)0)
/** Invalid L2CAP CoC PSM sentinel. */
#define QOSA_BLE_COC_PSM_INVALID       ((qosa_ble_coc_psm_t)0)

/** GATT characteristic supports Read. */
#define QOSA_BLE_GATT_PROP_READ        (1U << 1)
/** GATT characteristic supports Write Without Response. */
#define QOSA_BLE_GATT_PROP_WRITE_CMD   (1U << 2)
/** GATT characteristic supports Write Request. */
#define QOSA_BLE_GATT_PROP_WRITE_REQ   (1U << 3)
/** GATT characteristic supports Notification. */
#define QOSA_BLE_GATT_PROP_NOTI        (1U << 4)
/** GATT characteristic supports Indication. */
#define QOSA_BLE_GATT_PROP_INDI        (1U << 5)

/** Read requires encryption, MITM not required. */
#define QOSA_BLE_GATT_PERM_READ_UNAUTH     (1U << 8)
/** Read requires authenticated encryption with MITM protection. */
#define QOSA_BLE_GATT_PERM_READ_AUTH       (2U << 8)
/** Read requires LE Secure Connections. */
#define QOSA_BLE_GATT_PERM_READ_SEC_CONN   (3U << 8)
/** Write requires encryption, MITM not required. */
#define QOSA_BLE_GATT_PERM_WRITE_UNAUTH    (1U << 10)
/** Write requires authenticated encryption with MITM protection. */
#define QOSA_BLE_GATT_PERM_WRITE_AUTH      (2U << 10)
/** Write requires LE Secure Connections. */
#define QOSA_BLE_GATT_PERM_WRITE_SEC_CONN  (3U << 10)
/** Notification/indication requires encryption, MITM not required. */
#define QOSA_BLE_GATT_PERM_NI_UNAUTH       (1U << 12)
/** Notification/indication requires authenticated encryption with MITM protection. */
#define QOSA_BLE_GATT_PERM_NI_AUTH         (2U << 12)
/** Notification/indication requires LE Secure Connections. */
#define QOSA_BLE_GATT_PERM_NI_SEC_CONN     (3U << 12)
/** Read requires application authorization. */
#define QOSA_BLE_GATT_PERM_READ_AUTHOR     (1U << 14)
/** Write requires application authorization. */
#define QOSA_BLE_GATT_PERM_WRITE_AUTHOR    (2U << 14)

typedef enum
{
    QOSA_BLE_SUCCESS = 0,
    QOSA_BLE_EXECUTE_ERR = 1 | QOSA_BLE_ERRCODE_BASE,
    QOSA_BLE_MEM_ADDR_NULL_ERR,
    QOSA_BLE_OPEN_REPEAT_ERR,
    QOSA_BLE_NOT_OPEN_ERR,
    QOSA_BLE_INVALID_PARAM_ERR,
    QOSA_BLE_BUSY_ERR,
    QOSA_BLE_NO_RESOURCE_ERR,
    QOSA_BLE_NOT_CONNECTED_ERR,
    QOSA_BLE_NOT_SUPPORT_ERR,
    QOSA_BLE_SEC_ERR,
    QOSA_BLE_TIMEOUT_ERR,
} qosa_ble_error_e;

/** Opaque BLE connection handle returned by QOSA_BLE_EVT_CONN. */
typedef void *qosa_ble_conn_t;
/** L2CAP CoC channel handle allocated by the BLE stack. */
typedef qosa_uint16_t qosa_ble_coc_chan_t;
/** L2CAP CoC SPSM value. */
typedef qosa_uint16_t qosa_ble_coc_psm_t;
/** Token used to match an incoming CoC connection request and response. */
typedef qosa_uint32_t qosa_ble_coc_token_t;
/** Application-defined local GATT attribute ID used for GATTS event routing. */
typedef qosa_uint16_t qosa_ble_attr_id_t;
/** Opaque advertising-set handle returned by qosa_ble_adv_set(). */
typedef void *qosa_ble_adv_handle_t;

typedef struct qosa_ble_evt_s qosa_ble_evt_t;
/**
 * @brief BLE event callback.
 *
 * Event payload buffers are valid only before the callback returns. Copy data
 * inside the callback if the application needs to keep it.
 */
typedef void (*qosa_ble_cb_t)(const qosa_ble_evt_t *evt);

/**
 * @struct qosa_ble_data_t
 * @brief Data buffer descriptor used by GAP, GATT and CoC APIs.
 */
typedef struct
{
    qosa_uint8_t *data; /*!< Buffer address. */
    qosa_uint16_t len;  /*!< Buffer length in bytes. */
} qosa_ble_data_t;

/**
 * @struct qosa_ble_cb_cfg_t
 * @brief BLE callback configuration.
 */
typedef struct
{
    qosa_ble_cb_t cb; /*!< Event callback; QOSA_NULL disables callback reporting. */
    void *user_data;  /*!< User context passed through qosa_ble_evt_t::user_data. */
} qosa_ble_cb_cfg_t;

typedef enum
{
    QOSA_BLE_GAP_AD_TYPE_FLAGS = 0x01,
    QOSA_BLE_GAP_AD_TYPE_INC_16BIT_SVC_UUID = 0x02,
    QOSA_BLE_GAP_AD_TYPE_CMP_16BIT_SVC_UUID = 0x03,
    QOSA_BLE_GAP_AD_TYPE_INC_32BIT_SVC_UUID = 0x04,
    QOSA_BLE_GAP_AD_TYPE_CMP_32BIT_SVC_UUID = 0x05,
    QOSA_BLE_GAP_AD_TYPE_INC_128BIT_SVC_UUID = 0x06,
    QOSA_BLE_GAP_AD_TYPE_CMP_128BIT_SVC_UUID = 0x07,
    QOSA_BLE_GAP_AD_TYPE_SHORT_NAME = 0x08,
    QOSA_BLE_GAP_AD_TYPE_COMPLETE_NAME = 0x09,
    QOSA_BLE_GAP_AD_TYPE_TX_POWER = 0x0A,
    QOSA_BLE_GAP_AD_TYPE_CLASS_OF_DEVICE = 0x0D,
    QOSA_BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C = 0x0E,
    QOSA_BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RAND_R = 0x0F,
    QOSA_BLE_GAP_AD_TYPE_DEVICE_ID = 0x10,
    QOSA_BLE_GAP_AD_TYPE_SMP_TK_VALUE = 0x11,
    QOSA_BLE_GAP_AD_TYPE_SMP_OOB_FLAGS = 0x12,
    QOSA_BLE_GAP_AD_TYPE_SLAVE_CONN_INTERVAL = 0x14,
    QOSA_BLE_GAP_AD_TYPE_SVC_SOL_16BIT_UUID = 0x15,
    QOSA_BLE_GAP_AD_TYPE_SERVICE_DATA_16BIT = 0x16,
    QOSA_BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDR = 0x17,
    QOSA_BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDR = 0x18,
    QOSA_BLE_GAP_AD_TYPE_APPEARANCE = 0x19,
    QOSA_BLE_GAP_AD_TYPE_ADV_INTERVAL = 0x1A,
    QOSA_BLE_GAP_AD_TYPE_LE_ADDR = 0x1B,
    QOSA_BLE_GAP_AD_TYPE_LE_ROLE = 0x1C,
    QOSA_BLE_GAP_AD_TYPE_URI = 0x24,
    QOSA_BLE_GAP_AD_TYPE_MFG_DATA = 0xFF,
} qosa_ble_gap_ad_type_e;

typedef enum
{
    QOSA_BLE_GAP_AD_FLAG_LE_LIMITED_DISCOVERABLE = 0x01,
    QOSA_BLE_GAP_AD_FLAG_LE_GENERAL_DISCOVERABLE = 0x02,
    QOSA_BLE_GAP_AD_FLAG_BR_EDR_NOT_SUPPORTED = 0x04,
    QOSA_BLE_GAP_AD_FLAG_SIMUL_LE_BR_EDR_CONTROLLER = 0x08,
    QOSA_BLE_GAP_AD_FLAG_SIMUL_LE_BR_EDR_HOST = 0x10,
} qosa_ble_gap_ad_flag_e;

typedef enum
{
    QOSA_BLE_ADV_MODE_UNDIRECT = 0x01,
    QOSA_BLE_ADV_MODE_DIRECT = 0x02,
    QOSA_BLE_ADV_MODE_NON_CONN_NON_SCAN = 0x03,
    QOSA_BLE_ADV_MODE_NON_CONN_SCAN = 0x04,
    QOSA_BLE_ADV_MODE_HDC_DIRECT = 0x05,
    QOSA_BLE_ADV_MODE_BEACON = 0x06,
    QOSA_BLE_ADV_MODE_EXTEND_CONN_UNDIRECT = 0x11,
    QOSA_BLE_ADV_MODE_EXTEND_CONN_DIRECT = 0x12,
    QOSA_BLE_ADV_MODE_EXTEND_NON_CONN_SCAN = 0x13,
    QOSA_BLE_ADV_MODE_EXTEND_NON_CONN_SCAN_DIRECT = 0x14,
    QOSA_BLE_ADV_MODE_EXTEND_NON_CONN_NON_SCAN = 0x15,
    QOSA_BLE_ADV_MODE_EXTEND_NON_CONN_NON_SCAN_DIRECT = 0x16,
    QOSA_BLE_ADV_MODE_PER_ADV_UNDIRECT = 0x21,
    QOSA_BLE_ADV_MODE_PER_ADV_DIRECT = 0x22,
} qosa_ble_adv_mode_e;

typedef enum
{
    QOSA_BLE_ADDR_PUBLIC = 0,
    QOSA_BLE_ADDR_RANDOM_STATIC = 1,
    QOSA_BLE_ADDR_RANDOM_PRIVATE = 2,
} qosa_ble_addr_type_e;

typedef enum
{
    QOSA_BLE_UUID_SIZE_NONE = 0,
    QOSA_BLE_UUID_SIZE_16 = 2,
    QOSA_BLE_UUID_SIZE_32 = 4,
    QOSA_BLE_UUID_SIZE_128 = 16,
} qosa_ble_uuid_size_e;

typedef enum
{
    QOSA_BLE_PHY_NONE = 0,
    QOSA_BLE_PHY_LE_1M = 1,
    QOSA_BLE_PHY_LE_2M = 2,
    QOSA_BLE_PHY_LE_CODED = 3,
} qosa_ble_phy_e;

typedef enum
{
    QOSA_BLE_ATTR_SERVICE = 0,
    QOSA_BLE_ATTR_CHAR_DECL = 1,
    QOSA_BLE_ATTR_CHAR = 2,
    QOSA_BLE_ATTR_DESC = 3,
} qosa_ble_attr_type_e;

typedef enum
{
    QOSA_BLE_EVT_READY = 0,
    QOSA_BLE_EVT_ADV_ON,
    QOSA_BLE_EVT_ADV_OFF,
    QOSA_BLE_EVT_SCAN_ON,
    QOSA_BLE_EVT_SCAN_OFF,
    QOSA_BLE_EVT_SCAN_REP,
    QOSA_BLE_EVT_CONN,
    QOSA_BLE_EVT_DISC,
    QOSA_BLE_EVT_MTU,
    QOSA_BLE_EVT_PARAM,
    QOSA_BLE_EVT_SEC,
    QOSA_BLE_EVT_GATTS_READ,
    QOSA_BLE_EVT_GATTS_WRITE,
    QOSA_BLE_EVT_GATTS_SENT,
    QOSA_BLE_EVT_GATTS_ATT_INFO,
    QOSA_BLE_EVT_GATTC_DISCOVER,
    QOSA_BLE_EVT_GATTC_READ,
    QOSA_BLE_EVT_GATTC_WRITE,
    QOSA_BLE_EVT_GATTC_NOTIFY,
    QOSA_BLE_EVT_GATTC_INDICATE,
    QOSA_BLE_EVT_GATTC_SVC_DISC,
    QOSA_BLE_EVT_GATTC_CHAR_DISC,
    QOSA_BLE_EVT_GATTC_DESC_DISC,
    QOSA_BLE_EVT_GATT_LINK_CREATE,
    QOSA_BLE_EVT_GATT_LINK_LOST,
    QOSA_BLE_EVT_COC_REGISTERED,
    QOSA_BLE_EVT_COC_UNREGISTERED,
    QOSA_BLE_EVT_COC_CONNECT_REQ,
    QOSA_BLE_EVT_COC_CONNECTED,
    QOSA_BLE_EVT_COC_DISCONNECTED,
    QOSA_BLE_EVT_COC_SENT,
    QOSA_BLE_EVT_COC_RECV,
    QOSA_BLE_EVT_COC_MTU,
    QOSA_BLE_EVT_CONNECTING,
    QOSA_BLE_EVT_CONNECTION_FAILED,
    QOSA_BLE_EVT_RSSI,
    QOSA_BLE_EVT_LINK_VERSION,
    QOSA_BLE_EVT_LINK_FEATURE,
    QOSA_BLE_EVT_PKT_SIZE,
    QOSA_BLE_EVT_CH_MAP,
    QOSA_BLE_EVT_PHY_UPDATE,
    QOSA_BLE_EVT_PHY_REJECT,
    QOSA_BLE_EVT_PEER_NAME,
    QOSA_BLE_EVT_PEER_APPEARANCE,
    QOSA_BLE_EVT_PARAM_REJECT,
} qosa_ble_evt_id_e;

typedef enum
{
    QOSA_BLE_CONN_PERIPH = 0,
    QOSA_BLE_CONN_CENTRAL = 1,
} qosa_ble_conn_role_e;

typedef enum
{
    QOSA_BLE_SEC_PAIR_REQ = 0,
    QOSA_BLE_SEC_KEY_INPUT,
    QOSA_BLE_SEC_NUM_CONFIRM,
    QOSA_BLE_SEC_DONE,
    QOSA_BLE_SEC_SEC_REQ,
    QOSA_BLE_SEC_ENCRYPT_REQ,
    QOSA_BLE_SEC_OOB_REQ,
    QOSA_BLE_SEC_OOB_DATA,
} qosa_ble_sec_evt_e;

typedef enum
{
    QOSA_BLE_SEND_NOTIFY = 0,
    QOSA_BLE_SEND_INDICATE = 1,
} qosa_ble_send_type_e;

typedef enum
{
    QOSA_BLE_SCAN_PASSIVE = 0,
    QOSA_BLE_SCAN_ACTIVE = 1,
} qosa_ble_scan_type_e;

typedef enum
{
    QOSA_BLE_IO_CAP_NONE = 0,
    QOSA_BLE_IO_CAP_DISPLAY_ONLY,
    QOSA_BLE_IO_CAP_DISPLAY_YESNO,
    QOSA_BLE_IO_CAP_KEYBOARD_ONLY,
    QOSA_BLE_IO_CAP_KEYBOARD_DISP,
    QOSA_BLE_IO_CAP_NO_IO,
} qosa_ble_io_cap_e;

typedef enum
{
    QOSA_BLE_COC_SEC_NONE = 0,
    QOSA_BLE_COC_SEC_ENCRYPTED,
    QOSA_BLE_COC_SEC_AUTHENTIC,
} qosa_ble_coc_sec_e;

/**
 * @struct qosa_ble_addr_t
 * @brief BLE device address in display byte order.
 */
typedef struct
{
    qosa_uint8_t value[QOSA_BLE_ADDR_LEN]; /*!< 6-byte address, high byte first, e.g. C6:55:44:33:22:11. */
    qosa_ble_addr_type_e type;             /*!< Address type. */
} qosa_ble_addr_t;

/**
 * @struct qosa_ble_uuid_t
 * @brief BLE UUID value descriptor.
 */
typedef struct
{
    qosa_uint8_t size;                         /*!< UUID length: QOSA_BLE_UUID_SIZE_16/32/128. */
    qosa_uint8_t value[QOSA_BLE_UUID_128_LEN]; /*!< UUID value in Bluetooth little-endian order; use first size bytes. */
} qosa_ble_uuid_t;

/**
 * @struct qosa_ble_cfg_t
 * @brief BLE stack initialization configuration.
 */
typedef struct
{
    qosa_ble_cb_cfg_t cb_cfg;        /*!< Initial event callback configuration. */
    qosa_bool_t has_ble_addr;        /*!< QOSA_TRUE to use ble_addr; QOSA_FALSE to use platform default address. */
    qosa_ble_addr_t ble_addr;        /*!< Optional local BLE address, only effective during qosa_ble_init(). */
    const char *device_name;         /*!< Optional GAP device name string; QOSA_NULL means not set. */
    qosa_uint16_t device_name_len;   /*!< GAP device name length in bytes; 0 means not set. */
    qosa_uint16_t device_appearance; /*!< GAP appearance value; 0 means unknown/default. */
} qosa_ble_cfg_t;

/**
 * @struct qosa_ble_cap_t
 * @brief Read-only platform BLE capability returned by qosa_ble_get_cap().
 */
typedef struct
{
    qosa_bool_t periph;             /*!< Peripheral role support. */
    qosa_bool_t central;            /*!< Central role support. */
    qosa_bool_t phy_2m;             /*!< LE 2M PHY support. */
    qosa_bool_t phy_update;         /*!< PHY update procedure support. */
    qosa_bool_t data_len_ext;       /*!< Data Length Extension support. */
    qosa_bool_t security;           /*!< SMP pairing, bonding and encryption support. */
    qosa_bool_t coc;                /*!< L2CAP CoC support. */
    qosa_bool_t ext_adv;            /*!< Extended advertising support. */
    qosa_bool_t periodic_adv;       /*!< Periodic advertising support. */
    qosa_uint8_t max_conn;          /*!< Maximum simultaneous BLE connections. */
    qosa_uint8_t max_bond;          /*!< Maximum bonded peers. */
    qosa_uint16_t max_mtu;          /*!< Maximum ATT MTU. */
    qosa_uint8_t max_adv_data;      /*!< Maximum legacy advertising data length. */
    qosa_uint16_t max_ext_adv_data; /*!< Maximum extended advertising data length. */
    qosa_uint8_t max_coc_chan;      /*!< Maximum CoC channels per connection. */
    qosa_uint16_t max_coc_mtu;      /*!< Maximum CoC MTU. */
    qosa_uint8_t max_coc_psm;       /*!< Maximum registered CoC services. */
} qosa_ble_cap_t;

/**
 * @struct qosa_ble_info_t
 * @brief BLE runtime state snapshot returned by qosa_ble_get_info().
 */
typedef struct
{
    qosa_bool_t opened;     /*!< BLE stack has been initialized. */
    qosa_bool_t ready;      /*!< BLE stack is ready to execute operations. */
    qosa_uint8_t adv_cnt;   /*!< Number of active advertising sets. */
    qosa_bool_t scan_on;    /*!< QOSA_TRUE if scan is running. */
    qosa_bool_t connecting; /*!< QOSA_TRUE if a Central connection procedure is pending. */
    qosa_uint8_t conn_num;  /*!< Number of active BLE connections. */
} qosa_ble_info_t;

/**
 * @struct qosa_ble_adv_t
 * @brief Advertising set configuration.
 */
typedef struct
{
    qosa_ble_adv_mode_e mode;       /*!< Advertising mode; 0 uses QOSA_BLE_ADV_MODE_UNDIRECT. */
    qosa_ble_data_t adv_data;       /*!< Advertising payload; copied by qosa_ble_adv_set(). */
    qosa_ble_data_t rsp_data;       /*!< Scan response payload; copied by qosa_ble_adv_set(). */
    qosa_uint16_t interval;         /*!< Advertising interval in ms; 0 uses platform default. */
    qosa_uint8_t timeout;           /*!< Advertising timeout; 0 means continuous if supported. */
    qosa_ble_phy_e second_phy;      /*!< Secondary advertising PHY for extended/periodic advertising. */
    qosa_uint8_t adv_sid;           /*!< Advertising SID 0x00-0x0F; 0 may use platform default. */
    qosa_uint8_t max_skip;          /*!< Maximum skipped AUX_ADV_IND events for extended advertising. */
    qosa_uint16_t per_adv_interval; /*!< Periodic advertising interval in ms; 0 uses platform default. */
    qosa_ble_addr_t peer_addr;      /*!< Directed advertising target address. */
    qosa_ble_data_t per_adv_data;   /*!< Periodic advertising payload; copied by qosa_ble_adv_set(). */
} qosa_ble_adv_t;

/**
 * @struct qosa_ble_scan_t
 * @brief BLE scan configuration.
 */
typedef struct
{
    qosa_ble_scan_type_e type; /*!< Active or passive scan. */
    qosa_uint16_t interval;    /*!< Scan interval in 0.625 ms units; 0 uses platform default. */
    qosa_uint16_t window;      /*!< Scan window in 0.625 ms units; must be <= interval. */
    qosa_uint32_t duration;    /*!< Scan duration in 10 ms units; 0 scans until qosa_ble_scan_stop(). */
    qosa_bool_t dup_filter;    /*!< QOSA_TRUE to filter duplicate advertising reports. */
    qosa_ble_phy_e phy_mode;   /*!< Scan PHY; 0 uses platform default LE 1M. */
} qosa_ble_scan_t;

/**
 * @struct qosa_ble_conn_param_t
 * @brief BLE connection timing parameters.
 */
typedef struct
{
    qosa_uint16_t interval_min; /*!< Minimum connection interval in 1.25 ms units. */
    qosa_uint16_t interval_max; /*!< Maximum connection interval in 1.25 ms units. */
    qosa_uint16_t latency;      /*!< Peripheral latency in connection events. */
    qosa_uint16_t timeout;      /*!< Supervision timeout in 10 ms units. */
} qosa_ble_conn_param_t;

/**
 * @struct qosa_ble_conn_cfg_t
 * @brief Central connection configuration.
 */
typedef struct
{
    qosa_ble_addr_t peer;              /*!< Target peer address. */
    qosa_ble_conn_param_t param;       /*!< Requested connection parameters. */
    qosa_ble_addr_type_e own_addr_type;/*!< Local address type used to connect; 0 uses platform default. */
    qosa_ble_phy_e phy_mode;           /*!< Initiating PHY; 0 uses platform default LE 1M. */
} qosa_ble_conn_cfg_t;

/**
 * @struct qosa_ble_attr_t
 * @brief Local GATT Server database attribute.
 */
typedef struct
{
    qosa_ble_uuid_t uuid;      /*!< Attribute UUID. */
    qosa_uint16_t prop;        /*!< Attribute property/permission bitmask: QOSA_BLE_GATT_PROP_* | QOSA_BLE_GATT_PERM_*. */
    qosa_uint16_t max_size;    /*!< Maximum attribute value length in bytes. */
    qosa_uint8_t *p_data;      /*!< Initial/static value pointer; QOSA_NULL means app handles read/write events. */
    qosa_ble_attr_id_t id;     /*!< Application-defined stable local attribute ID. */
    qosa_ble_attr_type_e type; /*!< Attribute type. */
} qosa_ble_attr_t;

/**
 * @struct qosa_ble_db_t
 * @brief Local static GATT Server database descriptor.
 */
typedef struct
{
    const qosa_ble_attr_t *attrs; /*!< Ordered attribute table; should keep static lifetime. */
    qosa_uint16_t count;          /*!< Number of entries in attrs. */
} qosa_ble_db_t;

/** GATT Server read request event payload. */
typedef struct
{
    qosa_ble_conn_t conn;        /*!< Peer connection handle. */
    qosa_ble_attr_id_t attr_id;  /*!< Local attribute ID being read. */
    qosa_uint16_t offset;        /*!< Read offset. */
} qosa_ble_read_req_t;
/** GATT Server read response parameter. */
typedef struct
{
    qosa_ble_conn_t conn;        /*!< Peer connection handle. */
    qosa_ble_attr_id_t attr_id;  /*!< Local attribute ID. */
    qosa_ble_error_e status;     /*!< Read result. */
    qosa_ble_data_t value;       /*!< Response value when status is success. */
} qosa_ble_read_rsp_t;
/** GATT Server write request event payload. */
typedef struct
{
    qosa_ble_conn_t conn;        /*!< Peer connection handle. */
    qosa_ble_attr_id_t attr_id;  /*!< Local attribute ID being written. */
    qosa_uint16_t offset;        /*!< Write offset. */
    qosa_bool_t need_rsp;        /*!< QOSA_TRUE if application must call qosa_ble_gatts_write_rsp(). */
    qosa_ble_data_t value;       /*!< Written value, valid until callback returns. */
} qosa_ble_write_req_t;
/** GATT Server write response parameter. */
typedef struct
{
    qosa_ble_conn_t conn;        /*!< Peer connection handle. */
    qosa_ble_attr_id_t attr_id;  /*!< Local attribute ID. */
    qosa_ble_error_e status;     /*!< Write result. */
} qosa_ble_write_rsp_t;
/** GATT Server notification/indication parameter and sent event payload. */
typedef struct
{
    qosa_ble_conn_t conn;        /*!< Peer connection handle. */
    qosa_ble_attr_id_t attr_id;  /*!< Local characteristic value attribute ID. */
    qosa_ble_send_type_e type;   /*!< Notification or indication. */
    qosa_ble_data_t value;       /*!< Data to send; empty in sent event. */
} qosa_ble_send_t;
/** Advertising start/stop event payload. */
typedef struct
{
    qosa_ble_adv_handle_t handle; /*!< Advertising-set handle. */
    qosa_uint8_t act_id;          /*!< Platform activity ID for diagnostics. */
} qosa_ble_adv_evt_t;
/** GATT Client read parameter. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote ATT handle. */
    qosa_uint16_t offset;     /*!< Read offset. */
} qosa_ble_gatt_read_t;
/** GATT Client write parameter. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote ATT handle. */
    qosa_uint16_t offset;     /*!< Write offset. */
    qosa_ble_data_t value;    /*!< Value to write. */
} qosa_ble_gatt_write_t;
/** GATT Client discovery parameter. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
} qosa_ble_discover_t;
/** GATT Client subscribe parameter. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote characteristic value handle. */
} qosa_ble_subscribe_t;
/** Scan report event payload. */
typedef struct
{
    qosa_ble_addr_t addr;     /*!< Advertiser address. */
    qosa_int8_t rssi;         /*!< RSSI in dBm. */
    qosa_int8_t tx_pwr;       /*!< TX power in dBm if present. */
    qosa_uint8_t evt_type;    /*!< Advertising event type. */
    qosa_uint8_t phy_prim;    /*!< Primary PHY. */
    qosa_uint8_t phy_second;  /*!< Secondary PHY, 0 if not present. */
    qosa_uint8_t adv_sid;     /*!< Advertising SID for extended/periodic reports. */
    qosa_ble_data_t data;     /*!< Advertising or scan response payload. */
} qosa_ble_scan_report_t;
/** Connection established event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< Connection handle for later operations. */
    qosa_ble_conn_role_e role;    /*!< Local role in this connection. */
} qosa_ble_conn_info_t;
/** Disconnection event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Disconnected handle, invalid after callback returns. */
    qosa_uint8_t reason;      /*!< Controller disconnect reason code. */
} qosa_ble_disc_t;
/** ATT MTU update event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Connection handle. */
    qosa_uint16_t mtu;        /*!< New ATT MTU. */
} qosa_ble_mtu_upd_t;
/** Connection parameter update/request event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< Connection handle. */
    qosa_bool_t is_req;           /*!< QOSA_TRUE when peer requests parameters and response is required. */
    qosa_ble_conn_param_t param;  /*!< Requested or effective connection parameters. */
} qosa_ble_param_upd_t;
/** SMP/security event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_ble_sec_evt_e evt;   /*!< Security event type. */
    qosa_ble_error_e status;  /*!< Valid for QOSA_BLE_SEC_DONE. */
    qosa_uint32_t passkey;    /*!< Passkey or numeric-comparison value when applicable. */
} qosa_ble_sec_t;
/** SMP/security configuration. */
typedef struct
{
    qosa_ble_io_cap_e io_cap;  /*!< Local IO capability. */
    qosa_bool_t mitm;          /*!< QOSA_TRUE to require MITM protection. */
    qosa_bool_t lesc;          /*!< QOSA_TRUE to prefer LE Secure Connections. */
    qosa_bool_t bond;          /*!< QOSA_TRUE to distribute/store bonding keys. */
} qosa_ble_sec_param_t;
/** L2CAP CoC service registration parameter. */
typedef struct
{
    qosa_ble_coc_psm_t psm;       /*!< Local SPSM to register. */
    qosa_ble_coc_sec_e sec;       /*!< Minimum security level. */
    qosa_uint16_t default_rx_mtu; /*!< Default local receive MTU. */
    qosa_uint8_t max_chan;        /*!< Maximum accepted channels per connection. */
    qosa_bool_t auto_accept;      /*!< QOSA_TRUE to accept incoming CoC requests automatically. */
} qosa_ble_coc_service_t;
/** L2CAP CoC connection parameter. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_psm_t psm;       /*!< Remote SPSM. */
    qosa_uint8_t chan_count;      /*!< Requested channel count. */
    qosa_uint16_t local_rx_mtu;   /*!< Local receive MTU. */
} qosa_ble_coc_connect_t;
/** L2CAP CoC incoming connection response parameter. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle copied from request. */
    qosa_ble_coc_token_t token;   /*!< Request token copied from event. */
    qosa_bool_t accept;           /*!< QOSA_TRUE to accept. */
    qosa_uint8_t chan_count;      /*!< Accepted channel count. */
    qosa_uint16_t local_rx_mtu;   /*!< Local receive MTU. */
} qosa_ble_coc_connect_rsp_t;
/** L2CAP CoC send parameter. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Target CoC channel. */
    qosa_ble_data_t value;        /*!< Data to send. */
} qosa_ble_coc_send_t;
/** L2CAP CoC MTU update parameter. */
typedef struct
{
    qosa_ble_conn_t conn;             /*!< BLE connection handle. */
    qosa_ble_coc_chan_t *channels;    /*!< Channel handle array. */
    qosa_uint8_t chan_count;          /*!< Number of channels in array. */
    qosa_uint16_t local_rx_mtu;       /*!< New local receive MTU. */
} qosa_ble_coc_mtu_update_t;
/** L2CAP CoC disconnect parameter. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Channel to disconnect. */
} qosa_ble_coc_disconnect_t;

/** GATT Client discovered service information. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< Peer connection handle. */
    qosa_uint16_t start_handle;   /*!< Service start handle. */
    qosa_uint16_t end_handle;     /*!< Service end handle. */
    qosa_ble_uuid_t uuid;         /*!< Service UUID. */
    qosa_bool_t primary;          /*!< QOSA_TRUE for primary service. */
} qosa_ble_gattc_svc_info_t;
/** GATT Client discovered characteristic information. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< Peer connection handle. */
    qosa_uint16_t start_handle;   /*!< Declaration start handle. */
    qosa_uint16_t end_handle;     /*!< Characteristic end handle. */
    qosa_uint16_t value_handle;   /*!< Characteristic value handle. */
    qosa_ble_uuid_t uuid;         /*!< Characteristic UUID. */
} qosa_ble_gattc_char_info_t;
/** GATT Client discovered descriptor information. */
typedef struct
{
    qosa_ble_uuid_t uuid;     /*!< Descriptor UUID. */
    qosa_uint16_t handle;     /*!< Descriptor ATT handle. */
} qosa_ble_gattc_desc_info_t;
/** GATT Client read response event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote ATT handle. */
    qosa_ble_data_t value;    /*!< Read value. */
    qosa_ble_error_e status;  /*!< Read status. */
} qosa_ble_gattc_read_info_t;
/** GATT Client write response event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote ATT handle. */
    qosa_ble_error_e status;  /*!< Write status. */
} qosa_ble_gattc_write_info_t;
/** GATT Client notification/indication event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< Peer connection handle. */
    qosa_uint16_t handle;     /*!< Remote characteristic value handle. */
    qosa_ble_data_t value;    /*!< Notification or indication value. */
} qosa_ble_gattc_notify_info_t;
/** CoC registered/unregistered event payload. */
typedef struct
{
    qosa_ble_coc_psm_t psm;   /*!< Registered or unregistered PSM. */
} qosa_ble_coc_registered_t;
/** Incoming CoC connection request event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_token_t token;   /*!< Token required in qosa_ble_coc_connect_rsp(). */
    qosa_ble_coc_psm_t psm;       /*!< Requested local PSM. */
    qosa_uint8_t chan_count;      /*!< Requested channel count. */
    qosa_uint16_t peer_rx_mtu;    /*!< Peer receive MTU. */
} qosa_ble_coc_req_t;
/** CoC channel connected event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Channel handle. */
    qosa_uint16_t local_rx_mtu;   /*!< Local receive MTU. */
    qosa_uint16_t peer_rx_mtu;    /*!< Peer receive MTU. */
} qosa_ble_coc_chan_info_t;
/** CoC channel disconnected event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Channel handle. */
    qosa_uint8_t reason;          /*!< Disconnect reason. */
} qosa_ble_coc_disc_t;
/** CoC data received event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Source channel handle. */
    qosa_ble_data_t value;        /*!< Received data, valid until callback returns. */
} qosa_ble_coc_data_t;
/** CoC send completed event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Channel handle. */
} qosa_ble_coc_sent_t;
/** CoC MTU update event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_ble_coc_chan_t chan;     /*!< Channel handle. */
    qosa_uint16_t local_rx_mtu;   /*!< Local receive MTU. */
    qosa_uint16_t peer_rx_mtu;    /*!< Peer receive MTU. */
} qosa_ble_coc_mtu_t;
/** RSSI read result event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_int8_t rssi;         /*!< RSSI in dBm. */
} qosa_ble_rssi_t;
/** Link version event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_uint8_t version;     /*!< Link Layer version. */
    qosa_uint16_t company_id; /*!< Bluetooth company identifier. */
    qosa_uint16_t subversion; /*!< Controller subversion. */
} qosa_ble_link_ver_t;
/** Link feature event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_uint8_t features[8];     /*!< LE feature bitmask. */
} qosa_ble_link_feat_t;
/** Data length update event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_uint16_t tx_octets;  /*!< Max TX payload octets. */
    qosa_uint16_t tx_time;    /*!< Max TX time. */
    qosa_uint16_t rx_octets;  /*!< Max RX payload octets. */
    qosa_uint16_t rx_time;    /*!< Max RX time. */
} qosa_ble_pkt_size_t;
/** Channel map event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_uint8_t map[5];      /*!< LE channel map. */
} qosa_ble_ch_map_t;
/** PHY update event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_uint8_t tx_phy;      /*!< Current TX PHY. */
    qosa_uint8_t rx_phy;      /*!< Current RX PHY. */
} qosa_ble_phy_t;
/** PHY reject event payload. */
typedef struct
{
    qosa_ble_conn_t conn;     /*!< BLE connection handle. */
    qosa_uint8_t reason;      /*!< Reject reason. */
} qosa_ble_phy_reject_t;
/** Peer GAP device name event payload. */
typedef struct
{
    qosa_ble_conn_t conn;                     /*!< BLE connection handle. */
    char name[QOSA_BLE_NAME_MAX_LEN + 1];     /*!< Null-terminated peer name. */
    qosa_uint16_t len;                        /*!< Peer name length in bytes. */
} qosa_ble_peer_name_t;
/** Peer GAP appearance event payload. */
typedef struct
{
    qosa_ble_conn_t conn;         /*!< BLE connection handle. */
    qosa_uint16_t appearance;     /*!< Peer GAP appearance value. */
} qosa_ble_peer_appearance_t;

struct qosa_ble_evt_s
{
    qosa_ble_evt_id_e id;    /*!< Event identifier. */
    qosa_ble_error_e status; /*!< Common event status. */
    void *user_data;         /*!< User context configured by qosa_ble_cb_cfg_t. */
    union
    {
        qosa_ble_conn_info_t conn;                 /*!< QOSA_BLE_EVT_CONN payload. */
        qosa_ble_disc_t disc;                      /*!< QOSA_BLE_EVT_DISC payload. */
        qosa_ble_mtu_upd_t mtu;                    /*!< QOSA_BLE_EVT_MTU payload. */
        qosa_ble_param_upd_t param;                /*!< QOSA_BLE_EVT_PARAM payload. */
        qosa_ble_sec_t sec;                        /*!< QOSA_BLE_EVT_SEC payload. */
        qosa_ble_scan_report_t scan;               /*!< QOSA_BLE_EVT_SCAN_REP payload. */
        qosa_ble_adv_evt_t adv;                    /*!< QOSA_BLE_EVT_ADV_ON/OFF payload. */
        qosa_ble_read_req_t read_req;              /*!< QOSA_BLE_EVT_GATTS_READ payload. */
        qosa_ble_write_req_t write_req;            /*!< QOSA_BLE_EVT_GATTS_WRITE payload. */
        qosa_ble_send_t sent;                      /*!< QOSA_BLE_EVT_GATTS_SENT payload. */
        qosa_ble_gattc_svc_info_t gattc_svc;       /*!< QOSA_BLE_EVT_GATTC_SVC_DISC payload. */
        qosa_ble_gattc_char_info_t gattc_char;     /*!< QOSA_BLE_EVT_GATTC_CHAR_DISC payload. */
        qosa_ble_gattc_desc_info_t gattc_desc;     /*!< QOSA_BLE_EVT_GATTC_DESC_DISC payload. */
        qosa_ble_gattc_read_info_t gattc_read;     /*!< QOSA_BLE_EVT_GATTC_READ payload. */
        qosa_ble_gattc_write_info_t gattc_write;   /*!< QOSA_BLE_EVT_GATTC_WRITE payload. */
        qosa_ble_gattc_notify_info_t gattc_notify; /*!< QOSA_BLE_EVT_GATTC_NOTIFY/INDICATE payload. */
        qosa_ble_coc_registered_t coc_reg;         /*!< QOSA_BLE_EVT_COC_REGISTERED/UNREGISTERED payload. */
        qosa_ble_coc_req_t coc_req;                /*!< QOSA_BLE_EVT_COC_CONNECT_REQ payload. */
        qosa_ble_coc_chan_info_t coc_conn;         /*!< QOSA_BLE_EVT_COC_CONNECTED payload. */
        qosa_ble_coc_disc_t coc_disc;              /*!< QOSA_BLE_EVT_COC_DISCONNECTED payload. */
        qosa_ble_coc_data_t coc_data;              /*!< QOSA_BLE_EVT_COC_RECV payload. */
        qosa_ble_coc_sent_t coc_sent;              /*!< QOSA_BLE_EVT_COC_SENT payload. */
        qosa_ble_coc_mtu_t coc_mtu;                /*!< QOSA_BLE_EVT_COC_MTU payload. */
        qosa_ble_rssi_t rssi;                      /*!< QOSA_BLE_EVT_RSSI payload. */
        qosa_ble_link_ver_t link_ver;              /*!< QOSA_BLE_EVT_LINK_VERSION payload. */
        qosa_ble_link_feat_t link_feat;            /*!< QOSA_BLE_EVT_LINK_FEATURE payload. */
        qosa_ble_pkt_size_t pkt_size;              /*!< QOSA_BLE_EVT_PKT_SIZE payload. */
        qosa_ble_ch_map_t ch_map;                  /*!< QOSA_BLE_EVT_CH_MAP payload. */
        qosa_ble_phy_t phy;                        /*!< QOSA_BLE_EVT_PHY_UPDATE payload. */
        qosa_ble_phy_reject_t phy_reject;          /*!< QOSA_BLE_EVT_PHY_REJECT payload. */
        qosa_ble_peer_name_t peer_name;            /*!< QOSA_BLE_EVT_PEER_NAME payload. */
        qosa_ble_peer_appearance_t peer_appearance;/*!< QOSA_BLE_EVT_PEER_APPEARANCE payload. */
        qosa_uint8_t raw[128];                     /*!< Raw platform-specific payload storage. */
    } data; /*!< Event-specific payload selected by id. */
};

/**
 * @brief Initialize BLE stack and install the initial event callback.
 *
 * Return QOSA_BLE_SUCCESS means the stack is ready and applications may register
 * GATT databases, start advertising or start scanning immediately.
 *
 * @param[in] cfg BLE initialization configuration.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_init(const qosa_ble_cfg_t *cfg);

/**
 * @brief Deinitialize BLE stack and release GAP, GATT, SMP and CoC resources.
 *
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_deinit(void);

/**
 * @brief Update runtime BLE event callback configuration.
 *
 * @param[in] cfg Callback configuration. cfg->cb as QOSA_NULL disables callbacks.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_set_callback(const qosa_ble_cb_cfg_t *cfg);

/**
 * @brief Query platform BLE capabilities.
 *
 * @param[out] c Capability output buffer.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_get_cap(qosa_ble_cap_t *c);

/**
 * @brief Query current BLE runtime state.
 *
 * @param[out] inf Runtime state output buffer.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_get_info(qosa_ble_info_t *inf);

/**
 * @brief Get local BLE address.
 *
 * @param[out] a Local address in display byte order.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_get_addr(qosa_ble_addr_t *a);

/**
 * @brief Create and configure an advertising set.
 *
 * The advertising set is not started automatically; call qosa_ble_adv_start().
 *
 * @param[out] out_handle Returned advertising-set handle.
 * @param[in] adv Advertising configuration.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_adv_set(qosa_ble_adv_handle_t *out_handle, const qosa_ble_adv_t *adv);

/**
 * @brief Start an advertising set.
 *
 * Completion is reported by QOSA_BLE_EVT_ADV_ON.
 *
 * @param[in] handle Advertising-set handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_adv_start(qosa_ble_adv_handle_t handle);

/**
 * @brief Stop an advertising set.
 *
 * Completion is reported by QOSA_BLE_EVT_ADV_OFF.
 *
 * @param[in] handle Advertising-set handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_adv_stop(qosa_ble_adv_handle_t handle);

/**
 * @brief Delete an advertising set and invalidate its handle.
 *
 * @param[in] handle Advertising-set handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_adv_delete(qosa_ble_adv_handle_t handle);

/**
 * @brief Update periodic advertising data while the set exists.
 *
 * @param[in] handle Advertising-set handle.
 * @param[in] data Periodic advertising data buffer.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_per_adv_data_set(qosa_ble_adv_handle_t handle, const qosa_ble_data_t *data);

/**
 * @brief Start BLE scanning.
 *
 * Start result is reported by QOSA_BLE_EVT_SCAN_ON; reports use QOSA_BLE_EVT_SCAN_REP.
 *
 * @param[in] scan Scan configuration.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_scan_start(const qosa_ble_scan_t *scan);

/**
 * @brief Stop BLE scanning.
 *
 * Completion is reported by QOSA_BLE_EVT_SCAN_OFF.
 *
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_scan_stop(void);

/**
 * @brief Initiate a Central role connection procedure.
 *
 * Success is reported by QOSA_BLE_EVT_CONN; a pending attempt may be canceled.
 *
 * @param[in] cfg Connection configuration.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_connect(const qosa_ble_conn_cfg_t *cfg);

/**
 * @brief Cancel a pending connection procedure started by qosa_ble_connect().
 *
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_connect_cancel(void);

/**
 * @brief Disconnect an active BLE connection.
 *
 * Completion is reported by QOSA_BLE_EVT_DISC.
 *
 * @param[in] conn Connection handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_disconnect(qosa_ble_conn_t conn);

/**
 * @brief Request connection parameter update.
 *
 * Result is reported by QOSA_BLE_EVT_PARAM or QOSA_BLE_EVT_PARAM_REJECT.
 *
 * @param[in] conn Connection handle.
 * @param[in] p Requested connection parameters.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_conn_param_update(qosa_ble_conn_t conn, const qosa_ble_conn_param_t *p);

/**
 * @brief Accept or reject peer connection parameter request.
 *
 * Call when QOSA_BLE_EVT_PARAM carries is_req == QOSA_TRUE.
 *
 * @param[in] conn Connection handle.
 * @param[in] accept QOSA_TRUE to accept, QOSA_FALSE to reject.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_conn_param_rsp(qosa_ble_conn_t conn, qosa_bool_t accept);

/**
 * @brief Request ATT MTU exchange.
 *
 * New MTU is reported by QOSA_BLE_EVT_MTU.
 *
 * @param[in] conn Connection handle.
 * @param[in] mtu Requested ATT MTU.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_mtu_exchange(qosa_ble_conn_t conn, qosa_uint16_t mtu);

/**
 * @brief Register local static GATT Server database.
 *
 * db and db->attrs should keep static lifetime after registration.
 *
 * @param[in] db Local GATT database.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gatts_set(const qosa_ble_db_t *db);

/**
 * @brief Respond to a GATT Server read request.
 *
 * @param[in] rsp Read response.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gatts_read_rsp(const qosa_ble_read_rsp_t *rsp);

/**
 * @brief Respond to a GATT Server write request when need_rsp is QOSA_TRUE.
 *
 * @param[in] rsp Write response.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gatts_write_rsp(const qosa_ble_write_rsp_t *rsp);

/**
 * @brief Send a GATT Server notification or indication.
 *
 * Completion is reported by QOSA_BLE_EVT_GATTS_SENT.
 *
 * @param[in] p Send parameters.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gatts_send(const qosa_ble_send_t *p);

/**
 * @brief Register GATT Client event handling.
 *
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gatt_add_client(void);

/**
 * @brief Discover remote GATT services, characteristics and descriptors.
 *
 * Discovery results are reported by GATTC discovery events.
 *
 * @param[in] p Discovery parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gattc_discover(const qosa_ble_discover_t *p);

/**
 * @brief Read a remote GATT attribute by ATT handle.
 *
 * Result is reported by QOSA_BLE_EVT_GATTC_READ.
 *
 * @param[in] p Read parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gattc_read(const qosa_ble_gatt_read_t *p);

/**
 * @brief Write a remote GATT attribute by ATT handle.
 *
 * Result is reported by QOSA_BLE_EVT_GATTC_WRITE.
 *
 * @param[in] p Write parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gattc_write(const qosa_ble_gatt_write_t *p);

/**
 * @brief Subscribe remote characteristic notifications or indications.
 *
 * Notifications use QOSA_BLE_EVT_GATTC_NOTIFY; indications use QOSA_BLE_EVT_GATTC_INDICATE.
 *
 * @param[in] p Subscribe parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_gattc_subscribe(const qosa_ble_subscribe_t *p);

/**
 * @brief Start pairing or link encryption.
 *
 * Security events are reported by QOSA_BLE_EVT_SEC.
 *
 * @param[in] conn Connection handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_pair(qosa_ble_conn_t conn);

/**
 * @brief Accept or reject peer pairing/security request.
 *
 * @param[in] conn Connection handle.
 * @param[in] accept QOSA_TRUE to accept.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_pair_rsp(qosa_ble_conn_t conn, qosa_bool_t accept);

/**
 * @brief Reply to passkey input request.
 *
 * @param[in] conn Connection handle.
 * @param[in] passkey Passkey value, normally 0-999999.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_key_rsp(qosa_ble_conn_t conn, qosa_uint32_t passkey);

/**
 * @brief Reply to numeric comparison request.
 *
 * @param[in] conn Connection handle.
 * @param[in] accept QOSA_TRUE when numbers match.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_num_rsp(qosa_ble_conn_t conn, qosa_bool_t accept);

/**
 * @brief Accept or reject peer encryption request using stored keys.
 *
 * @param[in] conn Connection handle.
 * @param[in] accept QOSA_TRUE to accept encryption.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_encrypt_rsp(qosa_ble_conn_t conn, qosa_bool_t accept);

/**
 * @brief Accept or reject OOB security exchange request.
 *
 * @param[in] conn Connection handle.
 * @param[in] accept QOSA_TRUE to accept OOB procedure.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_sec_oob_rsp(qosa_ble_conn_t conn, qosa_bool_t accept);

/**
 * @brief Configure SMP security parameters.
 *
 * IO capability, MITM, LE Secure Connections and bonding decide pairing method and security level.
 *
 * @param[in] p Security parameters.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_set_sec_param(const qosa_ble_sec_param_t *p);

/**
 * @brief Delete bond information for a peer device.
 *
 * @param[in] peer Peer address.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_delete_bond(const qosa_ble_addr_t *peer);

/**
 * @brief Delete all stored bond information.
 *
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_delete_all_bonds(void);

/**
 * @brief Set TX power for a connection or global/default context.
 *
 * @param[in] conn Connection handle, or QOSA_BLE_INVALID_CONN if global/default is supported.
 * @param[in] tx_power TX power value.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_set_tx_power(qosa_ble_conn_t conn, qosa_int8_t tx_power);

/**
 * @brief Read current RSSI of a connection.
 *
 * Result is reported by QOSA_BLE_EVT_RSSI.
 *
 * @param[in] conn Connection handle.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_read_rssi(qosa_ble_conn_t conn);

/**
 * @brief Request connection PHY update.
 *
 * Result is reported by QOSA_BLE_EVT_PHY_UPDATE or QOSA_BLE_EVT_PHY_REJECT.
 *
 * @param[in] conn Connection handle.
 * @param[in] tx_phy TX PHY, see qosa_ble_phy_e.
 * @param[in] rx_phy RX PHY, see qosa_ble_phy_e.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_set_phy(qosa_ble_conn_t conn, qosa_uint8_t tx_phy, qosa_uint8_t rx_phy);

/**
 * @brief Register an L2CAP CoC service on a PSM.
 *
 * Registration is reported by QOSA_BLE_EVT_COC_REGISTERED.
 *
 * @param[in] svc CoC service configuration.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_register_service(const qosa_ble_coc_service_t *svc);

/**
 * @brief Unregister an L2CAP CoC service.
 *
 * Unregistration is reported by QOSA_BLE_EVT_COC_UNREGISTERED.
 *
 * @param[in] psm Service PSM.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_unregister_service(qosa_ble_coc_psm_t psm);

/**
 * @brief Initiate remote L2CAP CoC connection.
 *
 * Result is reported by QOSA_BLE_EVT_COC_CONNECTED.
 *
 * @param[in] p CoC connection parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_connect(const qosa_ble_coc_connect_t *p);

/**
 * @brief Reply to an incoming L2CAP CoC connection request.
 *
 * Call after QOSA_BLE_EVT_COC_CONNECT_REQ.
 *
 * @param[in] r CoC connection response.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_connect_rsp(const qosa_ble_coc_connect_rsp_t *r);

/**
 * @brief Update local receive MTU for one or more CoC channels.
 *
 * @param[in] p CoC MTU update parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_mtu_update(const qosa_ble_coc_mtu_update_t *p);

/**
 * @brief Disconnect an L2CAP CoC channel.
 *
 * Result is reported by QOSA_BLE_EVT_COC_DISCONNECTED.
 *
 * @param[in] p CoC disconnect parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_disconnect(const qosa_ble_coc_disconnect_t *p);

/**
 * @brief Send data on an L2CAP CoC channel.
 *
 * Completion is reported by QOSA_BLE_EVT_COC_SENT; value.len must not exceed peer RX MTU.
 *
 * @param[in] p CoC send parameter.
 * @return qosa_ble_error_e
 */
qosa_ble_error_e qosa_ble_coc_send(const qosa_ble_coc_send_t *p);

#ifdef __cplusplus
}
#endif

#endif /* __QOSA_BLE_H__ */