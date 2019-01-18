#include <Arduino.h>
#include <USsensor.h>

int Tpin;
int Epin;
int duration;
int USdistance;

USsensor::USsensor(int trigpin, int echopin){

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
    Tpin = trigpin;
    Epin = echopin;

};


void USsensor::Trigger()
{
    digitalWrite(Tpin, LOW);
    delayMicroseconds(2);

    digitalWrite(Tpin, HIGH);
    delayMicroseconds(10);

    digitalWrite(Tpin, LOW);
    
}

int USsensor::USread()
{
    duration = pulseIn(Epin, HIGH);
    USdistance = duration*0.034/2;

    return USdistance;

}



