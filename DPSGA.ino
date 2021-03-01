#include <DHT.h>    // підкльпення датчика вологості та температури повітря DHT11


#include <Wire.h> //бібліотека для роботи з I2C
#include <LiquidCrystal_I2C.h> //дисплей

#include <RTClib.h> //часи

#include <BH1750.h> //освітлення


LiquidCrystal_I2C lcd(0x27,20,4); //обявили дисплей

#define DHTPIN 10 // обявляємо пін DHT11
//DHT dht(DHTPIN, DHT22); //Ініціалізація датчика
DHT dht(DHTPIN, DHT11); //Ініціалізація датчика



RTC_DS3231 rtc;
DateTime t;
String daysOfTheWeek[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String monthsNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
String daysOfTheWeekS[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

BH1750 lightMeter;

#define PIN_PHOTO_SENSOR A0

// Енкодер
#define CLK 2
#define DT 3
#define SW 4

#include "GyverEncoder.h"

Encoder enc(CLK, DT, SW);

int ah, at; // ah- вологість повітря, at- температура повітря
int sm = 70; //sm- вологісь грунту


int lux;

boolean tflag = false;


int y; // змінні для правильного відобрачення часу

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  
  rtc.begin();
  //rtc.adjust(DateTime(21,1,27,12,5,0)); //установка часу
  
  lcd.init();
  lcd.backlight();

  lightMeter.begin();
  dht.begin();

  enc.setType(TYPE1); 
  
}
void mainTeme(){ //красивий вивід годинника
  
    t=rtc.now();

    if(t.hour() < 10){

      lcd.setCursor(12, 0);
      lcd.print("0");
      lcd.setCursor(13, 0);
      lcd.print(t.hour());
      lcd.setCursor(14, 0);
      lcd.print(":");
      
     }
     else{

      lcd.setCursor(12, 0);
      lcd.print(t.hour());
      lcd.print(":");
      
      }
     if(t.minute() < 10){

      lcd.setCursor(15, 0);
      lcd.print("0");
      lcd.setCursor(16, 0);
      lcd.print(t.minute());
      lcd.setCursor(17, 0);
      lcd.print(":");
      
     }
     else{

      lcd.setCursor(15, 0);
      lcd.print(t.minute());
      lcd.print(":");
      
      }
     if(t.second() < 10){

      lcd.setCursor(18, 0);
      lcd.print("0");
      lcd.setCursor(19, 0);
      lcd.print(t.second());
      
     }
     else{

      lcd.setCursor(18, 0);
      lcd.print(t.second());
      
     }


     if(t.day() < 10){

      lcd.setCursor(3, 0);
      lcd.print("0");
      lcd.setCursor(4, 0);
      lcd.print(t.day());
      lcd.setCursor(5, 0);
      lcd.print("/");
      
     }
     else{

      lcd.setCursor(3, 0);
      lcd.print(t.day());
      lcd.print("/");
      
      }
      
     if(t.month() < 10){

      lcd.setCursor(6, 0);
      lcd.print("0");
      lcd.setCursor(7, 0);
      lcd.print(t.month());
      lcd.setCursor(8, 0);
      lcd.print("/");
      
     }
     else{

      

      lcd.setCursor(8, 0);
      lcd.print(t.month());
      lcd.print("/");
      
      }
      
      y = t.year() - 2000;
      
      lcd.setCursor(9, 0);
      lcd.print(y);

      lcd.setCursor(0, 0);
      lcd.print(daysOfTheWeekS[t.dayOfTheWeek()]);
    
  }
void mainMenu(){
  
    mainTeme();

    // ряд - 2
    
    lcd.setCursor(0, 1);
    lcd.print("AH-");
    lcd.setCursor(3, 1);
    lcd.print(ah);
    lcd.setCursor(5, 1);
    lcd.print("%");


    lcd.setCursor(7, 1);
    lcd.print("At-");
    lcd.setCursor(10, 1);
    lcd.print(at);
    lcd.setCursor(12, 1);
    lcd.print("C");


    lcd.setCursor(14, 1);
    lcd.print("SM-");
    lcd.setCursor(17, 1);
    lcd.print(sm);
    lcd.setCursor(19, 1);
    lcd.print("%");
    
    // ряд - 3

    lcd.setCursor(0, 2);
    lcd.print("Lux-");
    lcd.setCursor(4, 2);
    lcd.print(lux);

    lcd.setCursor(11, 2);
    lcd.print("Light-");
    lcd.setCursor(17, 2);
    lcd.print("on");

    //

    lcd.setCursor(0, 3);
    lcd.print("Watering-");
    lcd.setCursor(9, 3);
    lcd.print("on");

    lcd.setCursor(16, 3);
    lcd.print("Menu");
    
    
  }


void loop()
{   
    int val = analogRead(PIN_PHOTO_SENSOR);
    int osv = map(val, 0, 1023, 0, 100);
    //lux = osv;
    
    lux = lightMeter.readLightLevel(); // зчитуємо освітлення

    float ahf = dht.readHumidity(); // Влажність
    float atf = dht.readTemperature(); //  Температура

    at = atf; // температура в int
    ah = ahf; // влага в int

  
    mainMenu();
}
