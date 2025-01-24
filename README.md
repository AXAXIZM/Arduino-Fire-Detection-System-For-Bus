# Arduino Fire Detection System

This project implements an automated fire detection system using gas sensors, temperature sensors, and an AI-powered camera (HuskyLens). The system triggers an alert when fire is detected based on several conditions.

## Components Used:
- Arduino Uno
- Gas Sensor (MQ series)
- Temperature Sensor (NTC Thermistor)
- HuskyLens AI Camera
- Servo Motor
- Buzzer
- 16x4 LCD Display

## How it Works:
The system continuously monitors the gas levels, temperature, and fire presence through the HuskyLens camera. If any of the conditions meet the thresholds, the system triggers an alarm by turning on the buzzer, rotating the servo motor, and displaying a warning on the LCD.

### Functions:
- **Gas Sensor**: Detects gas leaks and sends signals to Arduino.
- **Temperature Sensor**: Monitors the temperature of the environment.
- **HuskyLens AI Camera**: Detects fire through color recognition.
- **Servo Motor**: Rotates to simulate emergency response.
- **Buzzer**: Provides an audible alarm when danger is detected.
- **LCD Display**: Displays the system status.


## Installation:
1. Install the HuskyLens library from the Arduino Library Manager.
2. Connect all the components according to the wiring diagram.
3. Upload the code to the Arduino Uno.
4. Run the system and monitor the results.

## License:
This project is open-source and available under the MIT License.

