// CONSTANTS
const bool COMMON_CATHODE = !true;

const int DATA_PIN = 12;
const int LATCH_PIN = 11;
const int CLOCK_PIN = 9;
const int UNITS_PLACE_PIN = 2;
const int TENS_PLACE_PIN = 3;
const int HUNDREDS_PLACE_PIN = 4;
const int THOUSANDS_PLACE_PIN = 5;

const int DELAY_TIME = 5;  // milli seconds

const byte DIGIT_0_9[] = {
B11111100,  // 0
B01100000,  // 1
B11011010,  // 2
B11110010,  // 3
B01100110,  // 4
B10110110,  // 5
B10111110,  // 6 
B11100000,  // 7
B11111110,  // 8
B11100110   // 9
};

// VARIABLES
byte digit;
// BYTE
byte minutes_ones_byte;
byte minutes_tens_byte;
byte hours_ones_byte;
byte hours_tens_byte;
// MINUTES + HOURS + SECONDS
// INT
int hours_int = 8;
int minutes_int = 30;
int seconds_int = 0;
// ONES & TENS
int minutes_ones_int;
int minutes_tens_int;
int hours_ones_int;
int hours_tens_int;
// OTHER
int minutes_counter = 0;

void setup() {
// put your setup code here, to run once:
pinMode(DATA_PIN, OUTPUT);
pinMode(LATCH_PIN, OUTPUT);
pinMode(CLOCK_PIN, OUTPUT);
pinMode(UNITS_PLACE_PIN, OUTPUT);
pinMode(TENS_PLACE_PIN, OUTPUT);
pinMode(HUNDREDS_PLACE_PIN, OUTPUT);
pinMode(THOUSANDS_PLACE_PIN, OUTPUT);

}

void loop() {
// put your main code here, to run repeatedly:

// iterate over 10 decimal digits >> 0...9

  // splitting digits
  if (seconds_int == 59) {
    minutes_counter++;
    minutes_int++;
    if (minutes_counter == 5) {
      seconds_int = 1;
      minutes_counter = 0;
    }
    else {
      seconds_int = 0;
    }
  }
  
  if (minutes_int == 60) {
    hours_int++;
    minutes_int = 0;
  }

  if (hours_int == 13) {
    hours_int = 1;
  }
  
  // split digits
  // minutes
  if (minutes_int > 9) {
    minutes_ones_int = minutes_int%10;
    minutes_tens_int = minutes_int/10;
  }
  else{
    minutes_ones_int = minutes_int;
    minutes_tens_int = 0;
  }

  // hours
  if (hours_int > 9) {
    hours_ones_int = hours_int%10;
    hours_tens_int = hours_int/10;
  }
  else{
    hours_ones_int = hours_int;
    hours_tens_int = 0;
  }

  seconds_int++;
  
  // switch integer to binary
  hours_tens_byte = DIGIT_0_9[hours_tens_int];
  hours_ones_byte = DIGIT_0_9[hours_ones_int];
  minutes_tens_byte = DIGIT_0_9[minutes_tens_int];
  minutes_ones_byte = DIGIT_0_9[minutes_ones_int];
  
  // check whether display is common cathode or anode
  // >> use logical NOT operator
  if (!COMMON_CATHODE) {
    // this is a common anode display >> flip the bits
    // >> use bitwise NOT operator
    hours_tens_byte = ~hours_tens_byte;
    hours_ones_byte = ~hours_ones_byte;
    minutes_tens_byte = ~minutes_tens_byte;
    minutes_ones_byte = ~minutes_ones_byte;
  }
  
  // display the number
  for (int y = 1; y <= 50; y++) {

    digitalWrite(UNITS_PLACE_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, minutes_ones_byte);
    digitalWrite(LATCH_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(UNITS_PLACE_PIN, LOW);

    digitalWrite(TENS_PLACE_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, minutes_tens_byte);
    digitalWrite(LATCH_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(TENS_PLACE_PIN, LOW);

    digitalWrite(HUNDREDS_PLACE_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, hours_ones_byte);
    digitalWrite(LATCH_PIN, HIGH);
    delay(DELAY_TIME);
    digitalWrite(HUNDREDS_PLACE_PIN, LOW);

    if (hours_tens_int != 0) {
      digitalWrite(THOUSANDS_PLACE_PIN, HIGH);
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, hours_tens_byte);
      digitalWrite(LATCH_PIN, HIGH);
      delay(DELAY_TIME);
      digitalWrite(THOUSANDS_PLACE_PIN, LOW);
    }
    else {
      delay(DELAY_TIME);
    }
  }  
}
