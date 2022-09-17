#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "reboot/bootsel-reboot.h"

const uint LED_PIN = 13;

void blinkPico() {
    gpio_init(LED_PIN) ;
    gpio_set_dir(LED_PIN, GPIO_OUT) ;

    while(true) {
		check_bootsel_button();

        gpio_put(LED_PIN, 0) ;
        sleep_ms(250) ;
        gpio_put(LED_PIN, 1);
        sleep_ms(1000) ;
    }
}

void blinkPicoW() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(2500);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(1000);

    while (true) {
		check_bootsel_button();

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1000) ;
    }
}

int main() {
    stdio_init_all();
    arm_watchdog();

    if (cyw43_arch_init()) {
        blinkPico();
        return -1;
    }
    blinkPicoW();

    return 0;
}
