#include <Servo.h>     
Servo mg90;
Servo mg90e;          
int initial_position = 90; 
int initial_positione = 90;  
int LDR1 = A0; 
int LDR2 = A1; 
int LDR3 = A2;
int LDR4 = A3;         
int error = 50;          //Maximum difference threshold
int servopin=3;
int servopine=11;
void setup() 
{   
  mg90.attach(servopin);
  mg90e.attach(servopine);
  pinMode(LDR1, INPUT);  
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);
  mg90.write(initial_position);
  mg90e.write(initial_positione);
  delay(20);            
}  
 
void loop() 
{ 
  int R1 = analogRead(LDR1); 
  int R2 = analogRead(LDR2); 
  int R3 = analogRead(LDR3);
  int R4 = analogRead(LDR4);
  int diff1= abs(R1 - R2); 
  int diff3= abs(R3 - R4);
  //Limiting servo movement to 45 degree along both sides otherwise move by 1 deg after each iterations
  if (diff1 > error) 
  {    
    if(R1 > R2)
    { 
      initial_position = initial_position+1;
      if(initial_position > 135)
      {
        initial_position = 135;
      }
    }
    else
    {
     
      initial_position = initial_position-1;
      if(initial_position <45)
      {
        initial_position = 45;
      }
    }
   }
  mg90.write(initial_position); // write the position to servo
  delay(10);
 
   if(diff3 > error)
  {    
    if(R4 > R3)
    {
      initial_positione = initial_positione-1;
      if(initial_positione < 45)
      {
        initial_positione = 45;
      }
    }
   else 
    {
      initial_positione = initial_positione+1;
      if(initial_positione >135)
      {
        initial_positione = 135;
      }
    }
     
  }
  mg90e.write(initial_positione); // write the position to servo
  delay(10);
  
}