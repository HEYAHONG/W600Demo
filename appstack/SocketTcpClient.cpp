#include "SocketTcpClient.hpp"
#include "appconfig.h"
#include "lwip/errno.h"
#include "errno.h"

static const char *TAG="SocketTcpClient";

SocketTcpClient::SocketTcpClient()
{
    //ctor
    memset(&context,0,sizeof(context));
    hostname=NULL;
    port=0;
}

SocketTcpClient::~SocketTcpClient()
{
    //dtor
    if(__is_task_running())
    {
        __stop_task();
    }
    if(context.taskstack!=NULL)
        tls_mem_free(context.taskstack);

    if(hostname!=NULL)
    {
        tls_mem_free((void *)hostname);
    }
}

SocketTcpClient::SocketTcpClient(const SocketTcpClient& other)
{
    //copy ctor

    if(&other==this)
    {
        return;
    }

    memset(&context,0,sizeof(context));
    hostname=NULL;
    port=0;

    context.cfg=other.context.cfg;
    {
        if(hostname!=NULL)
        {
            tls_mem_free((void *)hostname);
            hostname=NULL;
        }
        if(other.hostname!=NULL && strlen(other.hostname)>0)
        {
            hostname=(char *)tls_mem_alloc(strlen(other.hostname)+1);
            memset(hostname,0,strlen(other.hostname)+1);
            strcpy(hostname,other.hostname);
        }
    }
    port=other.port;
}

SocketTcpClient & SocketTcpClient::operator = (const SocketTcpClient& other)
{
    if(&other==this)
    {
        return *this;
    }

    if(__is_task_running())
    {
        __stop_task();
    }

    context.cfg=other.context.cfg;
    {
        if(hostname!=NULL)
        {
            tls_mem_free((void *)hostname);
            hostname=NULL;
        }
        if(other.hostname!=NULL && strlen(other.hostname)>0)
        {
            hostname=(char *)tls_mem_alloc(strlen(other.hostname)+1);
            memset(hostname,0,strlen(other.hostname)+1);
            strcpy(hostname,other.hostname);
        }
    }
    port=other.port;


    return *this;
}

void SocketTcpClient::__start_task()
{
    vTaskSuspendAll();

    if(__is_task_running())
    {
        xTaskResumeAll();
        return;
    }

    //������
    if(context.cfg.task_priority==0)
    {
        context.cfg.task_priority=1;
    }
    if(context.cfg.task_stack_size<=2048)
    {
        context.cfg.task_stack_size=2048;
    }

    //�����ַ
    if(hostname==NULL || port==0)
    {
        xTaskResumeAll();
        return;
    }

    //����Ҫ�Ļص�����
    if(context.cfg.onloop==NULL)
    {
        xTaskResumeAll();
        return;
    }


    //��������ջ
    if(context.taskstack==NULL)
    {
        context.taskstack=tls_mem_alloc(context.cfg.task_stack_size);
    }
    else
    {
        context.taskstack=tls_mem_realloc(context.taskstack,context.cfg.task_stack_size);
    }


    tls_os_task_create(&context.taskhandle,"socket",__task_entry,this,(u8 *)context.taskstack,context.cfg.task_stack_size,context.cfg.task_priority,0);

    xTaskResumeAll();


}

void SocketTcpClient::__task_entry(void *arg)
{
    SocketTcpClient &m=*(SocketTcpClient *)arg;
    while(true)
    {
        m.socket_loop();
        while(m.context.task_flag.is_pending_stop)
        {
            m.context.task_flag.is_waiting_delete=1;
            vTaskDelay(1);
        }
        vTaskDelay(1);
    }
}

