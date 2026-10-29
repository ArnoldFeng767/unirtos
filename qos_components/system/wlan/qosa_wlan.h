#ifndef __QOSA_WLAN_H__
#define __QOSA_WLAN_H__

#include "qosa_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define QOSA_WLAN_SSID_MAX_LEN          (33U)
#define QOSA_WLAN_PWD_MIN_LEN           (8U)
#define QOSA_WLAN_PWD_MAX_LEN           (64U)
#define QOSA_WLAN_BSSID_SIZE            (6U)
#define QOSA_WLAN_MAC_SIZE              (6U)
#define QOSA_WLAN_MAC_STR_MAX_LEN       (16U)
#define QOSA_WLAN_IPV4_ADDR_LEN         (16U)
#define QOSA_WLAN_DNS_ADDR_LEN          (46U)
#define QOSA_WLAN_IDENTITY_MAX_LEN      (64U)
#define QOSA_WLAN_WPA2_PASSWORD_MAX_LEN (128U)
#define QOSA_WLAN_MAX_IPV6_ADDRESSES    (3U)
#define QOSA_WLAN_ERRCODE_BASE          ((qosa_uint32_t)QOSA_COMPONENT_WIFI << 16)

typedef enum
{
    QOSA_WLAN_SUCCESS = 0,
    QOSA_WLAN_EXECUTE_ERR = 1 | QOSA_WLAN_ERRCODE_BASE,
    QOSA_WLAN_INVALID_PARAM_ERR,
    QOSA_WLAN_NOT_SUPPORTED_ERR,
} qosa_wlan_errcode_e;

typedef enum
{
    QOSA_WLAN_MODE_STA = 0,
    QOSA_WLAN_MODE_AP = 1,
    QOSA_WLAN_MODE_APSTA = 2,
    QOSA_WLAN_MODE_MAX = 3,
} qosa_wlan_mode_e;

typedef enum
{
    QOSA_WLAN_SECURITY_NONE = 0,
    /* WEP is reported by scans but cannot be used to connect. */
    QOSA_WLAN_SECURITY_WEP = 1,
    QOSA_WLAN_SECURITY_WPA = 2,
    QOSA_WLAN_SECURITY_WPA2 = 3,
    QOSA_WLAN_SECURITY_WPA_WPA2_MIXED = 4,
    QOSA_WLAN_SECURITY_WPA3_SAE = 5,
    QOSA_WLAN_SECURITY_WPA2_WPA3_SAE_MIXED = 6,
    QOSA_WLAN_SECURITY_OWE = 7,
    QOSA_WLAN_SECURITY_WPA2_ENTERPRISE = 8,
    QOSA_WLAN_SECURITY_WPA3_ENTERPRISE = 9,
    QOSA_WLAN_SECURITY_MAX,
} qosa_wlan_security_type_e;

typedef enum
{
    QOSA_WLAN_EAP_TLS = 0,
    QOSA_WLAN_EAP_TTLS_MSCHAPV2 = 1,
    QOSA_WLAN_EAP_MAX = 2,
} qosa_wlan_eap_type_e;

typedef enum
{
    QOSA_WLAN_PEAP_TLS = 0,
    QOSA_WLAN_PEAP_MSCHAPV2 = 1,
    QOSA_WLAN_PEAP_GTC = 2,
    QOSA_WLAN_PEAP_MAX = 3,
} qosa_wlan_peap_type_e;

typedef enum
{
    QOSA_WLAN_IP_TYPE_INVALID = 0,
    QOSA_WLAN_IP_TYPE_V4 = 0x01,
    QOSA_WLAN_IP_TYPE_V6 = 0x02,
    QOSA_WLAN_IP_TYPE_ANY = 0x03,
} qosa_wlan_ip_type_e;

typedef enum
{
    QOSA_WLAN_ADDR_TYPE_STATIC = 0,
    QOSA_WLAN_ADDR_TYPE_DHCP = 1,
    QOSA_WLAN_ADDR_TYPE_LLA = 2,
} qosa_wlan_address_type_e;

typedef enum
{
    QOSA_WLAN_EVT_STA_IDLE = 0,
    QOSA_WLAN_EVT_STA_CONNECTING,
    QOSA_WLAN_EVT_STA_BEACON_LOSE,
    QOSA_WLAN_EVT_STA_PASSWORD_WRONG,
    QOSA_WLAN_EVT_STA_NO_AP_FOUND,
    QOSA_WLAN_EVT_STA_DISCONNECTED,
    QOSA_WLAN_EVT_STA_CONNECT_FAILED,
    QOSA_WLAN_EVT_STA_CONNECTED,
    QOSA_WLAN_EVT_STA_GOT_IP,
    QOSA_WLAN_EVT_AP_STARTED,
    QOSA_WLAN_EVT_AP_ASSOCIATED,
    QOSA_WLAN_EVT_AP_CONNECTED,
    QOSA_WLAN_EVT_AP_DISCONNECTED,
    QOSA_WLAN_EVT_AP_CONNECT_FAILED,
    QOSA_WLAN_EVT_AP_STOPPED,
    QOSA_WLAN_EVT_MAX,
} qosa_wlan_evt_e;

