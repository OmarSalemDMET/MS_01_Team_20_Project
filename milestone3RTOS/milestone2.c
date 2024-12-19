#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "pico/stdlib.h"
#include "motor_control.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

// GPIO Pins for Buzzer and LEDs
#define BUZZER_PIN 8
#define LED1_PIN 9
#define LED2_PIN 10

// Distance threshold (in cm)
#define OBSTACLE_THRESHOLD 10.0

// Task priorities
#define ULTRASONIC_TASK_PRIORITY 2
#define IR_TASK_PRIORITY 2
#define MOTOR_TASK_PRIORITY 3

// Queue for inter-task communication
static QueueHandle_t sensorQueue;

// Function Prototypes
void setup(void);
void stop_and_alert(void);
void Ultrasonic_Sensor_Task(void *pvParameters);
void IR_Sensor_Task(void *pvParameters);
void Motor_Control_Task(void *pvParameters);

int main() {
    setup();

    // Create the queue
    sensorQueue = xQueueCreate(10, sizeof(float));
    if (sensorQueue == NULL) {
        printf("Failed to create the queue\n");
        while (1);
    }

    // Create tasks
    xTaskCreate(Ultrasonic_Sensor_Task, "Ultrasonic Sensor Task", 256, NULL, ULTRASONIC_TASK_PRIORITY, NULL);
    xTaskCreate(IR_Sensor_Task, "IR Sensor Task", 256, NULL, IR_TASK_PRIORITY, NULL);
    xTaskCreate(Motor_Control_Task, "Motor Control Task", 256, NULL, MOTOR_TASK_PRIORITY, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (true);
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

/**
 * Task to handle ultrasonic sensor readings.
 */
void Ultrasonic_Sensor_Task(void *pvParameters) {
    (void)pvParameters;
    float distance;

    for (;;) {
        distance = ultrasonic_get_distance();
        printf("Distance: %.2f cm\n", distance);
        xQueueSend(sensorQueue, &distance, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * Task to handle IR sensor readings.
 */
void IR_Sensor_Task(void *pvParameters) {
    (void)pvParameters;
    float dummyValue = -1.0; // Placeholder value for IR detection

    for (;;) {
        if (ir_sensor_detected_hole()) {
            printf("Hole detected!\n");
            xQueueSend(sensorQueue, &dummyValue, portMAX_DELAY);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * Task to handle motor control based on sensor data.
 */
void Motor_Control_Task(void *pvParameters) {
    (void)pvParameters;
    float sensorData;

    for (;;) {
        if (xQueueReceive(sensorQueue, &sensorData, portMAX_DELAY)) {
            if (sensorData < OBSTACLE_THRESHOLD && sensorData >= 0) {
                printf("Obstacle detected! Stopping car and alerting...\n");
                stop_and_alert();
            } else if (sensorData == -1.0) {
                printf("Hole detected! Stopping car and alerting...\n");
                stop_and_alert();
            } else {
                motor_control(1, 65535, true); // 50% speed, forward
                motor_control(2, 65535, true); // 50% speed, forward
            }
        }
    }
}
