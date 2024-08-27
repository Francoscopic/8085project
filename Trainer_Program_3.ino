/*
* This program is written to control a dc motor connected
* to the arduino PWM pin 11
* last updated: 26th July, 2024.
*/

#include <SoftwareSerial.h>
#define rxPin 2    // connected to bluetooth's transmit pin
#define txPin 3    // connected to bluetooth's receiver pin
#define DEFAULT 0  // default status
#define motorPin 11

SoftwareSerial bluetooth(rxPin, txPin);  // bluetooth object
String receivedCommand;                  // stores the commands received over the bluetooth
int speed = 0;

// multitasking control
unsigned int now;
unsigned int prev = 0;
unsigned int interval = 100;

void setup(void) {
  Serial.begin(115200);
  bluetooth.begin(38400);
  pinMode(motorPin, OUTPUT);
  
  // prevent the leds from coming on
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}  // end setup

void loop(void) {
  if (bluetooth.available() > 0) {
    receivedCommand = bluetooth.readString();
    speed = receivedCommand.toInt();

    // for debugging purposes
    Serial.print("Speed: ");
    Serial.println(speed);

    // feedback from microcontroller
    bluetooth.print("*A");
    bluetooth.print(map(speed, 0, 255, 0, 100));
    bluetooth.println("*A");
  }  // end if

  spinMotor(speed);
}  // end main

void spinMotor(int s) {
  analogWrite(motorPin, speed);
  // delay(50);
}  // end spinMotor
