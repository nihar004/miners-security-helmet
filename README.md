# IoT-Enabled Safety Helmet for Worker Protection

## Overview

This project presents an **IoT-enabled safety helmet** designed to enhance worker safety in hazardous environments such as mines and industrial workplaces. The helmet integrates various sensors, communication modules, and real-time data monitoring and alert systems to provide comprehensive protection and proactive safety measures.
![image](https://github.com/user-attachments/assets/c212836c-91da-45d4-bacd-1ce4b56aba93)
![image](https://github.com/user-attachments/assets/b1233868-9cb3-4925-870e-91e901eed001)


## Features

* **Gas Detection**: Detects harmful gases like methane and carbon monoxide using the MQ-2 sensor.
* **Temperature Monitoring**: Monitors ambient temperature using the DHT11 sensor.
* **Fall Detection**: Detects worker falls with the MPU6050 accelerometer and gyroscope.
* **Light Adaptation**: Adjusts visibility in low-light environments using an LDR sensor and headlamp.
* **IoT Connectivity**: Real-time data visualization and monitoring via ThingSpeak.
* **Emergency Alerts**: Sends SMS notifications using Twilio API during emergencies.
* **Two-Way Communication (Planned)**: Enables direct voice communication via the SIM800H GPRS module..

## Technologies Used

* **Microcontroller**: ESP32
* **Sensors**: MQ-2, DHT11, MPU6050, LDR
* **IoT Platform**: ThingSpeak
* **SMS Service**: Twilio API
* **Communication Module**: SIM800H
* **Programming**: Arduino IDE, Embedded Systems

## How It Works

1. **Data Collection**: Sensors continuously monitor environmental and worker conditions.
2. **Hazard Detection**: Threshold-based detection for gas levels, temperature, light, and fall events.
3. **Real-Time Alerts**: Visual (LEDs), auditory (buzzer), and remote (SMS via Twilio) notifications.
4. **Two-Way Communication**: Facilitates direct voice calls for immediate assistance.
5. **Data Visualization**: Real-time data uploaded to ThingSpeak for monitoring and analysis.

## Getting Started

### Hardware Requirements

1. **Sensors**: MQ-2 (gas), DHT11 (temperature), MPU6050 (fall), LDR (light).
2. **Modules**: ESP32, SIM800H (GPRS).
3. Additional components: LEDs, buzzer, fan, lithium-ion battery, and optional solar panel for power.

### Software Requirements

1. **Arduino IDE** with the following libraries installed:
   * Adafruit_MPU6050
   * Adafruit_Sensor
   * DHT Sensor Library
   * PulseSensor Playground
   * WiFi.h
   * HTTPClient.h
   * SoftwareSerial
2. **ThingSpeak API Key**: For IoT data visualization.
3. **Twilio Credentials**: For sending SMS notifications.

### Setup Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/miners-safety-helmet.git
2. Open `helmet_code.ino` in the Arduino IDE.
3. Update the following placeholders in the code:
   *Wi-Fi credentials (`ssid`,`password`)
   *ThingSpeak API key (`thingSpeakAPIKey`)
   *Twilio credentials (`accountSID`, `authToken`, `twilioNumber`, `recipientNumber`).
4. Upload the code to your ESP32.
5. Assemble the hardware components and power on the helmet.

### Execution
* **Real-Time Monitoring**: View sensor data on the ThingSpeak dashboard.
* **Emergency Alerts**: Test hazard detection features to trigger SMS notifications via Twilio.
* **Two-Way Communication**: Test voice calls using the SIM800H module.

### Code
The complete source code for the project is located in the `src/helmet_code.ino` file. [Click here]() to view the code.

### Contributions
**Contributions are welcome!**
If you'd like to improve this project, feel free to fork the repository, make your changes, and submit a pull request. For major changes, please open an issue to discuss what you would like to change.

### License
This project is licensed under the [MIT License](https://github.com/nihar004/miners-security-helmet/blob/main/LICENSE).

### Acknowledgments
Special thanks to the team:

* **Nihar Singla** [Contact via email](mailto:niharsingla001@email.com  "Click to send an email to niharsingla001@email.com ")
* **Team Members**: Piyush Garg, Manan Khandelwal, Bhavesh Choudhary, Divyanshu Bansal
* **Mentor**: Dr. Sandeep [Contact via email](mailto:sandeep.kumar@bmu.edu.in  "Click to send an email to sandeep.kumar@bmu.edu.in ")

