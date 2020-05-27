#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);

int relayPin = 7;                // choose the pin for the Relay Pin

int inputPin = 13;               // choose the input pin (for PIR sensor)
int inputPin2 = 9;               // choose the input pin (for PIR sensor 02)
const int relay = 7;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int val2 = 0;                    // variable for reading the pin status
const unsigned long interval = 7000;           // interval at which to blink (milliseconds)

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
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);      // declare Relay as output
  pinMode(relay2, OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT);  
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
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("ROBOTICS--CENTER");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.setCursor(0, 2);
  lcd.print("ChemLevel: ");
  lcd.setCursor(0, 3);
  lcd.print("Duration: ");
  ambuttonState = digitalRead(amButton);
  if(ambuttonState == HIGH){
    val = digitalRead(inputPin);  // read input value
    val2 = digitalRead(inputPin2);  // read input value
    if (val == HIGH && pirState == LOW) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      Serial.println("Motion detected!");
      pirState = HIGH;
      delay(1000);
    }
    else{
      if(val2 == HIGH && pirState == HIGH){
        digitalWrite(buzzer, LOW);
        digitalWrite(relay, LOW);
        digitalWrite(relay2, LOW);
        Serial.println("Motion ended!");
        pirState = LOW;
        delay(100);
      }
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
