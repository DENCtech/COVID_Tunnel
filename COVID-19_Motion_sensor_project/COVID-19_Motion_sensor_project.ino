#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);

int relayPin = 7;                // choose the pin for the Relay Pin

int inputPin = 11;               // choose the input pin (for PIR sensor)
int inputPin2 = 9;               // choose the input pin (for PIR sensor 02)
const int relay = 7;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int val2 = 0;                    // variable for reading the pin status
const unsigned long minInterval = 5000;           // interval at which to blink (milliseconds)
const unsigned long maxInterval = 30000;           // interval at which to blink (milliseconds)

// Buttons and state
int amButton = 8;
int ssButton = 12;
int ambuttonState = LOW;
int ssbuttonState = LOW;

// Lights
int relay2 = 5;
int buzzer = 6;

//variable resistors
int var1 = A0;
int var2 = A1;

//ultrasonic sensor one
const int trigPin3 = 13;    // Trigger
const int echoPin3 = 12;    // Echo
int distance3;
float duration3;
int state3;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);      // declare Relay as output
  pinMode(relay2, OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT); 
  pinMode(amButton, INPUT);
  pinMode(ssButton, INPUT); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(buzzer, LOW);
  delay(100);
  Serial.begin(9600);
  // LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  chemLevel();
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("ROBOTICS--CENTER");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.setCursor(-4, 2);
  lcd.print("ChemLevel: ");
  lcd.setCursor(-4, 3);
  lcd.print("Duration: ");
  ambuttonState = digitalRead(amButton);
  if(ambuttonState == HIGH){
    lcd.setCursor(7, 1);
    lcd.print("      ");
    lcd.setCursor(7, 1);
    lcd.print("AUTO");
    val = digitalRead(inputPin);  // read input value
    val2 = digitalRead(inputPin2);  // read input value
    if (val == HIGH) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      delay(5000);
      digitalWrite(relay, LOW);
      digitalWrite(relay2, LOW);
      delay(10);
      while(val2 == LOW){
        val2 = digitalRead(inputPin2);// read input value
        delay(10);
      }
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
    }
  }
  else{
    lcd.setCursor(7, 1);
    lcd.print("      ");
    lcd.setCursor(7, 1);
    lcd.print("MANUAL");
    ssbuttonState = digitalRead(ssButton);
    int var4 = digitalRead(var2);
    int var5 = map(var4,0,1023,minInterval,maxInterval);
    int var6 = map(var5,minInterval,maxInterval,5,30);
    lcd.setCursor(7, 3);
    lcd.print("      ");
    lcd.setCursor(7, 3);
    lcd.print(var6+"secs");
    if(ssbuttonState == HIGH){
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      delay(var6);
    }
    else{
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
      digitalWrite(relay2, LOW);
      delay(500);
    }
  }
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
  int val1 = analogRead(var1);
  int val3 = map(val1,0,1023,0,100);
  if(distance3 >= val3){
    lcd.setCursor(7, 2);
    lcd.print("    ");
    lcd.setCursor(7, 2);
    lcd.print(val3+"%");
    Serial.println("0%");
  }
//  if(distance3 > 0 && distance3 < 20){
//    state3 = HIGH;
//    Serial.println("100%");
//  }
//  if(distance3 > 19 && distance3 < 40){
//    state3 = HIGH;
//    Serial.println("100%");
//  }
//  if(distance3 > 39 && distance3 < 60){
//    state3 = HIGH;
//    Serial.println("60%");
//  }
//  if(distance3 > 59 && distance3 < 80){
//    state3 = HIGH;
//    Serial.println("20%");
//  }
//  if(distance3 > 79 && distance3 < 100){
//    state3 = LOW;
//    Serial.println("0%");
//  }
}
