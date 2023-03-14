#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h" //For the temperature sensor, analog to digital
#include "hardware/gpio.h"
#include "hardware/pwm.h"

void main(){
    const int ADC_Port = 2;
    const float conversion_factor = 3.3f/ (1<<12);
    const int GPIO_LED_Port = 14;
    const int wrap = 65535;

    //Initialize serial output for usb and gpios.
    stdio_init_all();
    gpio_set_function(GPIO_LED_Port, GPIO_FUNC_PWM);

    //Initialize the pwm port
    //Get the slice and channel number.
    uint Slice_Num = pwm_gpio_to_slice_num(GPIO_LED_Port);
    uint channel = pwm_gpio_to_channel(GPIO_LED_Port);

    //get the defualt pwm settings
    pwm_config settings = pwm_get_default_config();

    //Intialize the pwm. Wrap is set to the max for a 16 bit.
    pwm_set_wrap(Slice_Num, wrap);

    //Initialize adc
    adc_init();
    adc_select_input(ADC_Port);//Need to select which ADC, can only read one at a time.
    
    while(true)
    {
        //adc reads 0-4095 (12 bit integer). Duty cycle needs to be 16 bit integer that represents the % of time the pulse is high.
        uint16_t raw = adc_read();
        uint16_t duty_cycle = (raw*65535)/4095;
        printf("Poti value is: %u, \n", raw);
        
        pwm_set_chan_level(Slice_Num, channel, duty_cycle);
        pwm_set_enabled(Slice_Num, true);
        sleep_ms(10);
    }

}