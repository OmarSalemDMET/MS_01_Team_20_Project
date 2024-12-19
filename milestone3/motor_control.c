#include "motor_control.h"
#include "hardware/pwm.h"

// Helper function to initialize a PWM pin
static void init_pwm_pin(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_enabled(slice, true);
}

void motor_init(void) {
    // Initialize PWM pins for both motors
    init_pwm_pin(MOTOR1_PWM_PIN);
    init_pwm_pin(MOTOR2_PWM_PIN);

    // Initialize direction pins
    gpio_init(MOTOR1_DIR_PIN1);
    gpio_set_dir(MOTOR1_DIR_PIN1, GPIO_OUT);
    gpio_init(MOTOR1_DIR_PIN2);
    gpio_set_dir(MOTOR1_DIR_PIN2, GPIO_OUT);

    gpio_init(MOTOR2_DIR_PIN1);
    gpio_set_dir(MOTOR2_DIR_PIN1, GPIO_OUT);
    gpio_init(MOTOR2_DIR_PIN2);
    gpio_set_dir(MOTOR2_DIR_PIN2, GPIO_OUT);
}

void motor_control(uint8_t motor, uint16_t speed, bool forward) {
    uint slice, pwm_pin, dir_pin1, dir_pin2;

    if (motor == 1) {
        pwm_pin = MOTOR1_PWM_PIN;
        dir_pin1 = MOTOR1_DIR_PIN1;
        dir_pin2 = MOTOR1_DIR_PIN2;
    } else if (motor == 2) {
        pwm_pin = MOTOR2_PWM_PIN;
        dir_pin1 = MOTOR2_DIR_PIN1;
        dir_pin2 = MOTOR2_DIR_PIN2;
    } else {
        return; // Invalid motor number
    }

    slice = pwm_gpio_to_slice_num(pwm_pin);

    // Set motor direction
    gpio_put(dir_pin1, forward);
    gpio_put(dir_pin2, !forward);

    // Set PWM duty cycle
    pwm_set_wrap(slice, 65535);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(pwm_pin), speed);
}

void motor_stop(void) {
    // Set both motors to zero speed
    motor_control(1, 0, true);
    motor_control(2, 0, true);
}
