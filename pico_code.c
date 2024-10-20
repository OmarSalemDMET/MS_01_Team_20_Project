
#include "pico/stdlib.h"

#define RED 5
#define BLUE 7
#define GREEN 6

int main() {
  // Initialize stdio (not required unless using serial communication)
  stdio_init_all();

  // Set the GPIO pins as input or output
  gpio_init(RED);
  gpio_set_dir(RED, GPIO_OUT);

  gpio_init(BLUE);
  gpio_set_dir(BLUE, GPIO_OUT);
  gpio_pull_up(BLUE); // Enable internal pull-up resistor for the BLUE pin

  gpio_init(GREEN);
  gpio_set_dir(GREEN, GPIO_OUT);

  while (1) {
    // Turn on the RED LED
    gpio_put(RED, 1);
    sleep_ms(1000);
    // Turn off the RED LED
    gpio_put(RED, 0);

    // Turn on the GREEN LED
    gpio_put(GREEN, 1);
    sleep_ms(1000);
    // Turn off the GREEN LED
    gpio_put(GREEN, 0);

    // Pull down the BLUE pin (simulates a low state if connected to an LED)
    gpio_put(BLUE, 0);
    sleep_ms(1000);

    // Pull down the BLUE pin (simulates a low state if connected to an LED)
    gpio_put(BLUE, 1);
    sleep_ms(1000);

    // Turn on both RED and GREEN LEDs, keep BLUE off
    gpio_put(RED, 1);
    gpio_put(GREEN, 1);
    gpio_put(BLUE, 0);
    sleep_ms(1000);

    // Turn off RED and GREEN LEDs, turn on BLUE LED
    gpio_put(RED, 0);
    gpio_put(GREEN, 0);
    gpio_put(BLUE, 1);
    sleep_ms(5000);
  }

  return 0;
}
