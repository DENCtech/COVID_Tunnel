//ultrasonic sensor one
const int trigPin3 = 13;    // Trigger
const int echoPin3 = 12;    // Echo
//const int relay = 7;
int distance3;
float duration3;
int state3;
int var2 = A1; // Level changer variable resistor

void setup() {
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

}

void loop() {
  getDistance3();
  int val1 = analogRead(var2);
  int var = map(val1,0,1023,0,100);
  if(distance3 > 0 && distance3 < 20){
    state3 = HIGH;
    Serial.println("100%");
  }
  if(distance3 > 19 && distance3 < 40){
    state3 = HIGH;
    Serial.println("100%");
  }
  if(distance3 > 39 && distance3 < 60){
    state3 = HIGH;
    Serial.println("60%");
  }
  if(distance3 > 59 && distance3 < 80){
    state3 = HIGH;
    Serial.println("20%");
  }
  if(distance3 > 79 && distance3 < 100){
    state3 = LOW;
    Serial.println("0%");
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
