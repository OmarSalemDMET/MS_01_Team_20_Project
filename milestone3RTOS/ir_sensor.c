// ir_sensor.c

#include "ir_sensor.h"

/**
 * Initializes the IR sensor pin.
 * Configures the pin as input and sets up any necessary pull-up/down resistors.
 */
void ir_sensor_init(void) {
    gpio_init(IR_SENSOR_PIN);
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN);
    
    // Depending on your IR sensor, you might need to enable internal pull-up or pull-down resistors.
    // Uncomment one of the following lines if required:
    
    // gpio_pull_up(IR_SENSOR_PIN);   // Enable internal pull-up resistor
    // gpio_pull_down(IR_SENSOR_PIN); // Enable internal pull-down resistor
}

/**
 * Reads the IR sensor to detect a hole.
 * 
 * @return `true` if a hole is detected, `false` otherwise.
 */
bool ir_sensor_detected_hole(void) {
    // Read the IR sensor pin
    // Adjust the logic based on your IR sensor's output:
    // For example, if the sensor outputs HIGH when a hole is detected:
    return gpio_get(IR_SENSOR_PIN);

    // If the sensor outputs LOW when a hole is detected, use the following line instead:
    // return !gpio_get(IR_SENSOR_PIN);
}
