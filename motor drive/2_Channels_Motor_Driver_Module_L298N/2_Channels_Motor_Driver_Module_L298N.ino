/************************************************
Editor   : MYBOTIC www.mybotic.com.my
Date     : 29 Aug 2014
Project  : 2 Channels Motor Driver Module
*************************************************/

//define motor 1 related pins
#define IN1 9
#define IN2 8
#define ENA 10

//define motor 2 related pins
#define IN3 7
#define IN4 6
#define ENB 5

void setup()
{ 
  //set output for motor 1 related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  //set output for motor 2 related pins
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  //set motor 1 run in clockwise
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  //set motor 2 run in anticlockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop()
{
  int PWM_Value = 0; //PWM value for motor 1 and 2
  
  //Motor 1 and Motor 2 run with gradually increasing speed until Max
  for(PWM_Value = 0; PWM_Value<=255; PWM_Value+=5)
  {
    analogWrite(ENA, PWM_Value); //set PWM to Motor 1
    analogWrite(ENB, PWM_Value); //set PWM to Motor 2
    delay(100);
  }
  
  //Motor 1 and Motor 2 run with gradually descreasing speed until Stop
  for(PWM_Value = 255; PWM_Value>=0; PWM_Value-=5)
  {
    analogWrite(ENA, PWM_Value); //set PWM to Motor 1
    analogWrite(ENB, PWM_Value); //set PWM to Motor 2
    delay(100);
  }
}
