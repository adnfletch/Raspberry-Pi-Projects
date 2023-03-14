#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    gpio_init(14);
    gpio_init(13);
    gpio_set_dir(13, GPIO_OUT);
    gpio_set_dir(14, GPIO_OUT);
    gpio_put(14, 1);
    gpio_put(13,0);
    sleep_ms(5000);
}
