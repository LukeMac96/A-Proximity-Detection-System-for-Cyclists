
#include <IRsensor.h>
#include <Arduino.h>
#include <voltage>
#include <distance>

int _IRpin;
int IRdistance;
extern float voltage[];
extern float distance[];

IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

int IRsensor::readIR(){

    float v  = analogRead(_IRpin);
    v = v/1024.0*5;

    




    return IRdistance;
}