int spots = 0;
int outpin = 0;
long ignore = 0;

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  ignore = 2000 + millis();
}

void loop() {
  for (outpin = 1; outpin < 5; outpin++) {
    digitalWrite(outpin, LOW);
  }

  spots = random(1, 7);

  if (spots == 6) {
    digitalWrite(1, HIGH);
  }
  if (spots == 1 || spots == 3 || spots == 5) {
    digitalWrite(2, HIGH);
  }
  if (spots > 3) {
    digitalWrite(3, HIGH);
  }
  if (spots > 1) {
    digitalWrite(4, HIGH);
  }

  delay(20);

  if (millis() > ignore && digitalRead(0) == LOW) {
    checkbutton();
  }
}

void checkbutton() {
  delay(50);
  while (digitalRead(0) == LOW) {}
  delay(50);
  while (digitalRead(0) == HIGH) {}
  ignore = 2000 + millis();
}
