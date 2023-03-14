add_executable(PWM_Light
        main.c
        )

# pull in common dependencies
target_link_libraries(PWM_Light
pico_stdlib
hardware_adc
hardware_pwm)

pico_enable_stdio_usb(PWM_Light 1)
pico_enable_stdio_uart(PWM_Light 0)

pico_add_extra_outputs(PWM_Light)
