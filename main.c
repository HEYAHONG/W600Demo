#include "wm_include.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"


#ifndef pdMS_TO_TICKS
#include "FreeRTOS.h"
#define pdMS_TO_TICKS(x) ((x)/((1000/configTICK_RATE_HZ)))
#endif // pdMS_TO_TICKS

static const char * TAG="main";
static uint32_t main_task_stack[1024];
static void main_task(void *arg)
{
    while(true)
    {
        printf("%s:main task running\r\ntick=%lu\r\n",TAG,xTaskGetTickCount());
        vTaskDelay((pdMS_TO_TICKS(1000)));
    }
}


void UserMain(void)
{
    tls_os_task_create(NULL,"main",main_task,NULL,(void *)main_task_stack,sizeof(main_task_stack),1,0);
}

