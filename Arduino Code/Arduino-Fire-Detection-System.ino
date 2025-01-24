#include <Wire.h>
#include "HUSKYLENS.h"
#include <LiquidCrystal.h>
#include <Servo.h>

HUSKYLENS huskylens;
Servo myServo;

// LCD ekran pinleri: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int gasSensorPin = A0;  // Gaz sensörünün arduinoda bağlı olduğu pin
int tempSensorPin = A1; // sıcaklık sensörünün bağlı olduğu pin
int buzzerPin = 8;  // Buzzer'ın bağlı olduğu pin
int gasThreshold = 80;  // Gaz seviyesi eşiği
int tempThreshold = 390; // Sıcaklık eşiği

void setup() {
  Serial.begin(9600);  
  Wire.begin();  
  huskylens.begin(Wire);

  lcd.begin(16, 4);  
  myServo.attach(9);  
  pinMode(buzzerPin, OUTPUT);  
  myServo.write(0);  

  if (!huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION)) {
    lcd.clear();
    lcd.print("Huskylens hatasi!");
    Serial.println("Huskylens algoritma yazma hatası!");  
    while (1);  
  } else {
    lcd.clear();
    lcd.print("Huskylens hazir.");
    Serial.println("Huskylens algoritma yazıldı ve hazır.");  
  }
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);  // Gaz seviyesini oku
  int tempLevel = analogRead(tempSensorPin); // Sıcaklık seviyesini oku

  Serial.print("Gaz Seviyesi: ");
  Serial.println(gasLevel);  

  Serial.print("Sıcaklık Seviyesi: ");
  Serial.println(tempLevel);  

  bool flameDetected = false;

  if (huskylens.request()) {
    for (int i = 0; i < huskylens.count(); i++) {  
      HUSKYLENSResult result = huskylens.read();  
      if (result.command == COMMAND_RETURN_BLOCK && result.ID == 1) {  // "1" ID'li nesneyi alev olarak öğretmelisin
        flameDetected = true;
        break;
      }
    }
  }

  if (gasLevel > gasThreshold || tempLevel < tempThreshold || flameDetected) {
    lcd.clear();
    lcd.print("Tehlike Algilandi!");
    myServo.write(90);  // Servo motorunu 90 derece döndür
    digitalWrite(buzzerPin, HIGH);  // Buzzer'ı çalıştır
    delay(2000);  // 2 saniye bekle
    digitalWrite(buzzerPin, LOW);  // Buzzer'ı durdur  
    lcd.clear();
  } else {
    lcd.clear();
    lcd.print("Durum Normal");
    myServo.write(0);  // Servo motoru başlangıç pozisyonuna getir
  }

  delay(500);  
}
