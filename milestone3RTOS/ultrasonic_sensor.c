// ultrasonic_sensor.c

#include "ultrasonic_sensor.h"

void ultrasonic_init(void) {
    // Initialize Trig pin as output
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0); // Ensure Trig is low initially

    // Initialize Echo pin as input
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

float ultrasonic_get_distance(void) {
    uint32_t pulse_start = 0, pulse_end = 0;

    // Send a 10us pulse to Trig pin
    gpio_put(TRIG_PIN, 1);
    sleep_us(10); // 10 microseconds
    gpio_put(TRIG_PIN, 0);

    // Wait for Echo pin to go high
    while (gpio_get(ECHO_PIN) == 0) {
        pulse_start = time_us_32();
        // Optionally, add a timeout to prevent infinite loop
    }

    // Wait for Echo pin to go low
    while (gpio_get(ECHO_PIN) == 1) {
        pulse_end = time_us_32();
        // Optionally, add a timeout to prevent infinite loop
    }

    // Calculate the duration of the pulse
    uint32_t pulse_duration = pulse_end - pulse_start;

    // Calculate distance in cm
    float distance = (pulse_duration * 0.0343) / 2;

    return distance;
}
