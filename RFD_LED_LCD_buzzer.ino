//www.elegoo.com
//2018.10.24
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
int tempPin = 0;
#define RST_PIN   4     // Configurable, see typical pin layout above
#define SS_PIN    53   // 

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

/* Set your new UID here! */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}

MFRC522::MIFARE_Key key;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define BLUE 3
#define GREEN 5
#define RED 6
int buzzer = 2;
void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);
  while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init(); 
  pinMode(buzzer,OUTPUT);
 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
  lcd.setCursor(0, 0);
  lcd.print("Enter Passcode");
}

void loop()
{
lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("Enter Passcode");
  
  
//  delay(500);
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }

Serial.print(F("Card UID:"));
String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


    //0C 2D EC 37  blue kechain

        if (content.substring(1) == "13 D4 16 07"){
          String msg= "Authorized Access";
          lcd.setCursor(0, 1);
          lcd.print(msg);
//          delay(500);
          digitalWrite(RED, LOW);
          digitalWrite(GREEN, 255);
          analogWrite(BLUE, LOW);
          delay(200);
          digitalWrite(GREEN, 0);
          delay(200);
          digitalWrite(GREEN, 255);
          delay(200);
          digitalWrite(GREEN, 0);
          digitalWrite(buzzer,HIGH);
          delay(250);//wait for 1ms
          digitalWrite(buzzer,LOW);
          delay(500);//wait for 1ms
          
          
        }
        else{
         for(int i=0;i<180;i++)
         {
          digitalWrite(buzzer,HIGH);
          delay(1);//wait for 1ms
          digitalWrite(buzzer,LOW);
          delay(1);//wait for 1ms
          } 
         String msg= "Unauthorized Access";
          lcd.setCursor(0, 1);
          lcd.print(msg);
          digitalWrite(GREEN, LOW);
          digitalWrite(BLUE, LOW);
          analogWrite(RED, 255);
          delay(200);
          digitalWrite(RED, 0);
          delay(200);
          digitalWrite(RED, 255);
          delay(200);
          digitalWrite(RED, 0);
        }
     
      
  
  

//  delay(1000);
}
