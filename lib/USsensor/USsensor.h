
#ifndef USsensor_h
#define Ussensor_h

#include "Arduino.h"

class USsensor{

    public:
        USsensor(int trigpin, int echopin);
        void Trigger();
        int USread();

    private:
        int _trigpin;
        int _echopin;
        int duration;
        int USdistance;


        




};
#endif
