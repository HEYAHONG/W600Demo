#include "MQTT.hpp"
#include "MQTT_SMGS.h"
#include "string.h"
#include "libSMGS.h"
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "MQTTFreeRTOS_LWIP.h"
#include "MQTTClient.h"
extern void * cpp_malloc(size_t nsize);
extern void cpp_free(void *p);
#ifdef __cplusplus
}
#endif // __cplusplus
static const char * TAG="MQTT";


/*
MQTT相关
*/
struct Network mqttserver= {0};
struct MQTTClient mqttclient= {0};
uint8_t mqtttxbuff[1024]= {0};
uint8_t mqttrxbuff[1024]= {0};
static MQTT_Cfg_t Cfg;
static MQTT_Callback_t callback;
void MQTT_Set_Callback(MQTT_Callback_t cb)
{
    callback=cb;
}

bool MQTT_Publish_Message(MQTT_Message_t & msg)
{
    auto client=&mqttclient;
    if(client==NULL || client->buf ==NULL || client->buf_size ==0 || client->ipstack==NULL || client->ipstack->mqttwrite==NULL)
    {
        return false;//参数有误
    }
    if(MQTTIsConnected(&mqttclient)==0)
    {
        return false;
    }

    QoS Qos=QOS0;
    switch(msg.qos)
    {
    default:
        break;
    case 0:
        Qos=QOS0;
        break;
    case 1:
        Qos=QOS1;
        break;
    case 2:
        Qos=QOS2;
        break;

    }

    struct MQTTMessage Msg;
    memset(&Msg,0,sizeof(Msg));
    Msg.payload=(char *)msg.payload.c_str();
    Msg.payloadlen=msg.payload.length();
    Msg.qos=Qos;
    Msg.retained=msg.retain;
    return MQTTPublish(&mqttclient,msg.topic.c_str(),&Msg)==0;
}
static bool check_cfg(MQTT_Cfg_t &Cfg)
{
    if(Cfg.host.empty())
    {
        return false;
    }

    if(Cfg.port==0)
    {
        return false;
    }

    if(Cfg.keepalive==0)
    {
        Cfg.keepalive=120;
    }

    if(Cfg.clientid.empty())
    {
        return false;
    }

    return true;
}

//执行ping
static bool mqtt_ping(MQTTClient * client)
{

    if(client==NULL || client->buf ==NULL || client->buf_size ==0 || client->ipstack==NULL || client->ipstack->mqttwrite==NULL)
    {
        return false;//参数有误
    }

    uint8_t buff[8]= {0};
    int len=MQTTSerialize_pingreq(buff,sizeof(buff));
    return len==client->ipstack->mqttwrite(client->ipstack,buff,len,1000);
}

static void mqttmessageHandler(MessageData*msg)
{
    MQTT_Message_t m;
    m.topic=std::string(msg->topicName->lenstring.data,msg->topicName->lenstring.len);
    m.payload=std::string((char *)msg->message->payload,msg->message->payloadlen);
    m.qos=(uint8_t)msg->message->qos;
    m.retain=msg->message->retained;

    if(callback.onmessage!=NULL)
    {
        callback.onmessage(Cfg,m);
    }
}