typedef enum
{
    QOSA_WLAN_COUNTRY_POLICY_AUTO = 0,
    QOSA_WLAN_COUNTRY_POLICY_MANUAL,
} qosa_wlan_country_policy_e;

typedef struct
{
    qosa_bool_t mfpr;
    qosa_bool_t mfpc;
} qosa_wlan_mfp_cfg_t;

typedef struct
{
    char *cert;
} qosa_wlan_eap_cert_cfg_t;

typedef struct
{
    char eap_ver;
    qosa_wlan_eap_type_e eap_type;
    qosa_wlan_peap_type_e peap_type;
    qosa_wlan_eap_cert_cfg_t cert;
    char identity[QOSA_WLAN_IDENTITY_MAX_LEN];
    char password[QOSA_WLAN_WPA2_PASSWORD_MAX_LEN];
} qosa_wlan_eap_cfg_t;

typedef struct
{
    char cc[3];
    qosa_uint8_t schan;
    qosa_uint8_t nchan;
    qosa_int8_t max_tx_power;
    qosa_wlan_country_policy_e policy;
} qosa_wlan_country_t;

typedef struct
{
    qosa_wlan_address_type_e addr_type;
    char address[QOSA_WLAN_IPV4_ADDR_LEN];
    char gateway[QOSA_WLAN_IPV4_ADDR_LEN];
    char netmask[QOSA_WLAN_IPV4_ADDR_LEN];
    char dns1[QOSA_WLAN_IPV4_ADDR_LEN];
    char dns2[QOSA_WLAN_IPV4_ADDR_LEN];
} qosa_wlan_ipv4_config_t;

typedef struct
{
    /* NUL-terminated IP address; an empty string means unconfigured. */
    char address[QOSA_WLAN_DNS_ADDR_LEN];
} qosa_wlan_dns_server_t;

typedef struct
{
    qosa_wlan_evt_e event;
    void *data;
} qosa_wlan_event_msg_t;

typedef struct
{
    qosa_uint32_t address[4];
    qosa_uint8_t addr_type;
    qosa_uint8_t addr_state;
} qosa_wlan_ipv6_config_t;

typedef struct
{
    qosa_wlan_ipv6_config_t ipv6[QOSA_WLAN_MAX_IPV6_ADDRESSES];
    qosa_size_t ipv6_count;
    qosa_wlan_ipv4_config_t ipv4;
} qosa_wlan_ip_config_t;

typedef struct
{
    qosa_bool_t dhcp_enabled;
    char ssid[QOSA_WLAN_SSID_MAX_LEN + 1];
    char pwd[QOSA_WLAN_PWD_MAX_LEN + 1];
    char bssid[QOSA_WLAN_BSSID_SIZE + 1];
    qosa_wlan_mfp_cfg_t mfp_cfg;
    qosa_wlan_ip_config_t ip;
} qosa_wlan_sta_config_t;

typedef struct
{
    char ssid[QOSA_WLAN_SSID_MAX_LEN];
    char pwd[QOSA_WLAN_PWD_MAX_LEN];
    qosa_uint16_t security;
    qosa_uint16_t channel;
    qosa_uint16_t acs_band;
    qosa_wlan_mfp_cfg_t mfp_cfg;
    qosa_wlan_ip_config_t ip;
} qosa_wlan_uap_config_t;

typedef struct
{
    qosa_wlan_mode_e mode;
    qosa_wlan_sta_config_t *sta_cfg;
    qosa_wlan_uap_config_t *uap_cfg;
} qosa_wlan_network_t;

typedef struct
{
    char ssid[QOSA_WLAN_SSID_MAX_LEN];
    char bssid[QOSA_WLAN_BSSID_SIZE];
    qosa_int16_t rssi;
    qosa_uint16_t channel;
    qosa_uint16_t security;
} qosa_wlan_link_status_t;

typedef struct
{
    qosa_uint8_t dhcp;
    char ip[QOSA_WLAN_IPV4_ADDR_LEN];
    char gw[QOSA_WLAN_IPV4_ADDR_LEN];
    char netmask[QOSA_WLAN_IPV4_ADDR_LEN];
    char dns1[QOSA_WLAN_IPV4_ADDR_LEN];
    char dns2[QOSA_WLAN_IPV4_ADDR_LEN];
    char mac[QOSA_WLAN_MAC_STR_MAX_LEN];
    char broadcastip[QOSA_WLAN_IPV4_ADDR_LEN];
    qosa_wlan_ipv6_config_t ipv6[QOSA_WLAN_MAX_IPV6_ADDRESSES];
    qosa_size_t ipv6_count;
} qosa_wlan_ip_status_t;

