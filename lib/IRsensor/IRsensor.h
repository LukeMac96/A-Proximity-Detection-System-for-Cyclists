
#ifndef IRsensor_h
#define IRsensor_h

#include "Arduino.h"

class IRsensor{

    public:
        IRsensor(int IRpin);
        float readIR();
        float AreadIR();
        double formulaRead();

    private:
        int _IRpin;
        float IRdistance;
        
};
#endif