#include <Arduino.h>

const int irsense = A0;
int IRdistance =0;

const int trigPin =9;
const int echoPin =10;
int USdistance =0;
long duration;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  USdistance = (usread());


}

int usread(){
  int averaging

}