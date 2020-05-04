/** bad_thermostat
 *  
 *    
 *  by Nathaniel Hamovitz
 *  2020-05-03
 *  
 *  
 *  Some miscellaneous resources related to this sketch:
 *  - https://github.com/DeanIsMe/SevSeg (didn't use because it
 *  doesn't support shift registers (like the 74HC595 that I'm using).)
 *  - https://osoyoo.com/2017/08/08/arduino-lesson-4-digit-7-segment-led-display/
 *  this tutorial didn't suck
 *  - https://www.circuitbasics.com/arduino-7-segment-display-tutorial/
 *  this is the tutorial Jon recommended 
 *    
 */

// "0"-"9", indexed 0-9. Actually worked these out by hand as a (misguided, I think) attempt
// at troubleshooting. LSB first.
const byte GLYPHS[] = {
  0xfc,
  0x60,
  0xda,
  0xf2,
  0x66,
  0xb6,
  0xbe,
  0xe0,
  0xfe,
  0xe6
};
const byte R = 0x0b; // letter constants include the period to indicate their seperation
const byte G = 0xbd;
const byte B = 0x3f;
const byte OFF = 0x00; // no segments lit
const byte NO_INFO = 0b00000010; // a single dash

#include <dht_nonblocking.h>

// DHT (temperature and humidity sensor) library setup.

#define DHT_SENSOR_TYPE DHT_TYPE_11
const int DHT_SENSOR_PIN = 8;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//   From the example sketch, edited for style:
/* Poll for a measurement, keeping the state machine alive.  Returns true if a measurement is available.
 */
static bool measure_environment(float *temperature, float *humidity) { 
  static unsigned long measurement_timestamp = millis();
  
  // Measure once every four seconds.
  if (millis() - measurement_timestamp > 3000ul) {
    if (dht_sensor.measure(temperature, humidity)) {
      measurement_timestamp = millis();
      return true;
    }
  }

  return false;
}

// Global pin constants.

// RGB LED
const int RED = 5;
const int GREEN = 6;
const int BLUE = 3;

// Joystick
const int Y_AXIS_ = A3; // On board as `VY`. `Y_AXIS` is a reserved token.
const int X_AXIS_ = A5; // On board as `VX`. `X_AXIS` is a reserved token.
const int SWITCH = 2; // Pin 2. On board as `SW`.

// 74HC595
const int DATA_PIN = 12;
const int LATCH_PIN = A1;
const int CLOCK_PIN = 9;

// Seven-segment digit control pins
// the true ones
//const int DIGIT_1 = 11;
//const int DIGIT_2 = 7;
//const int DIGIT_3 = 4;
//const int DIGIT_4 = 10;

// the ones that work for some fucking reason
const int DIGIT_1 = 10;
const int DIGIT_2 = 11;
const int DIGIT_3 = 7;
const int DIGIT_4 = 4;

// Program variables

// joystick
bool pressed = false;
bool was_pressed = false;
int joy_val_1;
int joy_val_2;

// humidity
float hum = -1.0;
bool read_hum_yet = false; // don't light up the humidity indicator LED until we've read the humidity
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

/** This function is adapted from Elegoo 2016.12.12
 *  Specifically, from their `Four_Digital` example sketch for using a seven-segment display with a 74HC595.
 *  It was called `Display`.
 */
void show_glyphs(byte glyph) {
  digitalWrite(LATCH_PIN, LOW);
  // Reference on shiftOut (not very useful): https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, glyph);
  digitalWrite(LATCH_PIN, HIGH);
}

