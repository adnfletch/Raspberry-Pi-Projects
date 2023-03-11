#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h" //hardware interrupts
#include "hardware/adc.h" //For the temperature sensor, analog to digital


void core1_entry();
void core1_interrupt_handler();

//Note, core1 and core0 are the two cores on the Raspberry Pi Pico controller. This program will read the temperature on one core
//And print the temperature on another. Extra comments are here for my learning and future reference.
int main()
{
    
    const int Temp_ADC_Port = 4;
    //Initialize serial output for usb
    stdio_init_all();

    multicore_launch_core1(core1_entry); //Start core1_entry function. NEEDS TO BE BEFORE INTERUPTS
    
    adc_init();
    adc_set_temp_sensor_enabled(true); //turn on the temp sensor
    adc_select_input(Temp_ADC_Port);//Need to select which ADC, can only read one at a time.
    
    printf("starting C\n");

    while(true)
    {
        uint16_t raw = adc_read();
        multicore_fifo_push_blocking(raw); //Will push and if the fifo stack is full, it will wait until there is space
        sleep_ms(1000);
    }
}

//Core 1 Main Code
//Configure the interrupt handler, then idle. When an interrupt is called through fifo push, the handler will deal with it, then return to
//The infinite while loop.
void core1_entry()
{
    multicore_fifo_clear_irq(); //clear any old interupts
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler); //Set which function is the interrupt handler
    irq_set_enabled(SIO_IRQ_PROC1, true); //PROC1 is for core 2, PROC0 is for core 1. Enable interrupts

    while(1)
    {
        tight_loop_contents(); //Placeholder, dont want core1_entry to stop executing. Will return to this after interrupts are handled.
    }
}

//Core 1 interrupt handler
void core1_interrupt_handler()
{
    //Receive Raw Value, convert and print temp over the USB port
    while(multicore_fifo_rvalid()) //Rvalid checks if there is data that has been sent.
    {
        uint16_t raw = multicore_fifo_pop_blocking(); //Pop the data from the stack.
        //From the raspberry pi documentation, this is how to get the temperature
        const float convert_factor = 3.3f/(1<<12); //From the raspberry pi documentation
        float result = raw*convert_factor;
        float temp = 27 - (result -0.706)/0.001721;
        printf("Temp = %f C\n", temp);
    }

    multicore_fifo_clear_irq(); // Clear interupts
}