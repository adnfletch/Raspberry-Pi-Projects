add_executable(Mutexes
main.c)

# pull in common dependencies
target_link_libraries(Mutexes pico_stdlib FreeRTOS_Files)


pico_enable_stdio_usb(Mutexes 1)
pico_enable_stdio_uart(Mutexes 0)
#disable the uart output

# create map/bin/hex file etc.
pico_add_extra_outputs(Mutexes)