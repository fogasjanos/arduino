
// 9V + Vin, - Ground   G, Y, R
const int LIGHTS[] = {7, 6, 5, 4, 3, 2};
const int LIGHTS_LEN = 3;
const int STATES_COUNT = 32;

const int STATES[][3] = {
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {LOW, HIGH, LOW},
  {LOW, HIGH, LOW},
  {LOW, HIGH, LOW},

  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},

  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, LOW, HIGH},
  {LOW, HIGH, HIGH}
};

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long INTERVAL = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  for (int i = 0; i < 6; i++) {
    pinMode(LIGHTS[i], OUTPUT);
  }
}
int state = 0;
int ledStates[] = {0, (STATES_COUNT / 2)};
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    handleStateFrom(0);
    handleStateFrom(1);
  }
}

void handleStateFrom(int index) {
  if (++ledStates[index] == STATES_COUNT) {
    ledStates[index] = 0;
  }

  for (int i = 0; i < LIGHTS_LEN; i++) {
    int state = ledStates[index];
    digitalWrite(LIGHTS[i + (LIGHTS_LEN * index)], STATES[state][i]);
  }
}
