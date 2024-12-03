#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <PulseSensorPlayground.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <math.h>
#include <SoftwareSerial.h> // For GPRS communication

// Wi-Fi credentials
const char* ssid = "OneXXXXX"; // Enter your hotspot name here
const char* password = "bXXXXXX"; // Enter you hotspot password here

// Twilio credentials
// Enter your Twilio Credentials here 
const char* accountSID = "ACcc82XXXXXXXXXXXXXXXXXXXXX";
const char* authToken = "45bXXXXXXXXXXXXXXXXX";
const char* twilioNumber = "+125XXXXXXXX";
const char* recipientNumber = "+918XXXXXX"; // Enter the Phone number you want to receive the SMS on 

// ThingSpeak API Key and URL
const char* thingSpeakAPIKey = "QXIBQXXXXXXXXXX"; // Enter your ThingSpeak API Key here
const char* thingSpeakURL = "http://api.thingspeak.com/update";

// GPRS Module Pins and Configuration
#define RX_PIN 16
#define TX_PIN 17
SoftwareSerial gprsSerial(RX_PIN, TX_PIN); // SIM800 module pins
#define BAUD_RATE 9600

// Pin Definitions
#define SDA_PIN 26
#define SCL_PIN 27
#define PULSE_PIN 32
#define LDR_PIN 35
#define BUZZER_PIN 18
#define RED_LED 19
#define GREEN_LED 21
#define YELLOW_LED 22
#define FAN_PIN 13
#define LDR_LED 25
#define DHT_PIN 4
#define MQ2_PIN 34
#define BUTTON_PIN 2

// Thresholds
#define LIGHT_THRESHOLD 2000
#define GAS_THRESHOLD 2920
#define TEMP_THRESHOLD 30
#define FALL_THRESHOLD 3.0
const unsigned long SOS_TIMEOUT = 10000;

// Sensor Objects
Adafruit_MPU6050 mpu;
DHT dht(DHT_PIN, DHT11);
PulseSensorPlayground pulseSensor;

// Data fields for ThingSpeak
float temperature = 0.0;
int heartbeat = 0;
int gasLevel = 0;

// Time tracking
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 15000; // 15 seconds

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Pin Modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LDR_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  
  // Initialize all sensors
  initializeMPU();
  initializePulseSensor();
  initializeWiFi();
  initializeGPRS();
  dht.begin();
  
  Serial.println("All systems initialized!");
}

void loop() {
  // Read sensors
  readMPUData();
  readPulseSensor();
  readEnvironmentalSensors();

  // Send data to ThingSpeak every 15 seconds
  if (millis() - lastUpdateTime > updateInterval) {
    sendDataToThingSpeak();
    lastUpdateTime = millis();
  }
  
  delay(200); // Short delay for system stability
}

void initializeMPU() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 Initialized!");
}

void initializePulseSensor() {
  pulseSensor.analogInput(PULSE_PIN);
  pulseSensor.setThreshold(550);
  if (pulseSensor.begin()) {
    Serial.println("Pulse sensor initialized.");
  }
}

void initializeWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void initializeGPRS() {
  gprsSerial.begin(BAUD_RATE);
  delay(1000);
  sendGPRSCommand("AT", "OK");
  sendGPRSCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", "OK");
  sendGPRSCommand("AT+SAPBR=3,1,\"APN\",\"981XXXXXXXX\"", "OK"); // Enter your Mobile number here
  sendGPRSCommand("AT+SAPBR=1,1", "OK");
  sendGPRSCommand("AT+HTTPINIT", "OK");
  Serial.println("GPRS Initialized!");
}

void sendGPRSCommand(const char* command, const char* response) {
  gprsSerial.println(command);
  delay(500);
  String reply = gprsSerial.readString();
  if (reply.indexOf(response) != -1) {
    Serial.println(command);
  } else {
    Serial.println("GPRS Command Failed!");
  }
}

void readMPUData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  float totalAccel = sqrt(pow(a.acceleration.x, 2) +
                         pow(a.acceleration.y, 2) +
                         pow(a.acceleration.z, 2));
  
  Serial.print("Total Acceleration: ");
  Serial.println(totalAccel);
  
  if (totalAccel < FALL_THRESHOLD) {
    handleFallDetection();
  }
}

void readPulseSensor() {
  heartbeat = pulseSensor.getBeatsPerMinute();
  if (heartbeat > 0) {
    Serial.print("Heartbeat: ");
    Serial.print(heartbeat);
    Serial.println(" BPM");
  }
}

void readEnvironmentalSensors() {
  // LDR Sensor
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  digitalWrite(LDR_LED, ldrValue > LIGHT_THRESHOLD ? HIGH : LOW);
  
  // MQ2 Gas Sensor
  gasLevel = analogRead(MQ2_PIN);
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);
  if (gasLevel > GAS_THRESHOLD) {
    handleGasAlert();
  } else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(FAN_PIN, HIGH);
  }
  
  // DHT Temperature Sensor
  temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  if (temperature > TEMP_THRESHOLD) {
    handleTemperatureAlert();
  } else {
    digitalWrite(RED_LED, LOW);
  }
}

void handleFallDetection() {
  Serial.println("Fall Detected!");
  digitalWrite(YELLOW_LED, HIGH);
  
  unsigned long startTime = millis();
  while (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    if (millis() - startTime > SOS_TIMEOUT) {
      Serial.println("SOS Timeout - Sending Alert");
      sendSOSMessage();
      break;
    }
    delay(100);
  }
  
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void handleGasAlert() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(FAN_PIN, LOW);
  tone(BUZZER_PIN, 1000, 200);
}

void handleTemperatureAlert() {
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER_PIN, 1000, 200);
}

void sendSOSMessage() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.twilio.com/2010-04-01/Accounts/" + String(accountSID) + "/Messages.json";
    String messageBody = "EMERGENCY: Fall detected in mining helmet! Immediate assistance required!";
    
    http.begin(url);
    http.setAuthorization(accountSID, authToken);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "To=" + String(recipientNumber) +
                     "&From=" + String(twilioNumber) +
                     "&Body=" + messageBody;
    
    int httpResponseCode = http.POST(postData);
    
    if (httpResponseCode > 0) {
      Serial.print("Message sent. Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending message: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }
    
    http.end();
  } else {
    Serial.println("Wi-Fi disconnected. Cannot send SOS message.");
  }
}

void sendDataToThingSpeak() {
  if (WiFi.status() == WL_CONNECTED || gprsSerial.available()) {
    HTTPClient http;
    String url = String(thingSpeakURL) + "?api_key=" + thingSpeakAPIKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(heartbeat) +
                 "&field3=" + String(gasLevel);
                 
    http.begin(url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.print("ThingSpeak response: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error in ThingSpeak GET: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }
    
    http.end();
  } else {
    Serial.println("No network available to send data.");
  }
}