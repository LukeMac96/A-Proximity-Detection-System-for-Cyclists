#include <Arduino.h>
#include <USsensor.h>


//Dual sensor Code.
//12/01/2019.

const int irsense = A0;
int IRdistance =0;

//const int trigPin =9;
//const int echoPin =10;

USsensor US1(10, 2);     //Instantiate USsensor class, define pin numbers.


int USdistance =0;
//long duration =  pulseIn(echoPin, HIGH);


void setup() {
  //pinMode(trigPin, OUTPUT);     pinMode() call happens inside library USsensor.cpp
  //pinMode(echoPin, INPUT);

  Serial.begin(9600);
}


void loop() {

  US1.Trigger();   //Call function to trigger US pin 9.
  US1.USread();     //Call function to Read value from US, pin 10.    

}


