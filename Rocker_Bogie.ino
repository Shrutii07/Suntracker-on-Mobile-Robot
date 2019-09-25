  
#define STX 0x02                                
#define ETX 0x03                                
int bt[8]={0,0,0,0,0,0,0,0};                    // Output from joystick in format 'STX'xxxyyy'ETX'
int X,Y,left,right,i,leftspeed,rightspeed;
/*
 * in1 and in2, in3 and in4 are input pins for motor driver L298N for LHS and RHS motors
 * en1 and en2 are for enable pins of L298N for controlling rpm for LHS and RHS motors respectively
 */
#define BTstate 4
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define en1 10
#define en2 5
void setup() 
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(BTstate, INPUT);
}

void loop()
{
  /*
   * First check if bluetooth connection is avaliable.
   * Then, Seperate the coordinates X,Y sent by bluetooth joystick into variables X and Y respectively for later use.
   * Format sent by Joystick app used is 'STX'xxxyyy'ETX
   */
 if(Serial.available())  
 {         
  if(digitalRead(BTstate=='1'))  
   {                
   delay(2);
   bt[0] =  Serial.read();  
   if(bt[0] == STX) 
   {
     i=1;      
     while(Serial.available())
     {
       delay(1);
       bt[i] = Serial.read();
       if(bt[i]>127 || i>7)     
       break;   
       if((bt[i]==ETX) && (i==2 || i==7))  
       break;
       i++;
     }
   }
     X = (bt[1]-48)*100 + (bt[2]-48)*10 + (bt[3]-48);  
     Y = (bt[4]-48)*100 + (bt[5]-48)*10 + (bt[6]-48);
   X = X - 200;                                       
   Y = Y - 200;                                      //For some reason x and y cordinate sent by joystick is 200 more than expected... so to correct the error             
   }
   else
    {X = Y = 0;}
   //Using X and Y obtained to control left-hand side and right-hand side motor's direction and rpm.
   //Detailed explanation in Readme.md
   if (Y>=0)
       { 
        left = Y+X;
        right = Y-X;
       }
   else 
       {
        left=Y-X;
        right=Y+X;
       }
   if(left >= 95) left = 95;
   else if(left <= -95) left = -95;
   if(right >= 95) right = 95;
   else if(right <= -95) right = -95; 
   if(left<0)
  {  
    leftspeed = map (left, 0, -95, 0, 255);
    analogWrite(en1, leftspeed); 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else if (left>0)
  {
    leftspeed = map(left,0,95,0,255);
    analogWrite(en1, leftspeed); 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  {
    leftspeed =0; //stop
    analogWrite(en1, leftspeed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  
  }
  if (right<0)
  {  
    rightspeed = map (right, 0,-95, 0, 255);
    analogWrite(en2, rightspeed); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (right>0)
  {
    rightspeed = map(right,0,95,0,255);
    analogWrite(en2, rightspeed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }  
    else
  {
    rightspeed =0; //stop
    analogWrite(en2, rightspeed);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);  
  }
 }
}