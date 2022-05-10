//www.elegoo.com
//2016.12.9 

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  leds = 0;
     updateShiftRegister();
//  for (int i = 0; i < 8; i++)
////  {
//     leds = 8;
//     updateShiftRegister();
//      leds = 16;
//      delay(500);
//      updateShiftRegister();
////      delay(500);
////  }
//  
 delay(500);
   for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
  leds = 0;
  updateShiftRegister();
  for (int i = 8; i > 0; i--)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}
