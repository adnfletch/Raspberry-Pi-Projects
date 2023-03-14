add_executable(Matrix
        main.c
        )

# pull in common dependencies
target_link_libraries(Matrix pico_stdlib)

pico_enable_stdio_usb(Matrix 1)
pico_enable_stdio_uart(Matrix 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Matrix)

# add url via pico_set_program_url
example_auto_set_url(Matrix)