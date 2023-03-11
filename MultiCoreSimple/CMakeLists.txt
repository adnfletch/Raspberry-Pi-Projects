add_executable(MultiCoreSimple
        MultiCoreSimple.c
        )

# pull in common dependencies
target_link_libraries(MultiCoreSimple
pico_multicore
pico_stdlib
hardware_adc)

pico_enable_stdio_usb(MultiCoreSimple 1)
pico_enable_stdio_uart(MultiCoreSimple 0)

pico_add_extra_outputs(MultiCoreSimple)
