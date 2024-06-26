#define BLYNK_TEMPLATE_ID "TMPL6lk3mSoSv"
#define BLYNK_TEMPLATE_NAME "SMTFISHTANK"
#define BLYNK_AUTH_TOKEN "SHLatZ1Ke0Aw8jBVzDBVAnUiV_BVS6Uo"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define ssid "PHURITTHARIPHA_2.4G"
#define pass "P22052549"

#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

//-------------------------------------Define variable
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define Bad_Pump 12   //int Bad_Pump = 12;
#define Good_Pump 14

#define WaterFloat_pin 35
int WaterFloat_val;

int State = 0;

int Blynksw0;
int Blynksw1;
int Blynksw2;
int Blynksw3;
int Blynksw4;
int Blynksw6;
int Blynksw7;

//-------------------------------------Setup
void setup() {
  Serial.begin(9600);
  //Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  //--------------< LCD >
  lcd.begin();
  lcd.backlight();

  //--------------< Relay & Pump >
  pinMode(Bad_Pump, OUTPUT);
  pinMode(Good_Pump, OUTPUT);
  digitalWrite(Bad_Pump, 1);  // High is turn off
  digitalWrite(Good_Pump, 1);

  //--------------< WaterFloat sensor >
  pinMode(WaterFloat_pin, INPUT);
}

//-------------------------------------Loop
void loop() {
  Blynk.run();
  
  switch(State){
    case 0: //-----------< state "START" > 
      lcd.setCursor(3, 1);  lcd.print("Press any key");
      if(Blynksw7 == 1){
        State = 1;
      }
      else
        State = 0;
      
    break;

    case 1: //-----------< state "MENU" > 
      lcd.clear();
      lcd.setCursor(0, 0);  lcd.print("Press 2: BAD_PUMP");
      lcd.setCursor(0, 1);  lcd.print("Press 3: GOOD_PUMP");
      lcd.setCursor(0, 2);  lcd.print("Press 6: WaterSensor");

      if(Blynksw2 == 1){
        State = 2;
      }
      else if(Blynksw3 == 1){
        State = 3;
      }
      else if(Blynksw6 == 1){
        State = 4;
      }
      else 
        State = 1;
      
    break;

    case 2: //-----------< state "BAD_PUMP" > 
      lcd.clear();
      lcd.setCursor(5, 0);  lcd.print("BAD_PUMP");
      lcd.setCursor(0, 1);  lcd.print("Push fisrt button");
      lcd.setCursor(0, 2);  lcd.print("to start");

      lcd.setCursor(0, 3);  lcd.print("Press 4: to menu");      
      
      if(Blynksw4 == 1){
        State = 1; 
      }
      else if(Blynksw1 == 0){
        digitalWrite(Bad_Pump, 1); //BAD_PUMP stop work.
      }
      else if(Blynksw1 == 1){
        digitalWrite(Bad_Pump, 0); //BAD_PUMP working 
      }
      else 
        State = 2;
      
    break;

    case 3: //-----------< state "GOOD_PUMP" > 
      lcd.clear();
      lcd.setCursor(5, 0);  lcd.print("GOOD_PUMP");
      lcd.setCursor(0, 1);  lcd.print("Push fisrt button");
      lcd.setCursor(0, 2);  lcd.print("to start");

      lcd.setCursor(0, 3);  lcd.print("Press 4: to menu");

      if(Blynksw4 == 1){
        State = 1; 
      }
      else if(Blynksw0 == 0){
        digitalWrite(Good_Pump, 1); //Good_Pump stop work.
      }
      else if(Blynksw0 == 1){
        digitalWrite(Good_Pump, 0); //Good_Pump working 
      }
      else 
        State = 3;
      
    break;

    case 4: //-----------< state "WATER LEVEL SENSOR" >
      lcd.clear(); 
      lcd.setCursor(0, 0);  lcd.print("WATER LEVEL SENSOR");
      lcd.setCursor(8, 1);  lcd.print("-> " + String(WaterFloat_val));
      lcd.setCursor(0, 3);  lcd.print("Press 4: to menu");

      Blynk.virtualWrite(V5, String(WaterFloat_val));
      
      if(Blynksw4 == 1){
        State = 1;
      }
      else 
        State = 4;
      
    break;
  }
  WaterLevelSensor();
  delay(500);
}

//-------------------------------------Custom function
void WaterLevelSensor(){
  WaterFloat_val = analogRead(WaterFloat_pin);
  WaterFloat_val = WaterFloat_val == 4095 ? 0 : 1;
  //Serial.println(WaterFloat_val);
}

BLYNK_WRITE(V0){ //Blynk Switch 0
  if(param.asInt() == 1){
    Blynksw0 = 1;
  }
  else{
    Blynksw0 = 0;
  }
}
BLYNK_WRITE(V1){ //Blynk Switch 1
  if(param.asInt() == 1){
    Blynksw1 = 1;
  }
  else{
    Blynksw1 = 0;
  }
}
BLYNK_WRITE(V2){ //Blynk Switch 2
  if(param.asInt() == 1){
    Blynksw2 = 1;
  }
  else{
    Blynksw2 = 0;
  }
}
BLYNK_WRITE(V3){ //Blynk Switch 3
  if(param.asInt() == 1){
    Blynksw3 = 1;
  }
  else{
    Blynksw3 = 0;
  }
}
BLYNK_WRITE(V4){ //Blynk Switch 4
  if(param.asInt() == 1){
    Blynksw4 = 1;
  }
  else{
    Blynksw4 = 0;
  }
}
BLYNK_WRITE(V6){ //Blynk Switch 6
  if(param.asInt() == 1){
    Blynksw6 = 1;
  }
  else{
    Blynksw6 = 0;
  }
}
BLYNK_WRITE(V7){ //Blynk Switch 6
  if(param.asInt() == 1){
    Blynksw7 = 1;
  }
  else{
    Blynksw7 = 0;
  }
}