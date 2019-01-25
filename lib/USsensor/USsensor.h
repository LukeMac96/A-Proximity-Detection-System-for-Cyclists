
#ifndef USsensor_h
#define USsensor_h

#include "Arduino.h"

class USsensor{

    public:
        USsensor(int trigpin, int echopin);
        void Trigger();
        int USread();
        int Tread();

    private:
        int _trigpin;
        int _echopin;
        int duration;
        int USdistance;

};
#endif
