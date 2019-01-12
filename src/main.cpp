#include <Arduino.h>

//Dual sensor Code.
//12/01/2019.

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


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  USdistance = (usread());
  IRdistance = irread();

}

int usread(){
  int averagingUS =0;
  
  //Loop for reading in values
  for(int j=0; j<5; j++){

    USdistance = (duration*0.034)/2;
    averagingUS = averagingUS+ USdistance;

  }
  USdistance= averagingUS/5;
  Serial.print("US Distance= ");
  Serial.print(USdistance);
  Serial.println("cm  ");
  delay(5);

}

int irread(){
  int averaging =0;
  int div = 10;
  //Loop for reading in values
  for(int i=0; i<10; i++){

    //Read voltage on IRsense, A0 pin
    IRdistance = analogRead(irsense);

    //Summing current reading with previous
    averaging= averaging + IRdistance;
    Serial.print("Reading: ");
    Serial.print(i);
    Serial.println("IR Distance");
    delayMicroseconds(3000);

  }
  //
  IRdistance = averaging/div;
  Serial.print("Average IR distance: ");
  Serial.println(IRdistance);
  delayMicroseconds(1000);

}