#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices
#include <LiquidCrystal_I2C.h>
// Create MFRC522 instance.
#define SS_PIN 3
#define RST_PIN 2
MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);
//ultrasonic sensor one
const int trigPin = 9;    // Trigger
const int echoPin = 8;    // Echo
const int relay = 7;
int distance;
float duration;
int state;

//ultrasonic sensor two
const int trigPin2 = 13;    // Trigger
const int echoPin2 = 12;    // Echo
int distance2;
float duration2;
int state2;
unsigned long previousMillis;
unsigned long distanceMillis;
bool Flag1 = false;
bool Flag2 = false;

// Buttons and state
int amButton = 11;
int ssButton = 10;
int ambuttonState;
int ssbuttonState; // button state of the start and stp manual button


// Lights
int relay2 = 5;
int buzzer = 6;

//variable resistors
int var1 = A0; // Manual time delay variable resistor
int var2 = A1; // Level changer variable resistor


void setup() {
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(amButton, INPUT);
  pinMode(ssButton, INPUT);
  //Protocol Configuration
  Serial.begin (9600);
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  // LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
//  ambuttonState = digitalRead(amButton);
//  Serial.println("AM button state: ");
//  Serial.println(ambuttonState);
//  if(ambuttonState == HIGH){
    if (millis() - distanceMillis > 500)
    {
      //restart timing
      distanceMillis = millis();
      getDistance();
      getDistance2();
    }

    if(distance <= 100 && Flag1 == false){
      Flag1 = true;
      digitalWrite(buzzer, Flag1);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      Serial.println("Relay on");
      previousMillis = millis();
    }
    else if(distance > 100){
      Flag1 = false;
    }
    if (distance <= 100)
    {
      unsigned long currentMillis = millis();
  
      if (currentMillis - previousMillis >= 5000)
      {
        Flag1 = false;
        digitalWrite(buzzer, Flag1);
        digitalWrite(relay, LOW);
        digitalWrite(relay2, LOW);
        Serial.println("Relay off");
        previousMillis = currentMillis;
        delay(3000);
        while(distance2 > 0 && distance2 < 100 && Flag1 == false){
          Serial.println(distance2);
          Serial.println("Error leave the tunnel");
          error();
          getDistance2();
          delay(200);
        }
      }
    }
//  }
//  else{
//    ssbuttonState = digitalRead(ssButton);
//    Serial.println(ssbuttonState);
//    int val = analogRead(var1);
//    int value = map(val,0,1023,5000,30000);
//    int value2 = map(value,5000,30000,5,30);
//    if(ssbuttonState == HIGH){
//      digitalWrite(relay, HIGH);
//      digitalWrite(relay2, HIGH);
//      start();
//      delay(value2);
//      Serial.println("Relay on");
//      Serial.println(value);
//    }
//    else{
//      digitalWrite(relay, LOW);
//      digitalWrite(relay2, LOW);
//      Serial.println("Relay off");
//    }
//  }
}
void getDistance(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

//  Serial.print("Distance: ");
//  Serial.println(distance);

}
void getDistance2(){
  // Ultrasonic sensor two
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);   
   
  // measure duration of pulse from ECHO pin
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

//  Serial.println("AM Button State: ");
//  Serial.println(ambuttonState);
//  Serial.println("SS Button State: ");
//  Serial.println(ssbuttonState);
  Serial.print("Distance : ");
  Serial.println(distance);
}
void error(){
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(300);  
}
void start(){
  digitalWrite(buzzer, HIGH);
  delay(700);
  digitalWrite(buzzer, LOW);
}
