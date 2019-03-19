
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//L293D
//Motor L1
const int motorPin1  = 27;  // Pin 14 of L293
const int motorPin2  = 26;  // Pin 10 of L293
int enable1Pin = 14;

//Motor R1
const int motorPin3  = 32; // Pin  7 of L293
const int motorPin4  = 33;  // Pin  2 of L293
int enable2Pin = 25;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 160;


//This will run only one time.
void setup(){
  
  Serial.begin(115200);
  
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    
    pinMode(enable1Pin, OUTPUT);
    pinMode(enable2Pin, OUTPUT);

    // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);

}

void loop(){
  //Serial.println("2");
   if (SerialBT.available()) {
    char r=SerialBT.read();
    Serial.println(r);
    if(r=='a'){
   
    //This code will turn Motor forwards
    SerialBT.println("Going froward");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    }
    else if(r=='b'){
    //this code will turn rover backwards
    SerialBT.println("Going reverse");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    ledcWrite(pwmChannel, dutyCycle);
    //ledcWrite(pwmChannel, dutyCycle);
   }
   else if(r=='c')
   {
    //this code will stop the rover 
    SerialBT.println("Stop");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    }
    else if(r=='d')
   {
   dutyCycle=dutyCycle-10;
   SerialBT.println("dutyCycle");
   SerialBT.print(dutyCycle);
   }
   else if(r=='u')
   {
    dutyCycle=dutyCycle+10;
    SerialBT.println("dutyCycle");
    SerialBT.print(dutyCycle);
   }
   }
/*
    while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    if(dutyCycle>250)
    {dutyCycle=0;}
    
    delay(2000);
  }
  */
}
