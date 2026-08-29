#include <Wire.h>

#define smokeSensorPin 2
#define buzzerPin 3

ssmoke lcd(0x27, 16, 2);

void setup() {
  pinMode(smokeSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("MQ-2 Smoke Test");
  delay(2000);
  lcd.clear();
}

void loop() {
  int smokeStatus = digitalRead(smokeSensorPin);

  if (smokeStatus == LOW) {
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print(" Smoke Detected ");
    Serial.println("Smoke Detected!");
  } else {
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print(" Air Clean ");
    Serial.println("Air Clean");
  }

  delay(500);
}
