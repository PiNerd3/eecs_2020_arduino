/** bad_thermostat
 *  
 *    
 *  by Nathaniel Hamovitz
 *  2020-05-03
 */


//const byte GLYPHS1[] = {
//  0x3f, // 0011 1111 // 0
//  0x06, // 0000 0110 // 1
//  0x5b, // 0101 1011 // 2
//  0x4f, // 0100 1111 // 3
//  0x66, // 0110 0110 // 4
//  0x6d, // 0110 1101 // 5
//  0x7d, // 0111 1101 // 6
//  0x07, // 0000 0111 // 7
//  0x7f, // 0111 1111 // 8
//  0x6f, // 0110 1111 // 9
//};

const byte GLYPHS[] = {
  0xfc,
  0x60,
  0xda,
  0xf2,
  0x66,
  0xb6,
  0xbe,
  0xe2,
  0xfe,
  0xe6,
  0x0b,
  0xbd,
  0x3f
};
const byte R = 0x0b;
const byte G = 0xbd;
const byte B = 0x3f;

#include <dht_nonblocking.h>

// DHT (temperature and humidity sensor) library setup.

#define DHT_SENSOR_TYPE DHT_TYPE_11
const int DHT_SENSOR_PIN = 8;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//   From the example sketch, edited for style:
/* Poll for a measurement, keeping the state machine alive.  Returns true if a measurement is available.
 */
static bool measure_environment(float *temperature, float *humidity) {
//  static unsigned long measurement_timestamp = millis();
  
  // Measure once every four seconds.
//  if (millis() - measurement_timestamp > 500ul) {
    if (dht_sensor.measure(temperature, humidity)) {
//      measurement_timestamp = millis();
      return true;
    }
//  }

  return false;
}

// Global pin constants.
 
const int RED = 5;
const int GREEN = 6;
const int BLUE = 3;

const int Y_AXIS_ = A3; // Pin A5. On board as `VY`. `Y_AXIS` is a reserved token.
const int X_AXIS_ = A5; // Pin A3. On board as `VX`. `X_AXIS` is a reserved token.
const int SWITCH = 2; // Pin 2. On board as `SW`.

const int DATA_PIN = 12;
const int LATCH_PIN = A1;
const int CLOCK_PIN = 9;

const int DIGIT_1 = 11;
const int DIGIT_2 = 7;
const int DIGIT_3 = 4;
const int DIGIT_4 = 10;

bool pressed = false;
bool was_pressed = false;
int joy_val_1;
int joy_val_2;

unsigned int count = 0;
int thr = 3;
int fr = 4;

char humidity_color = 'R';

float getHumidity() {
  float temperature;
  float humidity;

  if (measure_environment(&temperature, &humidity)) {
    return humidity;
  } else {
    return -1.0;
  }
}

void show_glyphs(byte glyph) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, glyph);
  digitalWrite(LATCH_PIN, HIGH);
}

/** This function is adapted from Elegoo 2016.12.12
 *  Specifically, from their `Four_Digital` example sketch for using a seven-segment display with a 74HC595.
 *  It was called `Display`.
 */
void show_glyph(byte glyph, int digit) {
//  Serial.println(glyph, digit);
  
  pinMode(digit, INPUT);
//  digitalWrite(digit, LOW);

  delay(5);
  show_glyphs(glyph);
//  delay(15);
  
  pinMode(digit, OUTPUT);
  digitalWrite(digit, HIGH);
}

void turn_off_seven_segment() {
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);
  digitalWrite(DIGIT_4, HIGH);
}

void turn_on_seven_segment() {
  pinMode(DIGIT_1, INPUT);
  pinMode(DIGIT_2, INPUT);
  pinMode(DIGIT_3, INPUT);
  pinMode(DIGIT_4, INPUT);
}

int hum_to_led(float hum) {
  // TODO: make fancier?
  return (int)(hum * 2.55);
}

void setup() {
  // initialize RGB LED pins as outputs
  pinMode(RED  , OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE , OUTPUT);

  pinMode(SWITCH, INPUT_PULLUP);

  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  turn_off_seven_segment();
//  turn_on_seven_segment();

  Serial.begin(9600);
}

void loop() {
  pressed = digitalRead(SWITCH) == HIGH ? false : true;
  if (!pressed) {
    if (was_pressed) {
//      Serial.print("Switching color! Color was: "); Serial.println(humidity_color);
      if (humidity_color == 'R') {
        humidity_color = 'G';
      } else if (humidity_color == 'G') {
        humidity_color = 'B';
      } else if (humidity_color == 'B') {
        humidity_color = 'R';
      }
//      Serial.print("                 Color is: "); Serial.println(humidity_color);
    }
    was_pressed = false;
  } else {
    was_pressed = true;
  }

  
  joy_val_1 = analogRead(X_AXIS_) / 4;
  joy_val_2 = analogRead(Y_AXIS_) / 4;

  float hum = getHumidity();
  int hum_led = hum_to_led(hum);
  if (humidity_color == 'R') {
    if (hum >= 0) {
      analogWrite(RED, hum_led);
    }
    
    show_glyph(R, DIGIT_1);

    analogWrite(GREEN, joy_val_1);
    analogWrite(BLUE, joy_val_2);
  } else if (humidity_color == 'G') {
    if (hum >= 0) {
      analogWrite(GREEN, hum_led);
    }

    show_glyph(G, DIGIT_1);
    
    analogWrite(BLUE, joy_val_1);
    analogWrite(RED, joy_val_2);
  } else if (humidity_color == 'B') {
    if (hum >= 0) {
      analogWrite(BLUE, hum_led);
    }

    show_glyph(B, DIGIT_1);

    analogWrite(RED, joy_val_1);
    analogWrite(GREEN, joy_val_2);
  } else {
    // Should be unreachable
    turn_off_seven_segment();

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }



//  Serial.print("humid led: "); Serial.print(humidity_color);
  if (hum >= 0) {
//    Serial.print(" | "); Serial.println(hum);
  }

  if (hum >= 99.5) {
//    Serial.println("Showing 1 in DIGIT_3");
    show_glyph(GLYPHS[1], DIGIT_2);
  }
//  delay(500);
  unsigned int ones_place = (int)(fmod(hum, 10.0f));
  if (ones_place >= 10) {
    ones_place = 9;
  }
//  show_glyph(GLYPHS[ones_place], DIGIT_4);
//  Serial.print("1's place: "); Serial.println(ones_place);
//  delay(500);
  hum /= 10;
  unsigned int tens_place = (int)(fmod(hum, 10.0f));
  if (tens_place >= 10) {
    tens_place = 9; 
  }
//  show_glyph(GLYPHS[tens_place], DIGIT_3);
//  Serial.print("10's place: "); Serial.println(tens_place);
//  delay(50);

  if (count % 500 == 0) {
    thr = random(0, 10);
    fr = random(0, 10);
  }

//  show_glyph(GLYPHS[thr], DIGIT_3);
//  show_glyph(GLYPHS[fr], DIGIT_4);

  

  count++;
}
