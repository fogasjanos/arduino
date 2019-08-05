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
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin
const int RECV_PIN = 13;


IRrecv receiver(RECV_PIN);
decode_results results;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status



void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}


void handleIr(int value) {
  switch (value) {
    case IR_PLUS:
      digitalWrite(ledPin, HIGH);
      break;
    case IR_MINUS:
      digitalWrite(ledPin, LOW);
      break;
  }
}

void loop() {
  if (receiver.decode(&results)) {
    Serial.println(results.value, HEX);
    handleIr(results.value);
    receiver.resume();
  }
  
}
