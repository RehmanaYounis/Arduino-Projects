//www.elegoo.com
//2018.10.24
#include <Wire.h>
#include <DS3231.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];
DS3231 clock;
RTCDateTime dt;
#define BLUE 3
#define GREEN 5
#define RED 6

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);

  Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();

  
  // Manual (YYYY, MM, DD, HH, II, SS
  // clock.setDateTime(2016, 12, 9, 11, 46, 00);
  
  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    
  /*
  Tips:This command will be executed every time when Arduino restarts. 
       Comment this line out to store the memory of DS3231 module
  */
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
   lcd.print("No water");
}

void loop()
{
  dt = clock.getDateTime();
  
  // For leading zero look to DS3231_dateformat example

//  Serial.print("Raw data: ");
//  Serial.print(dt.year);   Serial.print("-");
//  Serial.print(dt.month);  Serial.print("-");
//  Serial.print(dt.day);    Serial.print(" ");
//  Serial.print(dt.hour);   Serial.print(":");
//  Serial.print(dt.minute); Serial.print(":");
//  Serial.print(dt.second); Serial.println("");
//  String mtime= String(dt.hour)+":"+String(dt.minute)+":"+String(dt.second);
//  lcd.setCursor(0, 0);
//  lcd.print(mtime);
   int value = analogRead(adc_id); // get adc value

    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      Serial.print(printBuffer);
      HistoryValue = value;
       String sentence= "water level: "+String(value);
      lcd.clear();
       if (value <= 60){
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, LOW);
        analogWrite(GREEN, 255);
        String msg= "Below Threshold";
        lcd.setCursor(0, 0);
        lcd.print(msg);
        }
        if (value > 60 && value <= 170){
          digitalWrite(RED, LOW);
          digitalWrite(GREEN, LOW);
          analogWrite(BLUE, 255);
          String msg= "Average Level";
          lcd.setCursor(0, 0);
          lcd.print(msg);
        }
        if (value > 170 ){
         String msg= "Above Threshold";
          lcd.setCursor(0, 0);
          lcd.print(msg);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        analogWrite(RED, 255);
        }
     
       lcd.setCursor(0, 1);
       lcd.print(sentence);
       
    }
  
  

//  delay(1000);
}
