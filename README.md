# IoT-Enabled Miners Safety Helmet

Overview
This project presents an IoT-enabled safety helmet designed to enhance worker safety in hazardous environments such as mines and industrial workplaces. The helmet integrates various sensors and communication modules to provide real-time monitoring, hazard detection, and proactive safety measures.

Features
Gas Detection: Detects harmful gases like methane and carbon monoxide using the MQ-2 sensor.
Temperature Monitoring: Monitors ambient temperature using the DHT11 sensor.
Fall Detection: Detects worker falls with the MPU6050 accelerometer and gyroscope.
Light Adaptation: Adjusts visibility in low-light environments using an LDR sensor and headlamp.
IoT Connectivity: Real-time data visualization and monitoring via ThingSpeak.
Emergency Alerts: Sends SMS notifications using Twilio API during emergencies.
Two-Way Communication (Planned): SIM800H module integration for audio communication.

Technologies Used
Microcontroller: ESP32
Sensors: MQ-2, DHT11, MPU6050, LDR
IoT Platform: ThingSpeak
SMS Service: Twilio API
Programming: Arduino IDE, Embedded Systems
How It Works
Data Collection: Sensors continuously monitor environmental and worker conditions.
Hazard Detection: Threshold-based detection for gas levels, temperature, light, and fall events.
Real-Time Alerts: Visual (LEDs), auditory (buzzer), and remote (SMS via Twilio) notifications.
Data Visualization: Real-time data uploaded to ThingSpeak for monitoring and analysis.
Getting Started
Hardware Requirements
Sensors: MQ-2 (gas), DHT11 (temperature), MPU6050 (fall), LDR (light).
Modules: ESP32, SIM800H (GPRS).
Additional components: LEDs, buzzer, fan, lithium-ion battery, and optional solar panel for power.
Software Requirements
Arduino IDE with the following libraries installed:
Adafruit_MPU6050
Adafruit_Sensor
DHT Sensor Library
PulseSensor Playground
WiFi.h
HTTPClient.h
ThingSpeak API Key: For IoT data visualization.
Twilio Credentials: For sending SMS notifications.
Setup Instructions
Clone the repository:
bash
Copy code
git clone https://github.com/yourusername/miners-safety-helmet.git
Open helmet_code.ino in the Arduino IDE.
Update the following placeholders in the code:
Wi-Fi credentials (ssid, password)
ThingSpeak API key (thingSpeakAPIKey)
Twilio credentials (accountSID, authToken, twilioNumber, recipientNumber).
Upload the code to your ESP32.
Assemble the hardware components and power on the helmet.
Execution
Real-Time Monitoring: View sensor data on the ThingSpeak dashboard.
Emergency Alerts: Test hazard detection features to trigger SMS notifications via Twilio.
Future Integration: Two-way communication module setup is in progress.
Repository Structure
bash
Copy code
miners-safety-helmet/
│
├── README.md              # Project description and details
├── LICENSE                # License file (if applicable)
├── src/                   # Source code directory
│   └── helmet_code.ino    # Your Arduino code
├── images/                # Images for the README (e.g., diagrams, helmet photos)
├── docs/                  # Additional documentation (e.g., schematics, test results)
└── CONTRIBUTING.md        # Guidelines for contributing (optional)
Contributions
Contributions are welcome!
Please see CONTRIBUTING.md for guidelines on how to contribute.

License
This project is licensed under the MIT License.

Acknowledgments
Special thanks to the team:

Nihar Singla
Team Members: Piyush Garg, Manan Khandelwal, Bhavesh Choudhary, Divyanshu Bansal
Mentor: Dr. Sandeep
