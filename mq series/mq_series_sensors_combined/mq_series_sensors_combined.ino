//code is still in testing mode

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
  

}

void loop() {
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
delay(500);
  
}
