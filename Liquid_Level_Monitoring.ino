
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[]="eda_fl3hvAMOrlemFWpU88NxjujWSTnb";
char ssid[]="Wifi Name";
char pass[]="Wifi pass";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

#define trigPin 13
#define echoPin 11
float distance;
float duration;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2)/28.9;
  Serial.println(distance,2);
  delay(1000);
  if(distance>=12.00){
    Blynk.notify("Low Liquid");
  }
  
}
