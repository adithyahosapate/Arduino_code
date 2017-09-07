#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define buzzer  6// Onboard LED
long duration, distance;
int led = 2;
int led1 =3;
int state;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
    pinMode(led1, OUTPUT);
    pinMode(4, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(buzzer, OUTPUT); 
}

void loop() {
  
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
//if (distance>1)
 // Serial.println(distance);
digitalWrite(4,HIGH);

  
  if(Serial.available() > 0){     
      state = Serial.read();}

  if (state == 49) {
      digitalWrite(led, HIGH);}   // turn the LED on (HIGH is the voltage level)
 
  else if (state == 50) {
      digitalWrite(led, LOW);}    // turn the LED off by making the voltage LOW

        if (state == 51) {
      digitalWrite(led1, HIGH);}   // turn the LED on (HIGH is the voltage level)
 
  else if (state == 52) {
      digitalWrite(led1, LOW);}    // turn the LED off by making the voltage LOW
      
  delay(100);               // wait for 100ms
  
Serial.println(state);
}
