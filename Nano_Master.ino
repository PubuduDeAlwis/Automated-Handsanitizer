#include <SPI.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int motorPin = 7;
int irDigitalPin = 8;
int buzzer = 4;
boolean valueD0;
double temp;

void setup() {
  //Intializing MLX90614 Infrared Temperature Sensor
  mlx.begin();
  Serial.begin(9600);
  digitalWrite(SS,HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(motorPin,OUTPUT);
  pinMode(irDigitalPin,INPUT);
  pinMode(buzzer,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char tempString[16];
  digitalWrite(motorPin,LOW);
  char c;
  char c2;
  temp = 0;
  float sumTemp = 0;
  valueD0 = digitalRead(irDigitalPin);
  
  if(valueD0 ==false){
    for(int i = 0; i<5000; i++){
      sumTemp += mlx.readObjectTempC();
      if(valueD0 == true){
        goto error;
      }
    }
    temp = sumTemp/5000.0;
    dtostrf(temp,5,2,tempString);
    
    if(temp>30&& temp<=37){
      tempString[5]=' ';
      tempString[6]='C';
      
      for(int j = 7; j<15; j++){
        tempString[j]=' ';
      }
      tempString[15]='\r';
      Serial.print("temp: ");
      Serial.println(tempString);
      digitalWrite(SS,LOW);
      for(const char *p = tempString; c= *p; p++){
        SPI.transfer(c);
        Serial.print(c);
      }
  
      digitalWrite(SS,HIGH);
      delay(2000);
      if(digitalRead(irDigitalPin)==true){
        goto error;
      }
      digitalWrite(motorPin,HIGH);
      delay(1000);
      digitalWrite(motorPin,LOW);
      delay(1000);
    }
    else{
      
      int count = 0;
      for(int i = 0; i  <= 10; i++){
        if(temp>37){
          count++;
        }
      }
      if(count>5){
        digitalWrite(SS,LOW);
        for(const char *p2 = "FEVER          \r";c2 = *p2; p2++){
          SPI.transfer(c2);
          Serial.print(c2);
        }
        for(int j = 0; j<5; j++){
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          delay(500);
        }
        digitalWrite(SS,HIGH);
        delay(2000);
        
      }
      else{
error:  digitalWrite(SS,LOW);
        for(const char *p3 = "Error          \r";c2 = *p3; p3++){
          SPI.transfer(c2);
          Serial.print(c2);
        }
        for(int j = 0; j<2; j++){
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          delay(500);
        }
        digitalWrite(SS,HIGH);
        delay(2000);
       
      }
      
    }
  }
  else{
     digitalWrite(SS,LOW);
     for(const char *p2 = "Place Hands    \r";c2 = *p2; p2++){
          SPI.transfer(c2);
          Serial.print(c2);
     }
     digitalWrite(SS,HIGH);
     delay(2000);
  }
}
