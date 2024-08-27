/*
* This program is written to control a servo motor's 
* directon of rotation, with LED's cycling according to the direction
* of rotation.
* Last Updated: 26th JULY, 2024
*/

#include <SoftwareSerial.h>
#define rxPin 2  // connected to bluetooth's transmit pin
#define txPin 3  // connected to bluetooth's receiver pin

SoftwareSerial bluetooth(rxPin, txPin);  // bluetooth object
String receivedCommand;                  // stores the commands received over the bluetooth

// Stepper motor driver
int Pin1 = 4;  // IN1 is connected
int Pin2 = 5;  // IN2 is connected
int Pin3 = 6;  // IN3 is connected
int Pin4 = 7;  // IN4 is connected

int pole1[] = { 0, 0, 0, 0, 0, 1, 1, 1, 0 };  //pole1, 8 step values
int pole2[] = { 0, 0, 0, 1, 1, 1, 0, 0, 0 };  //pole2, 8 step values
int pole3[] = { 0, 1, 1, 1, 0, 0, 0, 0, 0 };  //pole3, 8 step values
int pole4[] = { 1, 1, 0, 0, 0, 0, 0, 1, 0 };  //pole4, 8 step values

int steps = 0;
int dirStatus = 3;  // stores direction status; 3 => stop (do not change)
int dir = 3;

// Define shift registers pins
#define dataPin 10
#define clockPin 8
#define latchPin 9
int sum = 255;

// multitasking control
unsigned int now;
unsigned int prev = 0;
unsigned int interval = 100;

void setup(void) {
  Serial.begin(115200);
  bluetooth.begin(38400);

  // stepper motor pins
  pinMode(Pin1, OUTPUT);  //define pin for ULN2003 in1
  pinMode(Pin2, OUTPUT);  //define pin for ULN2003 in2
  pinMode(Pin3, OUTPUT);  //define pin for ULN2003 in3
  pinMode(Pin4, OUTPUT);  //define pin for ULN2003 in4

  // shift registers
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}  // end setup

void loop(void) {
  now = millis();
  activateStepper(dirStatus);
  if (now - prev >= interval) {
    if (bluetooth.available() > 0) {
      receivedCommand = bluetooth.readString();
      dirStatus = receivedCommand.toInt();
    }  // end bluetooth
    
    cyclePattern(dirStatus);
    Serial.println(steps);
    prev = now;
  }  // end if
}  // end main loop


void driveStepper(int c) {
  //Watch details at my Arduino Course at Udemy.com
  digitalWrite(Pin1, pole1[c]);
  digitalWrite(Pin2, pole2[c]);
  digitalWrite(Pin3, pole3[c]);
  digitalWrite(Pin4, pole4[c]);
}  // end driveStepper

void activateStepper(int dirStatus) {
  if (dirStatus == 1) {
    driveStepper(steps);
    steps--;
  }  // CW rotation

  else if (dirStatus == 2) {
    driveStepper(steps);
    steps++;
  }  // CCW rotation

  else if (dirStatus == 3) {
    driveStepper(8);
  }  // stop; No rotation

  if (steps > 8) {
    steps = 0;
  }
  if (steps < 0) {
    steps = 8;
  }
  delay(1);
}  // end activateStepper

void cyclePattern(int d) {
  if (d == 3) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);  // Turn off LEDs
    digitalWrite(latchPin, HIGH);
  }  // stop

  else if (d == 2) {
    sum = 2 * sum + 1;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, sum);
    digitalWrite(latchPin, HIGH);
  }  // cw rotation

  else if (d == 1) {
    sum = 2 * sum + 1;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, sum);
    digitalWrite(latchPin, HIGH);
  }  // ccw rotation


  if (sum >= 255) {
    sum = 0;
  }
}  //end cyclePattern

void cyclingPattern(int directionOfRev) {
  if (directionOfRev == 1) {
    // Cycling pattern for clockwise rotation
    for (int i = 0; i <= 7; i++) {
      sum = 2 * sum + 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, sum);
      digitalWrite(latchPin, HIGH);
      delay(50);
    }

    // from behind
    for (int i = 0; i <= 7; i++) {
      sum = sum << 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, sum);
      digitalWrite(latchPin, HIGH);
      delay(50);
    }
  }  //end if

  else if (directionOfRev == 2) {
    // Cycling pattern for counterclockwise rotation
    for (int i = 0; i <= 7; i++) {
      sum = 2 * sum + 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, sum);
      digitalWrite(latchPin, HIGH);
      delay(50);
    }

    // from behind
    for (int i = 0; i <= 7; i++) {
      sum = sum << 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, sum);
      digitalWrite(latchPin, HIGH);
      delay(50);
    }
  }  //end else-if
  else {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
  }
}  //end cyclingPattern
