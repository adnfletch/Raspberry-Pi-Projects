add_executable(blinkRTOS 
main.c)

# pull in common dependencies
target_link_libraries(blinkRTOS pico_stdlib freertos)


pico_enable_stdio_usb(blinkRTOS 1)
pico_enable_stdio_uart(blinkRTOS 0)
#disable the uart output

# create map/bin/hex file etc.
pico_add_extra_outputs(blinkRTOS)
