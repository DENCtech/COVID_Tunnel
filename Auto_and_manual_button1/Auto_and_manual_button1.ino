// Buttons and state
#define amButton 5
#define ssButton 4
int ambuttonState; // button state of the auto and manual button
int ssbuttonState; // button state of the start and stp manual button

void setup() {
  Serial.println(9600);
  pinMode(amButton, INPUT);
  pinMode(ssButton, INPUT);

}

void loop() {
  ambuttonState = digitalRead(amButton);
  if(ambuttonState == HIGH){
    
  }
  else{
    ssbuttonState = digitalRead(ssButton);
    if(ssbuttonState == HIGH){
      
    }
    else{
      
    }
  }
}
