//ultrasonic sensor one
const int trigPin3 = 4;    // Trigger
const int echoPin3 = 3;    // Echo
int distance3;
float duration3;
int state3;
int percentage;
int pot,pot_map;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT); 
}

void loop() {
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;
  Serial.println(distance3);
  pot = analogRead(A0);
  pot_map = map(pot,0,1023,0,240);
  if(distance3>0 && distance3<240 && pot_map>=distance3){
    percentage = map(distance3,0,pot_map,100,0);
    Serial.print("percentage ");
    Serial.println(percentage);
  }
  else{
    Serial.println("Container Max-Height Exceeded");
    percentage = 0;
  }
//  delay(500);
}
