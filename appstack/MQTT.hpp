#ifndef MQTT_HPP
#define MQTT_HPP

#ifdef __cplusplus
#include <string>
#include <functional>
#include <stdint.h>
#include <stdlib.h>
#include "appconfig.h"

typedef struct
{
    std::string host;//主机名
    uint16_t port; //端口
    int keepalive; //保活时间(本代码中不可为0，默认120)
    bool cleansession;//是否开启干净会话
    std::string clientid;
    struct _auth
    {
        std::string username; //用户名
        std::string password;//密码
    } auth;
    struct _will
    {
        std::string will_topic;//遗嘱主题
        std::string will_payload;//遗嘱负载数据
        uint8_t will_qos;//遗嘱qos
        bool will_retain;//遗嘱是否为保留消息
    } will;
    struct _subscribe
    {
        std::string subtopic;//订阅主题
        int qos;//订阅的服务质量
    } subscribe;
} MQTT_Cfg_t;

typedef struct
{
    std::string topic;
    std::string payload;
    uint8_t qos;
    bool retain;
} MQTT_Message_t;


/*
初始化MQTT
*/
void MQTT_Init();

typedef struct
{
    std::function<void(MQTT_Cfg_t &)> init;
    std::function<void(MQTT_Cfg_t &)> connect;
    std::function<void(MQTT_Cfg_t &)> disconnect;
    std::function<void(MQTT_Cfg_t &,MQTT_Message_t &)> onmessage;
} MQTT_Callback_t;

/*
设置回调函数
*/
void MQTT_Set_Callback(MQTT_Callback_t cb);

/*
发布消息
*/
bool MQTT_Publish_Message(MQTT_Message_t & msg);

#endif // __cplusplus


#endif // MQTT_HPP
