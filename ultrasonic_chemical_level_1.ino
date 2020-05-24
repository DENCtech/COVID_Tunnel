//ultrasonic sensor one
const int trigPin = 13;    // Trigger
const int echoPin = 12;    // Echo
//const int relay = 7;
int distance;
float duration;
int state;

void setup() {
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  getDistance();
  if(distance > 0 && distance < 20){
    state = HIGH;
    Serial.println("100%");
  }
  if(distance > 19 && distance < 40){
    state = HIGH;
    Serial.println("100%");
  }
  if(distance > 39 && distance < 60){
    state = HIGH;
    Serial.println("60%");
  }
  if(distance > 59 && distance < 80){
    state = HIGH;
    Serial.println("20%");
  }
  if(distance > 79 && distance < 100){
    state = LOW;
    Serial.println("0%");
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
