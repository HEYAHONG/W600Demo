﻿#ifndef APPCONFIG_H_INCLUDED
#define APPCONFIG_H_INCLUDED

#ifdef USE_KCONFIG

#include "config.h"

#endif // USE_KCONFIG

/*
默认配置
注意：可通过配置关闭Kconfig,因此config.h中的内容不可直接使用
*/
#ifndef CONFIG_CPP_OP_NEW_DEBUG
#define CONFIG_CPP_OP_NEW_DEBUG 0
#endif // CONFIG_CPP_OP_NEW_DEBUG


#ifndef CONFIG_CPP_OP_DELETE_DEBUG
#define CONFIG_CPP_OP_DELETE_DEBUG 0
#endif // CONFIG_CPP_OP_DELETE_DEBUG

#ifndef CONFIG_CPP_RESET_ON_EXCEPTION
#define CONFIG_CPP_RESET_ON_EXCEPTION 1
#endif // CONFIG_CPP_RESET_ON_EXCEPTION


#ifndef CONFIG_WIFI_NETWORK
#define CONFIG_WIFI_NETWORK 0
#endif // CONFIG_WIFI_NETWORK

#ifndef CONFIG_WIFI_NETWORK_STA
#define CONFIG_WIFI_NETWORK_STA 0
#endif // CONFIG_WIFI_NETWORK_STA

#ifndef CONFIG_WIFI_NETWORK_ROUTER_AP_SSID
#define CONFIG_WIFI_NETWORK_ROUTER_AP_SSID "TestRouter"
#endif // CONFIG_WIFI_NETWORK_ROUTER_AP_SSID

#ifndef CONFIG_WIFI_NETWORK_ROUTER_AP_PASSWORD
#define CONFIG_WIFI_NETWORK_ROUTER_AP_PASSWORD "12345678"
#endif // CONFIG_WIFI_NETWORK_ROUTER_AP_PASSWORD

#ifndef CONFIG_WIFI_NETWORK_SOFTAP
#define CONFIG_WIFI_NETWORK_SOFTAP 0
#endif // CONFIG_WIFI_NETWORK_SOFTAP

#ifndef CONFIG_WIFI_NETWORK_AP_SSID
#define CONFIG_WIFI_NETWORK_AP_SSID "Test"
#endif // CONFIG_WIFI_NETWORK_AP_SSID

#ifndef CONFIG_WIFI_NETWORK_AP_PASSWORD
#define CONFIG_WIFI_NETWORK_AP_PASSWORD "12345678"
#endif // CONFIG_WIFI_NETWORK_AP_PASSWORD

#ifndef CONFIG_WIFI_NETWORK_AP_DNSNAME
#define CONFIG_WIFI_NETWORK_AP_DNSNAME "local.wm"
#endif // CONFIG_WIFI_NETWORK_AP_DNSNAME

#ifndef CONFIG_WIFI_NETWORK_AP_CHANNEL
#define CONFIG_WIFI_NETWORK_AP_CHANNEL 7
#endif // CONFIG_WIFI_NETWORK_AP_CHANNEL

#ifndef CONFIG_PROTOCOL_NTP
#define CONFIG_PROTOCOL_NTP 1
#endif // CONFIG_PROTOCOL_NTP

#ifdef  CONFIG_PROTOCOL_NTP_TIMEZONE
#define CONFIG_PROTOCOL_NTP_TIMEZONE "GMT-8"
#endif // CONFIG_PROTOCOL_NTP_TIMEZONE

#ifndef CONFIG_PROTOCOL_NTP_SERVER_1_IP
#define CONFIG_PROTOCOL_NTP_SERVER_1_IP "114.118.7.163"
#endif // CONFIG_PROTOCOL_NTP_SERVER_1_IP

#ifndef CONFIG_PROTOCOL_NTP_SERVER_2_IP
#define CONFIG_PROTOCOL_NTP_SERVER_2_IP "114.118.7.161"
#endif // CONFIG_PROTOCOL_NTP_SERVER_2_IP

#ifndef CONFIG_PROTOCOL_NTP_SERVER_3_IP
#define CONFIG_PROTOCOL_NTP_SERVER_3_IP "162.159.200.1"
#endif // CONFIG_PROTOCOL_NTP_SERVER_3_IP

#ifndef CONFIG_PROTOC_NTP_CHECK_TIME_INTERVAL
#define CONFIG_PROTOC_NTP_CHECK_TIME_INTERVAL 60
#endif // CONFIG_PROTOC_NTP_CHECK_TIME_INTERVAL


/*
非配置宏定义
*/
#include "FreeRTOS.h"
#include "task.h"
#ifndef pdMS_TO_TICKS
#include "FreeRTOS.h"
#define pdMS_TO_TICKS(x) ((x)/((1000/configTICK_RATE_HZ)))
#endif // pdMS_TO_TICKS

#ifndef TickType_t
#define TickType_t portTickType
#endif // TickType_t

#endif // APPCONFIG_H_INCLUDED
