/** color_wheel
 *  
 *  Controls an RGB LED (or 3 LEDs) off a joystick, such as the one in the Elegoo Arduino Super Starter Kit.
 *  
 *  Maps the joystick circle to a color wheel circle, roughly.
 *  
 *  by Nathaniel Hamovitz
 *  2020-03-18
 */

#define DEBUG false

const int RED = 3;
const int GREEN = 9;
const int BLUE = 10;

const int Y_AXIS_ = 5; // Pin A5. On board as `VY`. `Y_AXIS` is a reserved token.
const int X_AXIS_ = 3; // Pin A3. On board as `VX`. `X_AXIS` is a reserved token.
const int SWITCH = 2; // Pin 2. On board as `SW`.


inline double adjustRed(double green, double blue) {
  const double BRIGHTNESS_SCALAR = 255 / sqrt(pow(255, 2) + pow(255, 2));

  const double MAX_RED = 200;
  const double RED_SCALAR = MAX_RED / 255;

  const double raw_blue_green_brightness = sqrt(pow(green, 2) + pow(blue, 2));
  const double blue_green_brightness = raw_blue_green_brightness * BRIGHTNESS_SCALAR;
  const double red_brightness = 255 - blue_green_brightness; // make red dimmer as blue & green increase
  const double dimmer_red = red_brightness * RED_SCALAR;
  return dimmer_red;
}

void setup() {
  // initialize LED pins as outputs
  pinMode(RED  , OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE , OUTPUT);

  pinMode(SWITCH, INPUT_PULLUP);

  Serial.begin(9600); while (!Serial) {;};

}

void loop() {
  const bool pressed = digitalRead(SWITCH) == HIGH ? false : true;
  const double x = analogRead(X_AXIS_);
  const double y = analogRead(Y_AXIS_);

#ifdef DEBUG
  Serial.print("x: "); Serial.print(x, 4); Serial.print("\n");
  Serial.print("y: "); Serial.print(y, 4); Serial.print("\n\n");
  delay(100);
#endif

  const double r = sqrt(pow(x, 2) + pow(y, 2));
  const double theta = atan2(y, x); // -pi to pi: https://www.nongnu.org/avr-libc/user-manual/group__avr__math.html#ga054230cd7e4c12958dbfac75ab6886e5

  if (pressed) {
    analogWrite(RED, adjustRed(x, y));
  } else {
    digitalWrite(RED, LOW);
  }

//  analogWrite(GREEN, green_val);
//  analogWrite(BLUE, blue_val);
}
