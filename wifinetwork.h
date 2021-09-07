#ifndef WIFINETWORK_H_INCLUDED
#define WIFINETWORK_H_INCLUDED

#include "appconfig.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct
{
    bool isap;//�Ƿ�ΪAP
    char ssid[33];
    char password[65];
    int  channel;

} wifinetwork_cfg_t;

//��ʼ��wifinetwork
void wifinetwork_init();

void wifinetwork_set_config(wifinetwork_cfg_t cfg);

//����ʼ��wifinetwork
void wifinetwork_deinit();

#endif // WIFINETWORK_H_INCLUDED
