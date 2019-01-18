#include <Arduino.h>

//Dual sensor Code.
//12/01/2019.

const int irsense = A0;
int IRdistance =0;

const int trigPin =9;
const int echoPin =10;
int USdistance =0;
long duration =  pulseIn(echoPin, HIGH);


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  
}

void loop() {

//USRead() -- was not declared in this scope
  USRead();
  delay(2);
//irread() -- was not declared in this scope

  irread();

  delay(3000);
}



