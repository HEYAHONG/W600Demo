
#include "MQTT.hpp"
#include "app.h"
#include "stdio.h"
#include "string.h"

static const char * TAG="app";

void app_init()
{
    printf("%s:Init\r\n",TAG);


    //初始化MQTT
    MQTT_Init();

}

void app_loop()
{
    vTaskDelay(1);
}
