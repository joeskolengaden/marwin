
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

/*
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
*/

// Replace the next variables with your SSID/Password combination
 char* ssid ="motify_one";
 char* password ="trigon2016";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.43.236";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

float left = 0;
float center = 0;
float right = 0;


int trigPin1=2;
int echoPin1=4;

int trigPin2=16;
int echoPin2=17;

int trigPin3=5;
int echoPin3=18;




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
int dutyCycle = 250;





void setup() {
  Serial.begin(115200);
  
//  SerialBT.begin("ESP32test"); //Bluetooth device name
//  Serial.println("The device started, now you can pair it with bluetooth!");
     
     
     setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
   pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
   pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
   
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






void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      //digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      //digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





void loop() {


 if (!client.connected()) {
    reconnect();
  }
  client.loop();

  
   long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
  
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
  
   if (distance1 >= 500 || distance1 <= 0){
    Serial.println("Out of range");
    right=distance1;
  }
  else {
    Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
    right=distance1;
    
  }
 //delay(200);
  
long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;
  
  
   if (distance2 >= 500 || distance2 <= 0){
    Serial.println("Out of range");
    center=distance2;
  }
  else {
    Serial.print("Sensor2  ");
    Serial.print(distance2);
    Serial.println("cm");
    center=distance2;
    
  }
  //delay(200);
  
  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= (duration3/2) / 29.1;

   if (distance3 >= 500 || distance3 <= 0){
    Serial.println("Out of range");
    left=distance3;
  }
  else {
    Serial.print("Sensor3  ");
    Serial.print(distance3);
    Serial.println("cm");
    left=distance3;
    
  }
  //delay(200);


                                                           //MOTOR DEIVER 
   if((right>75)&&(center>75)&&(left>75))
   {
   
    //This code will turn Motor forwards
    Serial.println("Going froward");
    
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    }
    
    else if((right<25)&(center<25)&(left>75)){
    //this code will turn rover right
    Serial.println("Turning right");

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    //ledcWrite(pwmChannel, dutyCycle);
    //ledcWrite(pwmChannel, dutyCycle);
   }

       else if((right>75)&(center<25)&(left<25)){
    //this code will turn rover left
    Serial.println("Turning left");

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    //ledcWrite(pwmChannel, dutyCycle);
    //ledcWrite(pwmChannel, dutyCycle);
   }
     else if((right<25)&(center<25)&(left<25)){
    //this code will turn rover backwards
    Serial.println("Going reverse");

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    //ledcWrite(pwmChannel, dutyCycle);
    //ledcWrite(pwmChannel, dutyCycle);
   }
   
   else if((right<75)||(center<75)||(left<75))
   {
    //this code will stop the rover 
    Serial.println("Stop");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    }

    ledcWrite(pwmChannel, dutyCycle);

    
  
  char leftString[8];
  char centerString[8];
  char rightString[8];

  dtostrf(left, 1, 2, leftString);
  dtostrf(center, 1, 2, centerString);
  dtostrf(right, 1, 2, rightString);
  
  client.publish("esp32_1/left", leftString);
  client.publish("esp32_1/center", centerString);
  client.publish("esp32_1/right", rightString);
  

  

}
}
