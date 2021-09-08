#ifndef WIFINETWORK_H_INCLUDED
#define WIFINETWORK_H_INCLUDED

#include "appconfig.h"
#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "lwip/netif.h"

typedef struct
{
    bool isap;//�Ƿ�ΪAP
    char ssid[33];
    char password[65];
    int  channel;

} wifinetwork_cfg_t;

typedef struct
{
    union
    {
        struct
        {
            uint32_t is_enable:1;//�Ƿ���������
            uint32_t is_ap:1;//�Ƿ�Ϊapģʽ

            uint32_t is_connect_ap:1;//�Ƿ�����·����
            uint32_t is_sta_ip_ok:1;//�ͻ���ģʽ�Ƿ���䵽ip��ַ

            uint32_t is_ap_running:1;//�Ƿ�ɹ���AP
            uint32_t softap_sta_num:8;//APģʽ�Ŀͻ�������
        };
        uint32_t status;
    };
    const struct netif *stanetif;//�ͻ���ģʽ�µ�����ָ��,���ڶ�ȡIP��ַ�ȡ���ΪNULL��
    const struct netif *apnetif;//APģʽ�µ�����ָ��,���ڶ�ȡIP��ַ�ȡ���ΪNULL��
} wifinetwork_status_t;

//��ʼ��wifinetwork
void wifinetwork_init();

void wifinetwork_set_config(wifinetwork_cfg_t cfg);

wifinetwork_cfg_t wifinetwork_get_config();

wifinetwork_status_t wifinetwork_get_status();

//����ʼ��wifinetwork
void wifinetwork_deinit();

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // WIFINETWORK_H_INCLUDED