/* The event message and its data are valid only during the callback. */
typedef void (*qosa_wlan_event_cb)(void *param);

qosa_wlan_errcode_e qosa_wlan_driver_init(void);
qosa_wlan_errcode_e qosa_wlan_driver_deinit(void);

/* The country code contains exactly three octets, including its environment byte. */
qosa_wlan_errcode_e qosa_wlan_set_country_code(const char *country);
qosa_wlan_errcode_e qosa_wlan_get_country_code(char *country);
qosa_wlan_errcode_e qosa_wlan_get_country(qosa_wlan_country_t *ct);
qosa_wlan_errcode_e qosa_wlan_get_channel(qosa_uint16_t *channel);
qosa_wlan_errcode_e qosa_wlan_set_mac(const qosa_uint8_t *mac);
qosa_wlan_errcode_e qosa_wlan_get_mac(qosa_uint8_t *mac);

qosa_wlan_errcode_e qosa_wlan_start(const qosa_wlan_network_t *network);
qosa_wlan_errcode_e qosa_wlan_start_with_eap(const qosa_wlan_network_t *network, qosa_wlan_eap_cfg_t *eap);
qosa_wlan_errcode_e qosa_wlan_stop(qosa_wlan_mode_e mode);

qosa_wlan_errcode_e qosa_wlan_register_status_cb(qosa_wlan_event_cb cb);
qosa_wlan_errcode_e qosa_wlan_get_link_status(qosa_wlan_link_status_t *status);
/* APSTA is not a valid interface for this query. */
qosa_wlan_errcode_e qosa_wlan_get_ip_status(qosa_wlan_ip_status_t *status, qosa_wlan_mode_e interface);
/*
 * Query the maximum number of DNS server slots supported by the platform.
 * max_count must not be NULL and is cleared on failure. The result is the array
 * length required by set/get, not the number of currently configured servers.
 * This capability query does not require network initialization.
 * Returns QOSA_WLAN_SUCCESS on success, QOSA_WLAN_INVALID_PARAM_ERR for a NULL
 * output, or QOSA_WLAN_NOT_SUPPORTED_ERR if DNS configuration is unavailable.
 */
qosa_wlan_errcode_e qosa_wlan_get_dns_server_max(qosa_size_t *max_count);
/*
 * Replace the complete DNS server configuration for domain name resolution.
 * servers must not be NULL. Query max_count first and pass an array containing
 * exactly that many elements; count must equal max_count. Array indices map to
 * server slots; resolver priority depends on the platform. Each address must
 * be NUL-terminated within its array. An empty address clears that slot; an
 * all-empty array clears all servers. Nonempty addresses must be valid unicast
 * IP literals. IPv4/IPv6 are detected from the strings; support depends on the
 * platform. The server address family does not select the query result family.
 * All elements are validated before any server is changed. Parameter and
 * unsupported-family errors leave the existing configuration unchanged.
 * The return code applies to the whole array, without a failing element index.
 * Call after network initialization from application task context.
 * Returns QOSA_WLAN_SUCCESS, QOSA_WLAN_INVALID_PARAM_ERR for invalid input,
 * QOSA_WLAN_NOT_SUPPORTED_ERR for unsupported DNS configuration/address
 * families, or QOSA_WLAN_EXECUTE_ERR for execution/resource failures.
 */
qosa_wlan_errcode_e qosa_wlan_set_dns_server(const qosa_wlan_dns_server_t servers[], qosa_size_t count);
/*
 * Read the complete DNS server configuration into the caller's array.
 * servers must not be NULL. Query max_count first and allocate exactly that
 * many elements; count must equal max_count. Each slot receives a NUL-terminated
 * IP address, or an empty string if unconfigured. Invalid arguments leave the
 * array untouched; a valid output array is cleared on execution failure.
 * Call after network initialization from application task context.
 * Returns QOSA_WLAN_SUCCESS on success, or a corresponding error code on failure.
 */
qosa_wlan_errcode_e qosa_wlan_get_dns_server(qosa_wlan_dns_server_t servers[], qosa_size_t count);
qosa_wlan_ip_type_e qosa_wlan_check_ip_str_type(const char *ip);

qosa_bool_t qosa_wlan_is_uap_started(void);
qosa_bool_t qosa_wlan_is_sta_connected(void);
qosa_bool_t qosa_wlan_is_sta_ipv4_connected(void);
qosa_bool_t qosa_wlan_is_sta_ipv6_connected(void);

#ifdef __cplusplus
}
#endif

#endif
