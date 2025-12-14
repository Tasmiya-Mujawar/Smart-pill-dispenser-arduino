#include <Servo.h>

Servo myServo;

int buzzer = 8;
int buttonPin = 7;
int potPin = A0;

bool alarmActive = false;
bool systemArmed = false;
bool potWasLow = true;   // For edge detection

void setup() {
  myServo.attach(9);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(buzzer, LOW);
  myServo.write(0);

  delay(2000);  // Stabilize
}

void loop() {
  int potValue = analogRead(potPin);

  // Arm system once pot is brought to LOW
  if (potValue < 100) {
    systemArmed = true;
    potWasLow = true;
  }

  // Detect rising edge (LOW → HIGH)
  if (systemArmed && potWasLow && potValue > 700) {
    dispensePill();
    alarmActive = true;
    potWasLow = false;
  }

  // Reset button logic
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(buzzer, LOW);
    alarmActive = false;
  }
}

void dispensePill() {
  myServo.write(90);
  delay(2000);
  myServo.write(0);
  digitalWrite(buzzer, HIGH);
}
