#include "wm_include.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"


#ifndef pdMS_TO_TICKS
#include "FreeRTOS.h"
#define pdMS_TO_TICKS(x) ((x)/((1000/configTICK_RATE_HZ)))
#endif // pdMS_TO_TICKS

extern unsigned int USER_ADDR_START;
extern unsigned int USER_AREA_LEN;
extern unsigned int EX_USER_ADDR_START;
extern unsigned int EX_USER_AREA_LEN;

static const char * TAG="main";
static uint32_t main_task_stack[1024];
static void main_task(void *arg)
{

    printf("%s:user flash start=%08X length=%u,ex user flash start=%08X length=%u\r\n",TAG,USER_ADDR_START,USER_AREA_LEN,EX_USER_ADDR_START,EX_USER_AREA_LEN);

    while(true)
    {
        printf("%s:free memory %d bytes\r\n",TAG,tls_mem_get_avail_heapsize());
        printf("%s:main task running\r\ntick=%lu\r\n",TAG,xTaskGetTickCount());

        tls_os_disp_task_stat_info();
        vTaskDelay((pdMS_TO_TICKS(5000)));
    }
}


void UserMain(void)
{
    tls_os_task_create(NULL,"main",main_task,NULL,(void *)main_task_stack,sizeof(main_task_stack),1,0);
}

