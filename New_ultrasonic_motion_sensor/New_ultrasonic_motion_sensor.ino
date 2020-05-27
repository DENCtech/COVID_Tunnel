#include <LiquidCrystal_I2C.h>
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
//ultrasonic sensor three
const int trigPin3 = 4;    // Trigger
const int echoPin3 = 3;    // Echo
int distance3;
float duration3;
int state3;

const unsigned long interval = 7000;           // interval at which to blink (milliseconds)
unsigned long previousMillis;
unsigned long distanceMillis;
// Buttons and state
int amButton = 11;
int ssButton = 10;
int ambuttonState = LOW;
int ssbuttonState = LOW;
// Lights
int relay2 = 5;
int buzzer = 6;
//variable resistors
int var1 = A0;
int var2 = A1;

void setup() {
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(relay2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(buzzer, LOW);
  // LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("ROBOTICS--CENTER");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.setCursor(0, 2);
  lcd.print("ChemLevel: ");
  lcd.setCursor(0, 3);
  lcd.print("Duration: ");
  chemLevel();
  ambuttonState = digitalRead(amButton);
  if(ambuttonState == HIGH){
    getDistance();
    getDistance2();
    if(distance <= 100){
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      Serial.println("Relay on");
      delay(interval);
    }
    else{
      Serial.println("Relay off");
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
      digitalWrite(relay2, LOW);
      delay(100);  
    }
  }
  else{
    ssbuttonState = digitalRead(ssButton);
    if(ssbuttonState == HIGH){
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      Serial.println("Relay on");
      delay(interval);
    }
    else{
      Serial.println("Relay off");
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
      digitalWrite(relay2, LOW);
      delay(500);
    }
  }
  
}
int getDistance(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}
int getDistance2(){
  // Ultrasonic sensor two
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);   
   
  // measure duration of pulse from ECHO pin
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  Serial.print("Distance 2: ");
  Serial.println(distance2);
}
void getDistance3(){
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

//  Serial.print("Distance3: ");
//  Serial.println(distance3);
}
void chemLevel(){
  getDistance3();
  state3 = digitalRead(echoPin3);
  Serial.println(state3);
  int val1 = analogRead(var2);
  int val2 = map(val1,0,1023,0,100);
  int depth = map(state3,0,45,0,100);
  if(distance3 >= val2){
    Serial.println("0%");
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
    digitalWrite(relay2, LOW);
    delay(500);
  }
  
}
