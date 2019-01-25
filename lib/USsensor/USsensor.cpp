#include <Arduino.h>
#include <USsensor.h>

int _trigpin;
int _echopin;
int duration;
int USdistance;

//Variables for Smoothing Buffer
const int BuffSize = 10;
int Buff1[BuffSize];
int Index;
int total;
int average;

//Flag variables
volatile bool B1flag = false;



USsensor::USsensor(int trigpin, int echopin){

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
    _trigpin = trigpin;
    _echopin = echopin;

};

int USsensor::Smoothing()
{
    for(int i=0; i<BuffSize; i++)
    {
        //subtract last read
        total = total - Buff1[Index];
        //read from sensor
        Buff1[Index] = Tread();
        //Add reading to total
        total = total + Buff1[Index];
        Index = Index + 1;

    }

    average = total/BuffSize;
    B1flag = true;

    return average;
    
}




int USsensor::Tread()
{
    digitalWrite(_trigpin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigpin, LOW);
    
    duration = pulseIn(_echopin, HIGH);
    USdistance = duration*0.034/2;

    return USdistance;
}



