#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <queue.h>
#include "pico/stdlib.h"

static QueueHandle_t xQueue = NULL;

void led_task()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN; //The pin for the standard led on the board
    uint uIValueToSend = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(true){
        gpio_put(LED_PIN, 1);
        uIValueToSend = 1;
        xQueueSend(xQueue, &uIValueToSend, 0U); //)Queue name, value, ticks to wait)
        vTaskDelay(100);

        gpio_put(LED_PIN, 0);
        uIValueToSend=0;
        xQueueSend(xQueue, &uIValueToSend, 0U);
        vTaskDelay(100); //100 ticks is about 1 second of a delay
    }
}

void usb_task(void *pvParameters){
    uint uIReceivedValue;
    while(true)
    {
        xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);

        if(uIReceivedValue ==1)
        {
            printf("LED is On \n");
        }
        if(uIReceivedValue == 0)
        {
            printf("LED is Off \n");
        }
    }
}

    int main(){
        stdio_init_all();

    //communicating with unsized int. sizeof(uint) tells it how much space to allocate. 
        xQueue = xQueueCreate(1, sizeof(uint)); //Length of queue is one. only putting in 1 piece of data
        
        xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
        xTaskCreate(usb_task, "USB_Task", 256, NULL, 1, NULL);
        vTaskStartScheduler();
        
        while(1){}
    }