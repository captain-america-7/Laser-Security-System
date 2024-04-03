#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "ssid";
const char* password = "password";
const long channelID = *******;
const char* apikey = "****************";
int buzzer=D6;

WiFiClient client;

void setup() {
 
  ThingSpeak.begin(client);

  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(D1,INPUT);
  delay(2000);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status()!=WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
  pinMode(pirPin, INPUT);
  pinMode(D1, OUTPUT);
  delay(2000);
}
}

void loop() {
  // led Blink Code
  //digitalWrite(D0,HIGH);
  //delay(1000);
  //digitalWrite(D0,LOW);
  //delay(1000);
  int ldrStatus=digitalRead(D1);

  if (ldrStatus==1){
    //Laser Alarm Activated
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,LOW);
    delay(100);
    ThingSpeak.writeField(channelID, 1, ldrStatus, apikey);
    tone(buzzer,600,250);
    delay(100);
  }
  else{
    ThingSpeak.writeField(channelID, 1, ldrStatus, apikey);
  }
  delay(50);
}