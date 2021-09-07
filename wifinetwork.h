#ifndef WIFINETWORK_H_INCLUDED
#define WIFINETWORK_H_INCLUDED

#include "appconfig.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct
{
    bool isap;//是否为AP
    char ssid[33];
    char password[65];
    int  channel;

} wifinetwork_cfg_t;

//初始化wifinetwork
void wifinetwork_init();

void wifinetwork_set_config(wifinetwork_cfg_t cfg);

//反初始化wifinetwork
void wifinetwork_deinit();

#endif // WIFINETWORK_H_INCLUDED
