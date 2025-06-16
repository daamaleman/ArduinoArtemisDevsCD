#include<iostream>
using namespace std;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  Serial.write("LED ON\n");
  delay(2000);
  

  digitalWrite(13, LOW);
  Serial.write("LED OFF\n");
  delay(1000);
  
}
