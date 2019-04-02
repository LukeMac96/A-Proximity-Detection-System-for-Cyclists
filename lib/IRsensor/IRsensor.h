
#ifndef IRsensor_h
#define IRsensor_h

#include "Arduino.h"

class IRsensor{

    public:
        IRsensor(int IRpin);
        float readIR();
        float AreadIR();
        float formulaRead();
        float POWRead();

    private:
        int _IRpin;
        float IRdistance;
        
};
#endif