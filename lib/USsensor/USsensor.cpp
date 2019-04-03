#include <Arduino.h>
#include <USsensor.h>

int _trigpin;
int _echopin;
float duration;
float USdistance;

USsensor::USsensor(int trigpin, int echopin){

    pinMode(trigpin, OUTPUT);
    pinMode(echopin, INPUT);
    _trigpin = trigpin;
    _echopin = echopin;

}
void Trigger(){

    digitalWrite(_trigpin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigpin, LOW);
}

float USsensor::Tread()
{
    
    digitalWrite(_trigpin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigpin, LOW);
    delayMicroseconds(200);
    duration = pulseIn(_echopin, HIGH);
    USdistance = duration*0.034/2;

    if(USdistance > 3000){
        Trigger();
        delayMicroseconds(200);
        duration = pulseIn(_echopin, HIGH);
        USdistance = duration*0.034/2;
    }

    return USdistance;
}






