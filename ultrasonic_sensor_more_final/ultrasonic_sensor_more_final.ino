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
const unsigned long interval = 1000;           // interval at which to blink (milliseconds)
unsigned long previousMillis;
unsigned long distanceMillis;
bool Flag1 = false;
bool Flag2 = false;

// Buttons and state
#define amButton 5;
#define ssButton 4;
#define ambuttonState LOW;
#define ssbuttonState LOW;
// Lights
int light = 3;
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
  pinMode(light, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
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
    Serial.println("Relay on");
    previousMillis = millis();
  }
  else if(distance > 100){
    Flag1 = false;
    digitalWrite(buzzer, Flag1);
  }
  if (distance <= 100)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 5000)
    {
      Flag1 = false;
      Serial.println("Relay off");
      digitalWrite(buzzer, Flag1);
      previousMillis = currentMillis;
      delay(3000);
      while(distance2 > 0 && distance2 < 100 && Flag1 == false){
        Serial.println(distance2);
        Serial.println("Error leave the tunnel");
        getDistance2();
        delay(200);
      }
    }
  }
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

//  Serial.print("Distance 2: ");
  Serial.println(distance2);
}
