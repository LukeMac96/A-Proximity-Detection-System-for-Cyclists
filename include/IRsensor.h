
#ifndef include.IRsensor_h
#define IRsensor_h

#include "Arduino.h"

class IRsensor{

    public:
        IRsensor(int IRpin);
        int readIR();

    private:
        int _IRpin;
        int IRdistance;
        
};
#endif