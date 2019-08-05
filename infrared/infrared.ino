#include <IRremote.h>
#include <IRremoteInt.h>
#include "MyIrRemote.h"

// based on: https://www.instructables.com/id/Using-Infrared-Sensor-With-Arduino/

// see circuit.jpg

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
  if (state == HIGH) {
    return LOW;
  }
  return HIGH;
}

void blinkLed(int pin) {
  digitalWrite(pin, revert(state));
  delay(100);
  digitalWrite(pin, state);
}

void led(int pin, int value) {
  bitWrite(state, pin, value == HIGH ? 1 : 0);
  Serial.print("STATE: ");
  Serial.println(state, BIN);
  digitalWrite(pin, value);
}

void handleIr(int value) {
  switch (value) {
    case IR_1:
      led(GREEN, HIGH);
      break;
    case IR_2:
      led(YELLOW, HIGH);
      break;
    case IR_3:
      led(RED, HIGH);
      break;
    case IR_4:
      led(GREEN, LOW);
      break;
    case IR_5:
      led(YELLOW, LOW);
      break;
    case IR_6:
      led(RED, LOW);
      break;
    case IR_7:
      blinkLed(GREEN);
      break;
    case IR_8:
      blinkLed(YELLOW);
      break;
    case IR_9:
      blinkLed(RED);
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
