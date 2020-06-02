#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);

int relayPin = 7;                // choose the pin for the Relay Pin

int inputPin = 11;               // choose the input pin (for PIR sensor)
int inputPin2 = 9;               // choose the input pin (for PIR sensor 02)
const int relay = 7;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int val2 = 0;                    // variable for reading the pin status
const unsigned long minInterval = 4000;           // interval at which to blink (milliseconds)
const unsigned long maxInterval = 10000;           // interval at which to blink (milliseconds)

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
const int trigPin3 = 4;    // Trigger
const int echoPin3 = 3;    // Echo
int distance3;
float duration3;
int state3;
int percentage;
int pot,pot_map;
int val4,val5;
float val6;
char float_str[8];


void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);      // declare Relay as output
  pinMode(relay2, OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT); 
  pinMode(amButton, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(ssButton, INPUT); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(buzzer, LOW);
  
  Serial.begin(9600);
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ROBOTICS--CENTER");
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.setCursor(-4, 2);
  lcd.print("ChemLevel: ");
  lcd.setCursor(-4, 3);
  lcd.print("Duration: ");
  delay(1000);
}

void loop() {
  chemLevel();
  ambuttonState = digitalRead(amButton);
  if(ambuttonState == HIGH){
    lcd.setCursor(7, 1);
    lcd.print("      ");
    lcd.setCursor(7, 1);
    lcd.print("AUTO");
    val = digitalRead(inputPin);  // read input value
    val2 = digitalRead(inputPin2);  // read input value
    val4 = analogRead(var2);
    val5 = map(val4,0,1023,minInterval,maxInterval);
    val6 = val5/1000;
    Serial.println(val6);
    dtostrf(val6,4,2,float_str);
    
    lcd.setCursor(7, 3);
    lcd.print("      ");
    lcd.setCursor(7, 3);
    lcd.print(val6);
    lcd.print("sec");
    if (val == HIGH && percentage < 11) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
      delay(val6);
      
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
    if(ssbuttonState == HIGH && percentage < 11){
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(relay2, HIGH);
    }
    else{
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
      digitalWrite(relay2, LOW);
      delay(800);
    }
  }
}
void chemLevel(){
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  pot = analogRead(A0);
  pot_map = map(pot,0,1023,0,240);
  if(distance3>0 && distance3<240 && pot_map>=distance3){
    percentage = map(distance3,0,pot_map,100,0);
    lcd.setCursor(7, 2);
    lcd.print("      ");
    lcd.setCursor(7, 2);
    lcd.print(percentage);
    lcd.print("%");
  }
  else{
    Serial.println("Container Max-Height Exceeded");
    percentage = 0;
    lcd.setCursor(7, 2);
    lcd.print("      ");
    lcd.setCursor(7, 2);
    lcd.print(percentage);
  }
}
