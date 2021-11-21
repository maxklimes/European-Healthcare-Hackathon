
#include "HX711.h"
#include <Wire.h>
#include <soc/rtc.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


const int LOADCELL_DOUT_PIN = 19;
const int LOADCELL_SCK_PIN = 23;
const int BUTTON_PIN = 5;

float urine_density = 1.015;

int BUTTON_STATE = 0;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

const long interval = 200;  
const long interval2 = 10000;  



HX711 scale;

void tare() {

  scale.set_scale(393.f);                     
  scale.tare();				        
 
}

void measure1() {

  lcd.backlight();

  scale.power_up();

  float reading = scale.get_units(10);

  float volume1 = reading / urine_density;
 
  Serial.println("current volume is:");
  Serial.println(volume1);

  lcd.clear();

  delay(500);

  lcd.print("Current volume:");
  delay(1000);
  lcd.clear();
  delay(200);
  lcd.print(volume1);
  delay(2000);
  lcd.clear();

  lcd.noBacklight();

  scale.power_down();

}


void pushbutton() {
  BUTTON_STATE = digitalRead(BUTTON_PIN);  

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    if (BUTTON_STATE == 0) {
      Serial.println("press!");
      measure1();
    } else {
      Serial.println("waiting...");
    }

}

}

void altmeasure() {

  unsigned long currentMillis2 = millis();

  if (currentMillis2 - previousMillis2 >= interval2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;

  

  lcd.backlight();  

  scale.power_up();

  float reading4 = scale.get_units(10);
 
  float volume1 = reading4 / urine_density;
 
  Serial.println("current volume is: ");
  Serial.println(volume1);

//  float prevmeasuremenent = volume1;

//  Serial.print(prevmeasuremenent);

//  int measured_values[4];

//  measured_values[0] = prevmeasuremenent;

//  for(int i = 0; i < 4; i++)
//  {
//    Serial.println(measured_values[i]);
//  }

  lcd.clear();

  delay(500);

  lcd.print("Current volume:");
  delay(1000);
  lcd.clear();

  delay(500);

  lcd.print(reading4); 

  delay(2000);

  lcd.clear();
  lcd.noBacklight();
  
  scale.power_down();

}

}




void setup() {


  Serial.println("SADASD");

  lcd.init();                      // initialize the lcd 
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("HX711 Demo");

  

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("SETUP WORKS");

  BUTTON_STATE = digitalRead(BUTTON_PIN);

  if (BUTTON_STATE == 0) {

    lcd.backlight();
    tare();
    lcd.clear();
    lcd.print("TARE INITIATED");
    delay(2000);
    lcd.clear();
    lcd.noBacklight();

  }
  

  Serial.println("got here");

}

void loop() {

pushbutton();

altmeasure();



  }





