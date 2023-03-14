#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

static SemaphoreHandle_t mutex; //Create a mutex

void task1()
{
    char ch = '1';
    while(true)
    {
        if(xSemaphoreTake(mutex,0) == pdTRUE) //If the mutex is available
        {
        
        for(int i=1; i<10; i++)
        {
            printf("%c", ch);
        }
        printf(" done\n");
        xSemaphoreGive(mutex);
        
        }
    }
    
}

void task2()
{
    char ch = '2';
    while(true)
    {
        if(xSemaphoreTake(mutex,0) == pdTRUE) //If the mutex is available
        {
        
        for(int i=1; i<10; i++)
        {
            printf("%c", ch);
        }
        printf(" done\n");
        xSemaphoreGive(mutex);
        }
    }
   
    
}

    int main(){
        stdio_init_all();

        mutex = xSemaphoreCreateMutex();
        
        xTaskCreate(task1, "LED_Task", 256, NULL, 1, NULL);
        xTaskCreate(task2, "USB_Task", 256, NULL, 1, NULL);
        vTaskStartScheduler();
        
        while(1){}
    }