bool SocketTcpClient::__is_task_running()
{
    return context.taskhandle!=NULL;
}
void SocketTcpClient::__stop_task()
{
    if(!__is_task_running())
    {
        return;
    }

    vTaskSuspendAll();

    if(context.task_flag.is_pending_stop)
    {
        xTaskResumeAll();
        return;//�Ѿ�׼��ɾ��
    }

    context.task_flag.is_pending_stop=1;

    xTaskResumeAll();

    TickType_t start_tick=xTaskGetTickCount();

    while((!context.task_flag.is_waiting_delete)&& ((xTaskGetTickCount()-start_tick)<pdMS_TO_TICKS(3000)))
    {
        vTaskDelay(1);
    }

    vTaskDelete(context.taskhandle);

    context.taskhandle=NULL;

    memset(&context.task_flag,0,sizeof(context.task_flag));
}


void SocketTcpClient::setconfig(sockettcpclient_cfg_t _cfg)
{
    if(__is_task_running())
    {
        return;
    }
    context.cfg=_cfg;
}

bool SocketTcpClient::start()//�����еĲ�������
{
    if(hostname==NULL || port ==0)
    {
        return false;
    }

    __start_task();

    return true;
}
bool SocketTcpClient::start(const char * _hostname,uint16_t _port)//����
{
    if(_hostname==NULL || _port ==0)
    {
        return false;
    }
    {
        if(hostname!=NULL)
        {
            tls_mem_free((void *)hostname);
            hostname=NULL;
        }
        if(_hostname!=NULL && strlen(_hostname)>0)
        {
            hostname=(char *)tls_mem_alloc(strlen(_hostname)+1);
            memset(hostname,0,strlen(_hostname)+1);
            strcpy(hostname,_hostname);
        }
    }
    port=_port;
    return start();

}

void SocketTcpClient::stop()//ֹͣ
{
    __stop_task();
}

void SocketTcpClient::socket_loop()
{
    struct sockaddr_in addr;
    fd_set read_fds;
    struct timeval select_timeout= {0,0};
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port=htons(port);

    {
        //ͨ��hostname��ȡip��ַ
        struct hostent *p=gethostbyname(hostname);
        if(p!=NULL)
        {
            memcpy(&addr.sin_addr,p->h_addr_list[0],4);
            printf("%s: %s ip addr=%s\r\n",TAG,hostname,inet_ntoa(addr.sin_addr));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(2000));
            return;
        }
    }

    int socketid=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketid<=0)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
        return;
    }

    if(context.cfg.before_connect!=NULL)
    {
        context.cfg.before_connect(&context.cfg,socketid);
    }


    printf("%s:Connecting %s:%d\r\n",TAG,hostname,(int)port);

    if(connect(socketid,(struct sockaddr *)&addr,sizeof(struct sockaddr))==0)
    {
        {
            //���ý��ճ�ʱΪ5(��ֹ��������)
            int timeout=5;
            setsockopt(socketid,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
        }

        {
            //����keepalive
            int keepalive=60000;
            setsockopt(socketid,IPPROTO_TCP,TCP_KEEPALIVE,&keepalive,sizeof(int));
        }

        if(context.cfg.after_connect!=NULL)
        {
            context.cfg.after_connect(&context.cfg,socketid);
        }

        while(true)
        {
            if(!context.cfg.onloop(&context.cfg,socketid))
            {
                break;
            }

            if(context.task_flag.is_pending_stop)
            {
                break;
            }

            {
                FD_ZERO(&read_fds);
                FD_SET(socketid,&read_fds);
                select_timeout.tv_sec=0;
                select_timeout.tv_usec=0;
                int ret=select(socketid+1,&read_fds,NULL,NULL,&select_timeout);
                if(ret!=0)
                {
                    printf("%s:socket %d select error !! close socket!!\r\n",TAG,socketid);
                    break;
                }
            }
            vTaskDelay(1);
        }

    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    if(context.cfg.before_close!=NULL)
    {
        context.cfg.before_close(&context.cfg,socketid);
    }

    if(socketid>0)
    {
        closesocket(socketid);
    }
    return;
}