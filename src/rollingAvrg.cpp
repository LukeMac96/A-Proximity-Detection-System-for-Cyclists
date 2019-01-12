#include <Arduino.h>

//Rolling Average Code.
//12/01/2019.
const int irsense = A0;

long duration;
float average = 0;

//numReadings defines the length of the array.
const int numReadings= 10;

float readings[numReadings];
int readIndex = 0;
float total = 0;


void setup() {
  
  Serial.begin(9600);

//Loop to initialise all readings to zero.
  for(int thisReading=0; thisReading< numReadings; thisReading++){
    readings[thisReading] =0;
  }
}

void loop() {

    total = total - readings[readIndex];

//Sensor read.
    readings[readIndex] = analogRead(irsense);
    total = total +readings[readIndex];
    readIndex = readIndex +1;

    //when it reaches the end of the array, loops back to the start.
  if(readIndex>= numReadings){
    readIndex =0;
  }

//Calculate Average
  average = total/numReadings;

  Serial.println(average);
    delay(1);

}