void show_glyph(byte glyph, int digit) {
  /** There are two options for toggling a pin:
   *    |      pin on       |      pin off      |
   *  --+-------------------+-------------------+
   *   1| pinMode OUTPUT    |                   |
   *    | digitalWrite LOW  | either way:       |
   *  --+-------------------+ pinMode OUTPUT    |
   *   2| pinMode INPUT     | digitalWrite HIGH |
   *  --+-------------------+-------------------+
   *  
   *  Option 1 seems to produce a brighter and steadier glow
   *  (hypotheses: possibly switching pin mode takes longer;
   *  or the 0V from LOW is much less resistance than
   *  whatever the control pin sees at an INPUT), so we use that.
   *  
   *  This does mean that those pins will be current sinks (I think) but evidently that's OK up to 20 mA:
   *  - https://forum.arduino.cc/index.php?topic=81794.0
   *  - https://arduino.stackexchange.com/questions/46394/can-arduino-on-output-mode-sink-current
   *  I don't have a multimeter to makes sure I'm within that limit,
   *  but the arduino doesn't seem broken yet, so ¯\_(ツ)_/¯.
   */    
  digitalWrite(digit, LOW);

  delay(2); // prevent bleed-over. `shiftOut` must (in the sense of 'I observe x, so y must be true.') be parallelized at some level (which makes sense).
  show_glyphs(glyph);
  
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

// deprecated
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

void drive_hum_led(int color, int strength, bool show) {
  if (show) { // can't use `hum_read_yet`, even though its a global; (I think) because Arduino hoists function definitions to the top of the file. Although I thought it was just declarations? Who knows.
    analogWrite(color, strength);
  } else {
    digitalWrite(color, LOW);
  }
}

void setup() {
  // initialize RGB LED pins as outputs
  pinMode(RED  , OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE , OUTPUT);

  // turn off RGB LED until we get data
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  pinMode(SWITCH, INPUT_PULLUP);

  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  turn_off_seven_segment();
}

void loop() {
  pressed = digitalRead(SWITCH) == HIGH ? false : true;
  if (!pressed) { // we act on button-up, not button-down. allows for a feeling of greater control.
    if (was_pressed) { // cycle what color it is; R -> G -> B -> R
      if (humidity_color == 'R') {
        humidity_color = 'G';
      } else if (humidity_color == 'G') {
        humidity_color = 'B';
      } else if (humidity_color == 'B') {
        humidity_color = 'R';
      }
    }
    was_pressed = false;
  } else {
    was_pressed = true;
  }

  joy_val_1 = analogRead(X_AXIS_) / 4;
  joy_val_2 = analogRead(Y_AXIS_) / 4;

  float new_hum = getHumidity();
  // don't update the humidity unless a new reading came in
  if (new_hum >= 0) {
    hum = new_hum;
    read_hum_yet = true;
  }
  int hum_led = hum_to_led(hum); // calculate the LED duty cycle based on the humidity value
  if (humidity_color == 'R') {
    show_glyph(R, DIGIT_1);
    
    drive_hum_led(RED, hum_led, read_hum_yet);
    analogWrite(GREEN, joy_val_1);
    analogWrite(BLUE, joy_val_2);
  } else if (humidity_color == 'G') {
    show_glyph(G, DIGIT_1);

    drive_hum_led(GREEN, hum_led, read_hum_yet);    
    analogWrite(RED, joy_val_2);
    analogWrite(BLUE, joy_val_1);
  } else if (humidity_color == 'B') {
    show_glyph(B, DIGIT_1);
    
    drive_hum_led(BLUE, hum_led, read_hum_yet);
    analogWrite(RED, joy_val_1);
    analogWrite(GREEN, joy_val_2);
  } else {
    // Should be unreachable
    turn_off_seven_segment();
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }  

  // for some godforsaken reason, need to write to the digits in the order 1-2-3-4
  // or else they get shuffled.
  // so all possible program paths need to follow that order.
  if (!read_hum_yet) {
    show_glyph(NO_INFO, DIGIT_2);
    show_glyph(NO_INFO, DIGIT_3);
    show_glyph(NO_INFO, DIGIT_4);
  } else {
    if (hum >= 99.5) {
      show_glyph(GLYPHS[1], DIGIT_2);
    } else {
      show_glyph(OFF, DIGIT_2);
    }

    show_glyph(GLYPHS[int(hum / 10) % 10], DIGIT_3);
    show_glyph(GLYPHS[int(hum)      % 10], DIGIT_4);
  } 
}
