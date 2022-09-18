#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "reboot/bootsel-reboot.h"
#include "lora/lora.h"

const uint ledPin = 13;
const uint pwmPin = 28;

void blinkLight(uint millisecondsOn) {
    check_bootsel_button();

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(millisecondsOn);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    check_bootsel_button();
}

void blinkSequence(uint milliseconds, uint count) {
    for (uint i = 0; i < count; i++) {
        blinkLight(milliseconds);
        sleep_ms(milliseconds);
    }
    check_bootsel_button();
}

void blink() {
    while (true) {
		check_bootsel_button();

        blinkLight(250);
        sleep_ms(500);
		check_bootsel_button();
    }
}

void pwmLoop() {
    gpio_set_function(pwmPin, GPIO_FUNC_PWM);
    uint pwmSlice = pwm_gpio_to_slice_num(pwmPin);

    pwm_set_wrap(pwmSlice, 50);
    pwm_set_enabled(pwmSlice, true);

    for (int i = 0; i < 50; i++) {
		check_bootsel_button();
        blinkLight(5);
        pwm_set_chan_level(pwmSlice, PWM_CHAN_A, i);
        // pwm_set_enabled(pwmSlice, true);
        sleep_ms(250);
    }
}

void spiLoop() {
    blinkSequence(50, 5);

    auto begin = LoRa.begin(868E6);
	if (begin != 1) {
        // blinkSequence(50, 50);
        // sleep_ms(250);

        // blinkSequence(500, begin);
        return;
	}
    
    blinkSequence(250, 3);

    uint8_t counter = 0;
    while (true) {
		counter++;
		check_bootsel_button();
        
		LoRa.beginPacket();
		LoRa.print("hello ");
		LoRa.print(counter);
		LoRa.endPacket();

        sleep_ms(125);
		check_bootsel_button();
        sleep_ms(125);

        blinkSequence(50, 2);
        
    }
}

int main() {
    stdio_init_all();
    arm_watchdog();

    if (cyw43_arch_init()) {
        return -1;
    }

    spiLoop();
    // pwmLoop();
    // blink();

    return 0;
}
