# Emergency Brake System with Potentiometer Speed Control

A project implementing an emergency brake system for an autonomous vehicle, integrating obstacle/hole detection and dynamic speed control.

## Description
This system uses an **ultrasonic sensor** to detect obstacles and an **IR sensor** to detect holes/drop-offs. Upon hazard detection, the vehicle stops and triggers visual (LEDs) and audible (buzzer) alerts. Built with a Raspberry Pi Pico microcontroller.

## Features
- Obstacle detection (HC-SR04 ultrasonic sensor).
- Hole detection (IR proximity sensor).
- Audible (buzzer) and visual (LEDs) alerts.
- Motor control using L298N driver.

## Hardware Components
1. **Microcontroller**: Raspberry Pi Pico  
2. **Sensors**:  
   - Ultrasonic: HC-SR04  
   - IR: Infrared proximity sensor  
4. **Actuators**: 2x Geared DC motors, L298N motor driver  
5. **Alerts**: Piezoelectric buzzer, 2x LEDs  
6. **Power Supply**: Battery pack  
7. **Misc**: Breadboard, jumper wires  

## Installation & Setup
### Wiring Guide
- **Ultrasonic Sensor**:  
  - `TRIG_PIN` → GPIO 2  
  - `ECHO_PIN` → GPIO 3  
- **IR Sensor**:  
  - `IR_SENSOR_PIN` → GPIO 6 (enable pull-up/down resistor if needed).  
- **Motor Driver (L298N)**:  
  - Motor 1: PWM pin 0, DIR pins 12 & 13.  
  - Motor 2: PWM pin 1, DIR pins 14 & 15.  
- **Buzzer**: GPIO 8.  
- **LEDs**: GPIO 9 (LED1), GPIO 10 (LED2).  

### Software Dependencies
- Raspberry Pi Pico SDK.
- `pico/stdlib`, `hardware/pwm`, and `hardware/adc` libraries.

## Usage
1. Power the system and upload the code to the Raspberry Pi Pico.  
2. Rotate the potentiometer to adjust the vehicle's speed.  
3. The vehicle moves forward, continuously monitoring:  
   - **Obstacles** (within 10 cm threshold).  
   - **Holes** (detected via IR reflection drop).  
4. On hazard detection:  
   - Motors stop.  
   - Buzzer and LEDs activate for 5 seconds.  

## Testing
- **Obstacle Test**: Place an object within 10 cm of the ultrasonic sensor. The vehicle stops and alerts.  
- **Hole Test**: Simulate a hole (e.g., dark surface). The IR sensor triggers the brake.  

## References
- [Raspberry Pi Pico Datasheet](https://www.raspberrypi.org/documentation/pico/getting-started/)  
- [HC-SR04 Datasheet](link_to_datasheet)  
- [L298N Motor Driver Documentation](link_to_datasheet)  
- [Pico SDK Docs](https://raspberrypi.github.io/pico-sdk-doxygen/)  

---

