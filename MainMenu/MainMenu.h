#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <LiquidCrystal_I2C.h> //дисплей
#include <RTClib.h>

RTC_DS3231 rtc;
DateTime t;
String daysOfTheWeek[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String monthsNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
String daysOfTheWeekS[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

int y; // змінні для правильного відобрачення часу

LiquidCrystal_I2C lcd(0x27,20,4); //обявили дисплей
void Clock(){
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

void mainMenu(int AT, int AH, int LUX){

    int ah = AH;
    int at = AT;
    int lux = LUX;

    Clock();

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

#endif