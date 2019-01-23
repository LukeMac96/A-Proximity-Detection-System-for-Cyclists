
#include <IRsensor.h>
#include <Arduino.h>

int _IRpin;
int IRdistance;

IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

int IRsensor::readIR(){

    IRdistance = analogRead(_IRpin);



    return IRdistance;
}