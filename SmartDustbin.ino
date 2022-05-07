
#include <Servo.h>
#include "LedControl.h"

// constants won't change
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 2 is connected to the DataIn 
 pin 7 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */

LedControl lc=LedControl(2,10,7,1);
unsigned long delaytime1=500;
unsigned long delaytime2=50;

const int TRIG_PIN  = 13;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 12;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_PIN = 11; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 50; // centimeters

Servo servo; // create servo object to control a servo
void drawImage(byte image[]){
  for(int i =0; i<=7; i++){
    lc.setRow(0, i, image[i]);
  }
}

// variables will change:
float duration_us, distance_cm;
//byte down[8]= {0x18,0x18,0x18,0x18,0xff,0x7e,0x3c,0x18};
byte up[8]= {0x10,0x10,0x30,0xff,0xff,0x30,0x10,0x10};
//byte up[8]={0x18,0x3c,0x7e,0xff,0x18,0x18,0x18,0x18};
byte down[8]={0x00,0x18,0x04,0x04,0x04,0x04,0x18,0x00};
void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < DISTANCE_THRESHOLD){
    servo.write(80); // rotate servo motor to 90 degree
    drawImage(up);}
  else
  {
    drawImage(down);
    servo.write(30);  // rotate servo motor to 0 degree
  }
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
