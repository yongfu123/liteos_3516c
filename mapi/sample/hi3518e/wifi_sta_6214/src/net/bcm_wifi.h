#ifndef __BCM_WIFI_H__
#define __BCM_WIFI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

enum mhd_security {
    OPEN,
    WPA_PSK_AES,     // WPA-PSK AES
    WPA2_PSK_AES,    // WPA2-PSK AES
    WEP_OPEN,        // WEP+OPEN
    WEP_SHARED,      // WEP+SHARE
    WPA_PSK_TKIP,    // WPA-PSK TKIP
    WPA2_PSK_TKIP,   // WPA2-PSK TKIP
    WPA2_PSK_MIXED   // WPA2-PSK AES & TKIP MIXED
} mhd_security_e;

typedef struct mhd_ap_info {
    char ssid[32];        // AP's ssid
    char bssid[6];        // AP's MAC
    uint32_t channel;     // channel
    uint32_t security;    // refer to enum wwd_security_t
    uint32_t rssi;        // RSSI dBm
} mhd_ap_info_t;

// type for ssid
typedef struct {
    uint8_t len;     /**< SSID length */
    uint8_t val[32]; /**< SSID name (AP name)  */
} ssid_t;

// type for mac address
typedef struct {
    uint8_t octet[6]; /**< Unique 6-byte MAC address */
} mac_t;

// type for easy setup
typedef struct
{
    ssid_t SSID;
    uint8_t security;
    uint8_t channel;
    uint8_t security_key_length;
    char security_key[64];
    mac_t BSSID;
} mhd_es_ap_info_t;

struct ether_addr {
    uint8_t octet[6];
};
 
struct ipv4_addr {
    uint8_t   addr[4];
};

// struct for keep-alive
typedef struct tcpka_conn_ext {
    struct ether_addr dst_mac; /* Destinition Mac */
    struct ipv4_addr src_ip;   /* Sorce IP */
    struct ipv4_addr dst_ip;   /* Destinition IP */
    uint16_t ipid;             /* Ip Identification */
    uint16_t srcport;          /* Source Port Address */
    uint16_t dstport;          /* Destination Port Address */
    uint32_t seqnum;           /* TCP Sequence Number */
    uint32_t acknum;           /* TCP Ack Number */
    uint16_t tcpwin;           /* TCP window */
    uint32_t tsval;            /* Timestamp Value, can be set to 0 */
    uint32_t tsecr;            /* Timestamp Echo Reply, can be set to 0 */
    uint32_t last_payload_len; /* last packet payload len */ 
    uint32_t ka_payload_len;   /* keep alive payload length */
    char *ka_payload;          /* keep alive payload */
} tcpka_conn_ext_t;

// struct for keep-alive timer
typedef struct tcpka_timer {
    uint16_t interval;         // interval between keep-alive
    uint16_t retry_interval;   // retransmit interval of keep-alive packet
    uint16_t retry_count;      // retransmit times of keep-alive packet
} tcpka_timer_t;

// Release APIs
///////////////////////////////////////////////////////////////////////
// gpio_group: GPIO group value
// gpio_offset: GPIO offset value
// gpio_mux_offset: GPIO mux register offset
// gpio_mux_value: GPIO mux register value
// intr: interrupt number
extern void mhd_gpio_oob_register(unsigned char gpio_group, unsigned char gpio_offset,
                             unsigned char gpio_mux_offset, unsigned int gpio_mux_value,
                             unsigned int intr);

// download fw/nvram image, driver init
// return 0:success, 1:failed
extern int mhd_module_init(void);

// scan in station mode
// return 0:success, 1:failed
extern int mhd_start_scan(void);

// get scan result in station mode
// return 0:success, 1:failed
extern int mhd_get_scan_results(mhd_ap_info_t *results, int *num);

// station connects to ap.
// security: refer to enum mhd_security_t
// return 0:success, 1:failed
extern int mhd_sta_connect(char *ssid, char *bssid, uint8_t security, char *password, uint8_t channel);

// station leaves ap and network down
// input 0:not force, 1:force to disconnect
// return 0:success, 1:failed
extern int mhd_sta_disconnect(uint8_t force);

// get station state.
// return 0:disabled, 1:enabled
extern int mhd_sta_get_state(void);

// station get connection state.
// return 0:disconnected, 1:connected
extern int mhd_sta_get_connection(void);

// set station interface up, and start DHCP or config static ip if necessary
// eg1: for DHCP
//      mhd_sta_network_up(0, 0, 0);
// eg2: for static IP ip[192.168.1.98], gateway[192.168.1.1], netmask[255.255.255.0]
//      mhd_sta_network_up(0xc0a80162, 0xc0a80101, 0xffffff00);
extern int mhd_sta_network_up(uint32_t ip, uint32_t gateway, uint32_t netmask);

// set station interface down
extern int mhd_sta_network_down(void);

// set DTIM value for low power
extern int mhd_sta_set_bcn_li_dtim(uint8_t dtim);

// set power save mode
extern int mhd_sta_set_powersave(uint8_t mode, uint8_t time_ms);

// set scan suppress.
extern void mhd_set_scansuppress(int state);

// enable wowl in station mode. input net pattern string and offset, should be called once
// pattern_string: wakeup packet payload
// offset: payload offset in wakeup packet, eg: TCP - 54, UDP - 42
// eg: mhd_wowl_sta_add("0x983B16F8F39C", 54);
extern void mhd_wowl_sta_add(char *pattern_string, int offset);

// enable wowl settings in station mode
extern void mhd_wowl_sta_enable(void);

// disable wowl settings in station mode
extern void mhd_wowl_sta_disable(void);

// function type for network link up/down callback.
typedef void (*mhd_link_callback_t)(void);

// register callback function for network link up and link down.
// return 1: failed, 0: successful
extern int mhd_sta_register_link_callback(mhd_link_callback_t link_up_cb,
                                           mhd_link_callback_t link_down_cb);

// deregister callback function for network link up and link down.
// return 1: failed, 0: successful
extern int mhd_sta_deregister_link_callback(mhd_link_callback_t link_up_cb,
                                             mhd_link_callback_t link_down_cb);

// enable cooee protocol
extern void mhd_es_enable_cooee(void);

// start easy setup
extern int mhd_easy_setup_start(mhd_es_ap_info_t *ap_info);

// stop easy setup
extern int mhd_easy_setup_stop(void);

// start softap
// ssid:  less than 32 bytes
// password: less than 32 bytes
// security: refer to enum wwd_security_t, support only OPEN, WPA_PSK_AES, WPA2_PSK_AES
// channel: 1~13
extern int mhd_softap_start(char *ssid, char *password, uint8_t security, uint8_t channel);

// start DHCP server
// ip_address: 0xc0a80101
extern int mhd_softap_start_dhcpd(uint32_t ip_address);

// stop softap.
// input 0:not force, 1:force to stop
// return 0:success, 1:failed
extern int mhd_softap_stop(uint8_t force);

// get softap state.
// return 0:disabled, 1:enabled
extern int mhd_softap_get_state(void);

// enable wowl in softap mode
extern void mhd_wowl_ap_enable(void);

// clear wowl settings in softap mode
extern void mhd_wowl_ap_disable(void);

// config tcpka.
// return 0:success, 1:failed
extern int mhd_tcpka_config_ext(struct tcpka_conn_ext *session, struct tcpka_timer *timer);

// delete tcpka config.
// return 0:success, 1:failed
extern int mhd_tcpka_clear_ext(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif
