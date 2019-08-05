#include <IRremote.h>
#include <IRremoteInt.h>
#include "MyIrRemote.h"
/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int GREEN =  7;      // the number of the LED pin
const int YELLOW = 6;
const int RED = 5;
const int RECV_PIN = 13;

// variables will change:
IRrecv receiver(RECV_PIN);
decode_results results;
int activeLed = GREEN;         // variable for reading the pushbutton status
int state = 0x00000000;

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();

  // initialize the LED pin as an output:
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

int revert(int state) {
  if(state == HIGH) {
    return LOW;
  }
  return HIGH;
}

void blinkFrom(int state) {
  digitalWrite(activeLed, revert(state));
  delay(100);
  digitalWrite(activeLed, state);
  delay(1000);
}

void handleIr(int value) {
  switch (value) {
    case IR_1:
      activeLed = GREEN;
      break;
    case IR_2:
      activeLed = YELLOW;
      break;
    case IR_3:
      activeLed = RED;
      break;
    case IR_EQ:
      if (bitRead(state, activeLed) == 0) {
        blinkFrom(LOW);
      } else {
        blinkFrom(HIGH);
      }
      digitalWrite(activeLed, HIGH);
      delay(100);
      digitalWrite(activeLed, LOW);
      break;
    case IR_PLUS:
      digitalWrite(activeLed, HIGH);
      bitWrite(state, activeLed, 1);
      break;
    case IR_MINUS:
      digitalWrite(activeLed, LOW);
      bitWrite(state, activeLed, 0);
      break;
  }
}

void loop() {
  if (receiver.decode(&results)) {
    // Debug
    Serial.println(results.value, HEX);
    handleIr(results.value);
    receiver.resume();
  }
}
