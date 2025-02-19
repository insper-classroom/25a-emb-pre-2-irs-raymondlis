#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN = 4;
volatile int flag_apertou;
void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag_apertou = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  int led_on = 0;
  while (true) {
    if (flag_apertou){
      led_on = !led_on;
      gpio_put(LED_PIN,led_on);
      flag_apertou = 0;
    }
  }
}
