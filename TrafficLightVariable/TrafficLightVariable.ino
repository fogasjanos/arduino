// BOARD: Atmel atmega328p Xplained mini


// 9V + Vin, - Ground   G, Y, R
const int LIGHTS[] = {7, 6, 5, 4, 3, 2};
const int LIGHTS_LEN = 3;
const int STATES_COUNT = 25;
const int STATES_CONST[] = { LOW, HIGH };

const int LONG_STATES[][3] = {
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},

  {0, 1, 0},
  {0, 1, 0},
  {0, 0, 1},
  {0, 0, 1},

  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},

  {0, 1, 1}
};
const int SHORT_STATES[][3] = {
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},

  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 1, 1},

  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 0, 1},

  {0, 0, 1}
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
int ledStates[] = {0, 0};
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    handleLongState();
    handleShortState();
  }
}

void handleLongState() {
  handleStateFrom(0, LONG_STATES);
}

void handleShortState() {
  handleStateFrom(1, SHORT_STATES);
}

void handleStateFrom(int index, int statesArray[][3]) {
  if (++ledStates[index] == STATES_COUNT) {
    ledStates[index] = 0;
  }

  for (int i = 0; i < LIGHTS_LEN; i++) {
    int state = ledStates[index];
    int valueIndex = statesArray[state][i];
    digitalWrite(LIGHTS[i + (LIGHTS_LEN * index)], STATES_CONST[valueIndex]);
  }
}
