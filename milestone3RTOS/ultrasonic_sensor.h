#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "pico/stdlib.h"

// GPIO Pins for Ultrasonic Sensor
#define TRIG_PIN 2
#define ECHO_PIN 3

// Function Prototypes
void ultrasonic_init(void);
float ultrasonic_get_distance(void);

#endif // ULTRASONIC_SENSOR_H
