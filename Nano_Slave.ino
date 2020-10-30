#include <SPI.h>
#include<LiquidCrystal_I2C.h>

char buff[16];
volatile byte indx;
volatile boolean process;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  indx = 0;
  process = false;
  SPI.attachInterrupt();
  lcd.begin();
  lcd.backlight();
}

ISR(SPI_STC_vect){
  byte c = SPDR;
  
  if(indx <sizeof buff){
    buff[indx++] = c;
    if(c == '\r')
     process = true;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  
  if(process){
    process = false;
    String b = buff;
    //Serial.println(buff);
    Serial.println(b);
    lcd.setCursor(1,0);
    lcd.print("Temp:");
    lcd.setCursor(1,1);
    lcd.print(b);
    indx = 0; 
  }
}
