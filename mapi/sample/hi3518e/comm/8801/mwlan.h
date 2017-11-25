#ifndef _WLAN_H
#define _WLAN_H

typedef unsigned char t_u8;
typedef unsigned short t_u16;
typedef unsigned int t_u32;

#ifndef ETH_ALEN
#define ETH_ALEN            6
#endif

/** Action field value : get */
#ifndef ACTION_GET
#define ACTION_GET  0
#endif

/** Action field value : set */
#ifndef ACTION_SET
#define ACTION_SET  1
#endif


/** Command buffer max length */
#define BUFFER_LENGTH       (2 * 1024)
#define MAX_SSID_LEN       (40)
#define MAX_SECUIRTY_LEN (16)
#define PASS1         "1;ssid="
#define PASS2 	    ";passphrase="



typedef struct _cloud_keep_alive {
    /** id */
	t_u8 mkeep_alive_id;
    /** enable/disable of this id */
	t_u8 enable;
    /** Destination MAC address */
	t_u8 dst_mac[ETH_ALEN];
    /** Source MAC address */
	t_u8 src_mac[ETH_ALEN];
    /** packet send period */
	t_u16 sendInterval;
    /** packet length */
	t_u8 pkt_len;
    /** packet content */
	t_u8 pkt[255];
} cloud_keep_alive;

typedef struct _cloud_pkt_filter {
	t_u8 rpn; //0 - No, 1 - And, 2 -Or
	t_u8 repeat;
    	t_u8 offset;
    	t_u8 len;
    	t_u8 bytes[ETH_ALEN]; 
} cloud_pkt_filter;

typedef struct _cloud_pkt_pattern {
    t_u8 filter_num;
    cloud_pkt_filter filter[7];
} cloud_pkt_pattern;

#if 0
typedef struct _cloud_pkt_pattern {
    t_u8 repeat;
    t_u8 offset;
    t_u8 bytes[ETH_ALEN];  
} cloud_pkt_pattern;
#endif

typedef struct {
    /** Host IP address */
	t_u32 host_ip_addr;
    /** Start IP address */
	t_u32 start_ip_addr;
    /** Sub network mask */
	t_u32 subnet_mask;
    /** Lease time */
	t_u32 lease_time;
    /** Limit count */
	t_u8 limit_count;
    /** enabled / disabled */
	t_u8 is_enabled;
    /** Get / Set action*/
	t_u16 action;
} wlan_ioctl_embedded_dhcp_config;

typedef struct{
	char* ssid;
	t_u8 macaddr[ETH_ALEN];
	char* security;
	t_u8 RSSI;
	t_u8 channel;
}mrvl_ap_info;

typedef struct{
	char* ssid;
	t_u8 encryption;
	t_u8 channel;
}mrvl_softap_status;

typedef struct{
	t_u8 status;
	char* ssid;
	t_u8 macaddr[ETH_ALEN];
	t_u8 encryption;  //Can't get encryption info
}mrvl_sta_status;


typedef enum {	
	MRVL_EVT_SCAN_RESULTS,
	MRVL_EVT_CONNECTED,
	MRVL_EVT_DISCONNECTED,
} mrvl_sta_event;


int mlanutl_common(t_u32 argc, char **argv);
int uaputl_common(t_u32 argc, char **argv);
int mlanutl_keepalive(cloud_keep_alive *mkeep_alive); 
//int mlanutl_cloud_wakeup(cloud_pkt_pattern *pkt);
int mlanutl_wakeup(cloud_pkt_pattern *pkt);
int uaputl_embedded_dhcp_cfg(wlan_ioctl_embedded_dhcp_config *dhcp_cfg);

/* tyep:0 --station type:1 ---softap */
int mrvl_wifi_init(int type);
void mrvl_wifi_exit(void);
int mrvl_wifi_open(struct netif **pnetif);
int mrvl_sta_scan(void);

int mrvl_sta_get_scan_results(mrvl_ap_info results[], int *num);

int mrvl_sta_connect(char *ssid, char *bssid, t_u8 security, char *password);

int mrvl_sta_disconnect(void);

int mrvl_sta_get_status(mrvl_sta_status *status);

typedef void (*mrvl_sta_event_cb)(mrvl_sta_event event);

int mrvl_sta_register_event_cb(mrvl_sta_event_cb event_cb);
void mrvl_sta_event_handler(mrvl_sta_event event);

int mrvl_softap_start(char *ssid, int security, char *password, int channel);

int mrvl_softap_stop(void);

int mrvl_softap_get_status(mrvl_softap_status *status);


#endif
