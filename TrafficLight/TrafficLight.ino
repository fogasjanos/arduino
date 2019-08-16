
// 9V + Vin, - Ground   G, Y, R
const int LIGHTS[] = {7, 6, 5};
const int STATES_COUNT = 18;
const int STATES[][3] = {
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
  {HIGH, LOW, LOW},
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
  {LOW, HIGH, HIGH}
};

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long INTERVAL = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  int len = sizeof(LIGHTS);
  for (int i = 0; i < len; i++) {
    pinMode(LIGHTS[i], OUTPUT);
  }
}
int state = 0;
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;


    handleState();

  }
}

void handleState() {
  if (++state == STATES_COUNT) {
    state = 0;
  }

  for (int i = 0; i < 3; i++) {
    digitalWrite(LIGHTS[i], STATES[state][i]);
  }
}
