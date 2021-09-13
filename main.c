#include "wm_include.h"
#include "stdbool.h"
#include "appconfig.h"
#include "app.h"
#include "wifinetwork.h"


extern unsigned int USER_ADDR_START;
extern unsigned int USER_AREA_LEN;
extern unsigned int EX_USER_ADDR_START;
extern unsigned int EX_USER_AREA_LEN;

static const char * TAG="main";
static uint32_t main_task_stack[1024];
static void main_task(void *arg)
{

#if CONFIG_WIFI_NETWORK == 1
    //初始化WIFINetwork
    wifinetwork_init();
#endif // CONFIG_WIFI_NETWORK

    app_init();

    printf("%s:user flash start=%08X length=%u,ex user flash start=%08X length=%u\r\n",TAG,USER_ADDR_START,USER_AREA_LEN,EX_USER_ADDR_START,EX_USER_AREA_LEN);
    printf("%s:free memory %d bytes\r\n",TAG,tls_mem_get_avail_heapsize());
    printf("%s:main task running\r\ntick=%lu\r\n",TAG,xTaskGetTickCount());


    while(true)
    {
        app_loop();
    }
}


void UserMain(void)
{
    tls_os_task_create(NULL,"main",main_task,NULL,(void *)main_task_stack,sizeof(main_task_stack),1,0);
}

