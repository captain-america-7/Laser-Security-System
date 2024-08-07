#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "ssid";
const char* password = "password";

// ThingSpeak channel details
const long channelID = *******;
const char* apikey = "****************";

// Pin assignments
int buzzer = D6;     // Buzzer connected to D6
int led1 = D0;       // LED 1 connected to D0
int led2 = D2;       // LED 2 connected to D2
int ldrSensor = D1;  // LDR sensor connected to D1

WiFiClient client;

void setup() {
  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Pin modes
  pinMode(led1, OUTPUT);   // LED 1
  pinMode(led2, OUTPUT);   // LED 2
  pinMode(buzzer, OUTPUT); // Buzzer
  pinMode(ldrSensor, INPUT); // LDR sensor
  delay(2000);             // Initial delay for setup stabilization

  Serial.begin(115200);    // Begin serial communication for debugging

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client); // Initialize ThingSpeak
  delay(2000);              // Delay for stabilization
}

void loop() {
  // Read LDR sensor status
  int ldrStatus = digitalRead(ldrSensor);

  if (ldrStatus == 1) {
    // Laser Alarm Activated
    digitalWrite(led1, HIGH);    // Turn on LED 1
    digitalWrite(led2, HIGH);    // Turn on LED 2
    delay(100);                  // Wait for 100ms
    digitalWrite(led1, LOW);     // Turn off LED 1
    digitalWrite(led2, LOW);     // Turn off LED 2
    delay(100);                  // Wait for 100ms
    // Send the status to ThingSpeak
    ThingSpeak.writeField(channelID, 1, ldrStatus, apikey);
    // Activate buzzer
    tone(buzzer, 600, 250);      // Buzzer tone at 600Hz for 250ms
    delay(100);                  // Wait for 100ms
  } else {
    // Laser Alarm Deactivated
    // Send the status to ThingSpeak
    ThingSpeak.writeField(channelID, 1, ldrStatus, apikey);
  }
  delay(50);                     // Wait for 50ms before next loop iteration
}
