// ir_sensor.h

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "pico/stdlib.h"

// GPIO Pin for IR Sensor
#define IR_SENSOR_PIN 6

// Function Prototypes
void ir_sensor_init(void);
bool ir_sensor_detected_hole(void);

#endif // IR_SENSOR_H
