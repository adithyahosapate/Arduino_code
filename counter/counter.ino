int a,b,c,d,e,f,g;
int A,B,C,D;
void setup()
{
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
 Serial.begin(9600);      // open the serial port at 9600 bps:    
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);

  
  
  
}
int led=8;
void loop()
{
 
   digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // 
  A=digitalRead(9);
  B=digitalRead(10);
  C=digitalRead(11);
  D=digitalRead(12);
  Serial.print(A);
  Serial.print(B);
  Serial.print(C);
  Serial.print(D);

  a = (!A && B && !C && !D) || (!A && !B && !C && D) || (A && B && C && !D) || (A && !B && C && D);
b = (!A && B && !C && D) || (!A && B && C && !D) || (A && B && !C && !D) || (A && B && C && D);
c = (!A && !B && C && !D);
d = (!B && !C && D) || (!A && B && !C && !D) || (A && !B && D) || (!A && B && C && D) || (A && B && C && !D);
e = (D) | (!A && B && !C) || (A && B && C);
f = (!B && C) || (!A && B && D) || (D && !A && !B) || (!C && A && B);
g = (A && B  && C && D) || (!A && !B && !C) || (A && !B && C);
 digitalWrite(1,a);
 digitalWrite(2,b);
 digitalWrite(3,c);
 digitalWrite(4,d);
 digitalWrite(5,e);
 digitalWrite(6,f);
 digitalWrite(7,g);

    




 
}







