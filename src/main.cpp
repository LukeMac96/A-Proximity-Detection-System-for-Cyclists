#include <Arduino.h>
#include <USsensor.h>
#include <IRsensor.h>



//Project Library Main
//23/01/2019.

//Pin Layout
//const int irsense = A0;
//const int trigPin =3;
//const int echoPin =2;

USsensor US1(3, 2);     //Instantiate USsensor class, define pin numbers.
IRsensor IR1(A0);       //Instantiate IRsensor class, define pin numbers.


//int USdistance =0;
//long duration =  pulseIn(echoPin, HIGH);


void setup() {
  //pinMode(trigPin, OUTPUT);     pinMode() call happens inside library USsensor.cpp
  //pinMode(echoPin, INPUT);

  Serial.begin(9600);
}


void loop() {

  /*US1.Trigger();   //Call function to trigger US pin 3(Yellow).
  delayMicroseconds(500);
  US1.USread();     //Call function to Read value from US, pin 2(Blue).    
  delayMicroseconds(500);
  IR1.readIR();*/

  /*US1.Trigger();
  delayMicroseconds(10);
  Serial.print("US distance:  ");
  Serial.println(US1.USread());
  delayMicroseconds(2000);*/
  Serial.print("US distance:  ");
  Serial.println(US1.Tread());
  delayMicroseconds(200);

  Serial.print("IR distance:  ");
  Serial.println(IR1.readIR());
  delayMicroseconds(2000);
}


