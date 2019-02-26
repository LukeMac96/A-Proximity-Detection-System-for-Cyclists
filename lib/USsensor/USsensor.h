
#ifndef USsensor_h
#define USsensor_h

#include "Arduino.h"

class USsensor{

    public:
        USsensor(int trigpin, int echopin);
        //int Smoothing();
        
        float Tread();

    private:
        int _trigpin;
        int _echopin;
        float duration;
        float USdistance;

};
#endif
