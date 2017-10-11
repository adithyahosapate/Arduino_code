int hours,minutes,seconds;
int num_array[10][7] = { { 0,0,0,0,0,0,1},    // 0
                         { 1,0,0,1,1,1,1},    // 1
                         { 0,0,1,0,0,1,0},    // 2
                         { 0,0,0,0,1,1,0},    // 3
                         { 1,0,0,1,1,0,0},    // 4
                         { 0,1,0,0,1,0,0},    // 5
                         { 0,1,0,0,0,0,0},    // 6
                         { 0,0,0,1,1,1,1},    // 7
                         { 0,0,0,0,0,0,0},    // 8
                         { 0,0,0,1,1,0,0}};   // 9
                                       
void Num_Write(int a);
void setup() 
{ 
// set pin modes
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  

}
int list[6];
void loop() 
{
 for (hours=0;hours<24;hours++)
{
  for (minutes=0;minutes<60;minutes++)
  {
    for (seconds=0;seconds<60;seconds++)
    {
      list[0]=hours/10;list[1]=hours%10;list[2]=minutes/10;list[3]=minutes%10;list[4]=seconds/10;
      list[5]=seconds%10;
      
      display_time(list);
      
    }
  }
}  
}

void display_time(int *digit)
{
 for(int i=0;i<83;i++)
{
  for(int digit_i=8;digit_i<14;digit_i++)
  {
      digitalWrite(digit_i,1);
      Num_Write(digit[digit_i-8]);
            delay(2);

      digitalWrite(digit_i,0);


  }
} 
}
void Num_Write(int number) 
{
  int pin= 1;
  for (int j=0; j < 7; j++) {
   digitalWrite(pin++, num_array[number][j]);
   
  }
}
   
