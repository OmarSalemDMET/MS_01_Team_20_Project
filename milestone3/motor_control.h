#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pico/stdlib.h"

// Motor Control Pins
#define MOTOR1_PWM_PIN 0
#define MOTOR1_DIR_PIN1 11
#define MOTOR1_DIR_PIN2 12
#define MOTOR2_PWM_PIN 1
#define MOTOR2_DIR_PIN1 14
#define MOTOR2_DIR_PIN2 15

// Function Prototypes
void motor_init(void);
void motor_control(uint8_t motor, uint16_t speed, bool forward);
void motor_stop(void);

#endif // MOTOR_CONTROL_H
