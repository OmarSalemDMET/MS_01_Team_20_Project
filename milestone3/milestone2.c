// main.c

#include "pico/stdlib.h"
#include "motor_control.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

// GPIO Pins for Buzzer and LEDs
#define BUZZER_PIN 8
#define LED1_PIN 9
#define LED2_PIN 10  // Changed from 10 to 14 to avoid conflict

// Distance threshold (in cm)
#define OBSTACLE_THRESHOLD 15.0

// Function Prototypes
void setup(void);
void stop_and_alert(void);

int main() {
    setup();

    while (true) {
        // Measure distance using ultrasonic sensor
        float distance = ultrasonic_get_distance();
        printf("Distance: %.2f cm\n", distance);

        // Check for obstacle detection
        if (distance < OBSTACLE_THRESHOLD) {
            printf("Obstacle detected! Stopping car and alerting...\n");
            stop_and_alert();
            // Optionally, skip moving forward if obstacle is detected
            continue;
        }

        // Check for hole detection using IR sensor
        if (ir_sensor_detected_hole()) {
            printf("Hole detected! Stopping car and alerting...\n");
            stop_and_alert();
        } else {
            // Move the car forward if no obstacle or hole detected
            motor_control(1, 58000, true); // 50% speed, forward
            motor_control(2, 58000, true); // 50% speed, forward
        }

        // Wait for a short delay before the next loop iteration
        sleep_ms(100);
    }
}

/**
 * Initializes all hardware components.
 */
void setup(void) {
    // Initialize stdio for debug output
    stdio_init_all();

    // Initialize motor control
    motor_init();

    // Initialize ultrasonic sensor
    ultrasonic_init();

    // Initialize IR sensor
    ir_sensor_init();

    // Initialize buzzer and LEDs as outputs
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Ensure buzzer is off initially

    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_put(LED1_PIN, 0); // Ensure LED1 is off initially

    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_put(LED2_PIN, 0); // Ensure LED2 is off initially
}

/**
 * Stops the motors and activates buzzer and LEDs to alert the user.
 */
void stop_and_alert(void) {
    // Stop both motors
    motor_stop();

    // Activate buzzer and LEDs
    gpio_put(BUZZER_PIN, 1);
    gpio_put(LED1_PIN, 1);
    gpio_put(LED2_PIN, 1);

    // Keep the alert active for 5 seconds
    sleep_ms(5000);

    // Deactivate buzzer and LEDs
    gpio_put(BUZZER_PIN, 0);
    gpio_put(LED1_PIN, 0);
    gpio_put(LED2_PIN, 0);
}
