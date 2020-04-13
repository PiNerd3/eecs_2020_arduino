int spots = 0;
int outpin = 0;
long ignore = 0;

const int LED_3 = 13;
const int LED_2 = 12;
const int LED_1 = 6;
const int LED_4 = 8;
const int BUTTON_0 = 11;

void setup() {
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  ignore = 2000 + millis();

//  Serial.begin(9600);
}

void loop() {
//  for (outpin = 1; outpin < 5; outpin++) {
//    digitalWrite(outpin, LOW);
//  }
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);

  spots = random(1, 7);

//  Serial.println(spots);

  if (spots == 6) {
    digitalWrite(LED_1, HIGH);
  }
  
  if (spots == 1 || spots == 3 || spots == 5) {
    digitalWrite(LED_2, HIGH);
  }
  if (spots > 3) {
    digitalWrite(LED_3, HIGH);
  }
  if (spots > 1) {
    digitalWrite(LED_4, HIGH);
  }

  delay(20);

  if (millis() > ignore && digitalRead(BUTTON_0) == LOW) {
    checkbutton();
  }
}

void checkbutton() {
  delay(50);
  while (digitalRead(BUTTON_0) == LOW) {}
  delay(50);
  while (digitalRead(BUTTON_0) == HIGH) {}
  ignore = 2000 + millis();
}
