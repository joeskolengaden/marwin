//code is still in testing mode



#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Replace the next variables with your SSID/Password combination
 char* ssid = "motify_one";
 char* password = "trigon2016";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.43.236";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


int mq2_pin =34;
int mq3_pin =35;
int mq4_pin =32;
int mq5_pin =33;
int mq6_pin =25;
int mq7_pin =26;
int mq8_pin =27;
int mq9_pin =14;
int mq135_pin =12;

int mq2_value=0;
int mq3_value=0;
int mq4_value=0;
int mq5_value=0;
int mq6_value=0;
int mq7_value=0;
int mq8_value=0;
int mq9_value=0;
int mq135_value=0;

void setup() {
  Serial.begin(115200);//sets the baud rate
    setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


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
    
  
  mq2_value= analogRead(mq2_pin);
  mq3_value= analogRead(mq3_pin);
  mq4_value= analogRead(mq4_pin);
  mq5_value= analogRead(mq5_pin);
  mq6_value= analogRead(mq6_pin);
  mq7_value= analogRead(mq7_pin);
  mq8_value= analogRead(mq8_pin);
  mq9_value= analogRead(mq9_pin);
  mq135_value= analogRead(mq135_pin);

  Serial.print("  mq2:");
  Serial.print(mq2_value);
  Serial.print("  mq3:");
  Serial.print(mq3_value);
  Serial.print("  mq4:");
  Serial.print(mq4_value);
  Serial.print("  mq5:");
  Serial.print(mq5_value);
  Serial.print("  mq6:");
  Serial.print(mq6_value);
  Serial.print("  mq7:");
  Serial.print(mq7_value);
  Serial.print("  mq8:");
  Serial.print(mq8_value);
  Serial.print("  mq9:");
  Serial.print(mq9_value);
  Serial.print("  mq135:");
  Serial.println(mq135_value);

  
  char mq2String[8];
  char mq3String[8];
  char mq4String[8];
  char mq5String[8];
  char mq6String[8];
  char mq7String[8];
  char mq8String[8];
  char mq9String[8];
  char mq135String[8];
  
  dtostrf(mq2_value, 1, 2, mq2String);
  dtostrf(mq3_value, 1, 2, mq3String);
  dtostrf(mq4_value, 1, 2, mq4String);
  dtostrf(mq5_value, 1, 2, mq5String);
  dtostrf(mq6_value, 1, 2, mq6String);
  dtostrf(mq7_value, 1, 2, mq7String);
  dtostrf(mq8_value, 1, 2, mq8String);
  dtostrf(mq9_value, 1, 2, mq9String);
  dtostrf(mq135_value, 1, 2, mq135String);
    
  client.publish("esp32/mq2", mq2String);
  client.publish("esp32/mq3", mq3String);
  client.publish("esp32/mq4", mq4String);
  client.publish("esp32/mq5", mq5String);
  client.publish("esp32/mq6", mq6String);
  client.publish("esp32/mq7", mq7String);
  client.publish("esp32/mq8", mq8String);
  client.publish("esp32/mq9", mq9String);
  client.publish("esp32/mq135", mq135String);
  delay(200);
  
}
}
