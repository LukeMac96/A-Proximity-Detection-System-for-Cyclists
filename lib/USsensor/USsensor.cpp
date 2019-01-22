#include <Arduino.h>
#include <USsensor.h>

int _trigpin;
int _echopin;
int duration;
//int USdistance;

USsensor::USsensor(int trigpin, int echopin){

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
    _trigpin = trigpin;
    _echopin = echopin;

};


void USsensor::Trigger()
{
    digitalWrite(_trigpin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigpin, HIGH);
    delayMicroseconds(10);

    digitalWrite(_trigpin, LOW);
    
}

int USsensor::USread()
{
    duration = pulseIn(_echopin, HIGH);
    USdistance = duration*0.034/2;

    return USdistance;

}



