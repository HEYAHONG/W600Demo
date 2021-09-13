﻿#include "app.h"
#include "SocketTcpClient.hpp"

static const char * TAG="app";

SocketTcpClient *client=NULL;

extern "C"
{
    //连接前回调函数
    void before_connect(const struct __sockettcpclient_cfg_t * cfg,int socket_fd)
    {
        printf("%s:Socket Create Success! SocketId=%d\r\n",TAG,socket_fd);
    }
    //连接成功后回调函数
    void after_connect(const struct __sockettcpclient_cfg_t *cfg,int socketfd)
    {
        printf("%s:Socket Connect Success! SocketId=%d\r\n",TAG,socketfd);
    }
    //成功连接后循环内回调函数(只能进行发送与接收操作),不可长时间阻塞
    bool onloop(const struct __sockettcpclient_cfg_t *cfg,int socketfd)//返回false重启socket
    {
        char buff[128]= {0};
        int len=recv(socketfd,buff,sizeof(buff)-1,0);
        if(len>0)
        {
            send(socketfd,buff,len,0);
            printf("%s:Socket %d receive data:%s\r\n",TAG,socketfd,buff);
        }

        return true;
    }
    //关闭前回调
    void before_close(const struct __sockettcpclient_cfg_t *cfg,int socketfd)
    {
        printf("%s:Socket Close Success! SocketId=%d\r\n",TAG,socketfd);
    }
}

void app_init()
{
    client=new SocketTcpClient();
    sockettcpclient_cfg_t cfg= {0};
    cfg.before_connect=before_connect;
    cfg.before_close=before_close;
    cfg.after_connect=after_connect;
    cfg.onloop=onloop;
    client->setconfig(cfg);
    client->start("didiyun.hyhsystem.cn",3333);

}

void app_loop()
{
    vTaskDelay(1);
}
