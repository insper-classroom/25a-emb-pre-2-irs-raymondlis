#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN_R = 4;
const int BTN_PIN_G = 26;
const int LED_PIN_G = 6;

volatile int flag_red;
volatile int  flag_green;
void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R){
      flag_red = 1;
    }
  }
  if (events == 0x8){
    if (gpio == BTN_PIN_G){
      flag_green = 1;
    }
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);
  int led_g_on = 0;
  int led_r_on = 0;
  while (true) {
    if (flag_red){
      led_r_on = !led_r_on;
      gpio_put(LED_PIN_R,led_r_on);
      flag_red = 0;
    }
    if (flag_green){
      led_g_on = !led_g_on;
      gpio_put(LED_PIN_G,led_g_on);
      flag_green = 0;
    }
  }
}