static void mqtt_receive_task(void *arg)
{
    printf("%s:mqtt task start!!\r\n",TAG);

    while(true)
    {

        while(!check_cfg(Cfg))
        {
            if(callback.init!=NULL)
            {
                printf("%s:wait for config!!\r\n",TAG);
                callback.init(Cfg);
                vTaskDelay(500);
            }
            else
            {
                printf("%s:mqtt not init!!\r\n",TAG);
                vTaskDelay(3000);
            }
        }


        printf("%s:mqtt start!!\r\n",TAG);


        NetworkInit(&mqttserver);
        while(0!=NetworkConnect(&mqttserver,(char *)Cfg.host.c_str(),Cfg.port))
        {
            printf("%s:connect mqtt server!\r\n",TAG);
            vTaskDelay(3000);
        }

        MQTTClientInit(&mqttclient,&mqttserver,3000,mqtttxbuff,sizeof(mqtttxbuff),mqttrxbuff,sizeof(mqttrxbuff));

        {

            MQTTPacket_connectData cfg=MQTTPacket_connectData_initializer;

            //填写KeepAlive
            cfg.keepAliveInterval=Cfg.keepalive;

            //填写clientID
            cfg.clientID.cstring=(char *)Cfg.clientid.c_str();

            //填写cleansession
            cfg.cleansession=Cfg.cleansession;

            //填写用户名与密码
            if(!Cfg.auth.username.empty())
                cfg.username.cstring=(char *)Cfg.auth.username.c_str();
            if(!Cfg.auth.password.empty())
                cfg.password.cstring=(char *)Cfg.auth.password.c_str();

            if(!Cfg.will.will_topic.empty())
            {
                cfg.willFlag=1;
                cfg.will.topicName.cstring=(char *)Cfg.will.will_topic.c_str();
                cfg.will.message.lenstring.data=(char *)Cfg.will.will_payload.c_str();
                cfg.will.message.lenstring.len=Cfg.will.will_payload.length();
                cfg.will.qos=Cfg.will.will_qos;
                cfg.will.retained=Cfg.will.will_retain;
            }



            if(SUCCESS!=MQTTConnect(&mqttclient,&cfg))
            {
                printf("%s:mqtt connect failed!!\r\n",TAG);
                mqttserver.disconnect(&mqttserver);
                vTaskDelay(3000);
                continue;
            }
        }
        {
            if(!Cfg.subscribe.subtopic.empty())
            {
                QoS Qos=QOS0;
                switch(Cfg.subscribe.qos)
                {
                default:
                    break;
                case 0:
                    Qos=QOS0;
                    break;
                case 1:
                    Qos=QOS1;
                    break;
                case 2:
                    Qos=QOS2;
                    break;

                }
                if(SUCCESS!=MQTTSubscribe(&mqttclient,Cfg.subscribe.subtopic.c_str(),Qos,mqttmessageHandler))
                {
                    printf("%s:mqtt subscribe failed!!\r\n",TAG);
                    mqttserver.disconnect(&mqttserver);
                    continue;
                }
            }

        }

        {
            if(callback.connect!=NULL)
            {
                callback.connect(Cfg);
            }
        }

        {
            while(SUCCESS==MQTTYield(&mqttclient,10))
            {
                vTaskDelay(1);
            }
        }


        printf("%s:mqtt yield failed!!restarting!!!\r\n",TAG);

        if(callback.disconnect!=NULL)
        {
            callback.disconnect(Cfg);
        }


        if(mqttserver.disconnect!=NULL)
        {
            mqttserver.disconnect(&mqttserver);
        }

    }

}

static void mqtt_ping_task(void *arg)
{

    TickType_t last_ping_tick=xTaskGetTickCount();
    while(true)
    {
        if(mqttclient.isconnected && xTaskGetTickCount()-last_ping_tick>pdMS_TO_TICKS(Cfg.keepalive*1000/2))//10s ping 一次
        {
            last_ping_tick=xTaskGetTickCount();
            bool is_ok=mqtt_ping(&mqttclient);
            printf("%s:ping %s\r\n",TAG,is_ok?"success":"failed");
        }
        vTaskDelay(1000);
    }

}

uint32_t mqtt_receive_task_stack[4096]= {0};
uint32_t mqtt_ping_task_stack[1024]= {0};

extern "C"
{
#include  "wm_osal.h"
}

tls_os_task_t mqtt_receive_task_handle=NULL;
tls_os_task_t mqtt_ping_task_handle=NULL;
void MQTT_Init()
{

    if(mqtt_receive_task_handle!=NULL &&mqtt_ping_task_handle !=NULL)
    {
        return;
    }
    else
    {
        MQTT_Cfg_t cfg;
        Cfg=cfg;

        //变量初始化
        MQTT_Callback_t cb= {NULL,NULL,NULL,NULL};
        MQTT_Set_Callback(cb);

        cb.init=MQTT_SMGS_Init;
        cb.connect=MQTT_SMGS_Connect;
        cb.disconnect=MQTT_SMGS_DisConnect;
        cb.onmessage=MQTT_SMGS_OnMessage;
        MQTT_Set_Callback(cb);

        {
            Cfg.host="mqtt.hyhsystem.cn";
            Cfg.port=1883;
        }
        printf("%s:Init!\r\n",TAG);
    }


    /*
    由于套接字超时设置无效,因此需要单独的任务执行ping
    */
    tls_os_task_create(&mqtt_receive_task_handle,"mqtt_receive",mqtt_receive_task,NULL,(uint8_t *) mqtt_receive_task_stack,sizeof( mqtt_receive_task_stack),33,0);
    tls_os_task_create(&mqtt_ping_task_handle,"mqtt_ping",mqtt_ping_task,NULL,(uint8_t *) mqtt_ping_task_stack,sizeof( mqtt_ping_task_stack),33,0);
}



