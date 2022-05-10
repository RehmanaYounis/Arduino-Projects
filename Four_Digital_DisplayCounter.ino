//www.elegoo.com
//2016.12.12

int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
#include "Stepper.h"
#include "IRremote.h"



unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9

                             };

#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 3; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS,7, 5, 6, 4);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
   irrecv.enableIRIn(); // Start the receiver
   sevenSegWrite(0); 
   pinMode(31, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(2, OUTPUT);
}
void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}

void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latch, LOW);
     
  // the original data (bit pattern)
  shiftOut(data, clock, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latch, HIGH);
}
byte dispDigit = 1;
byte count2 = 0;
void loop() {
 digitalWrite(latch, LOW);
 shiftOut(data, clock, LSBFIRST, seven_seg_digits[dispDigit]);  
  
   
  // suspend 4 seconds
//  delay(1000);
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    switch(results.value)

    {

      case 0xFFA857: // VOL+ button pressed
                   
                    if (dispDigit <10){
                     dispDigit--;
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[dispDigit]);  
                      digitalWrite(31,LOW);  
                       digitalWrite(33,HIGH);  
                       digitalWrite(35,HIGH);  
                       digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);
                    }
                    else{
                      dispDigit=1;
                      count2--;
                      
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[count2]);  
                      digitalWrite(31,LOW);
                      digitalWrite(33,HIGH);
                      digitalWrite(35,HIGH);  
                      digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);
                      delay(500);
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[dispDigit]);  
                      digitalWrite(31,HIGH);
                      digitalWrite(33,LOW);
                      digitalWrite(35,HIGH);  
                      digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);
                    }
                      
//                    for (byte digit = 10; digit > 0; --digit) {
////                          delay(500);
//                      //    sevenSegWrite(digit - 1); 
//                          sevenSegWrite(dispDigit); 
//                        }
                      small_stepper.setSpeed(500); //Max seems to be 500
                      Steps2Take  =  500;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      digitalWrite(2, LOW);
//                      delay(500); 
                      break;

      case 0xFF629D: // VOL- button pressed
                      
                    if (dispDigit <10 && count2 ==0){
                      dispDigit++;
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[dispDigit]);  
                      digitalWrite(31,LOW);  
                       digitalWrite(33,HIGH);  
                       digitalWrite(35,HIGH);  
                       digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);
                      
                    }
                    else{
                      dispDigit=1;
                      
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[count2]);  
                      digitalWrite(31,LOW);
                      digitalWrite(33,HIGH);
                      digitalWrite(35,HIGH);  
                      digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);
                      delay(500);
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[dispDigit]);  
                      digitalWrite(31,HIGH);
                      digitalWrite(33,LOW);
                      digitalWrite(35,HIGH);  
                      digitalWrite(39,HIGH);  
                      digitalWrite(latch, HIGH);

                      
//                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[count2]); 
//                      digitalWrite(latch, LOW);
//                     digitalWrite(31,LOW);
// 
//                      digitalWrite(33,LOW);
//                      digitalWrite(35,HIGH);  
//                       digitalWrite(39,HIGH);  
//                      digitalWrite(latch, HIGH);
                      dispDigit+=1;
                      count2 += 1;
                      }
                      digitalWrite(2, HIGH);
                      small_stepper.setSpeed(500);
                      Steps2Take  =  -500;  // Rotate CCW
                      small_stepper.step(Steps2Take);
 
//                      delay(500);
                      break;
         case 0xFFA25D:
                      digitalWrite(latch, LOW);
                      shiftOut(data, clock, LSBFIRST, seven_seg_digits[8]);  
                      digitalWrite(31,LOW);  
                       digitalWrite(33,LOW);  
                       digitalWrite(35,LOW);  
                       digitalWrite(39,LOW);  
                      digitalWrite(latch,HIGH);
                      delay(1000);
                      break;
                
    }
   
      irrecv.resume(); // receive the next value
//                 digitalWrite(8, LOW);
//                 digitalWrite(9, LOW);
//                 digitalWrite(10, LOW);
//                 digitalWrite(11, LOW);       
  }  
//  Display(1);
//  delay(500);
//  Display(2);
//  delay(500);
//  Display(3);
//  delay(500);
//  Display(4);
//  delay(500);
//  Display(5);
//  delay(500);
//  Display(6);
//  delay(500);
//  Display(7);
//  delay(500);
//  Display(8);
//  delay(500);
//  Display(9);
//  delay(500);
//  Display(10);
//  delay(500);
//  Display(11);
//  delay(500);
//  Display(12);
//  delay(500);
//  Display(13);
//  delay(500);
//  Display(14);
//  delay(500);
//  Display(15);
//  delay(500);
}
