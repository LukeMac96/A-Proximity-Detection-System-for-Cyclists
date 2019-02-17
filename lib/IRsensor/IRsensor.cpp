
#include <IRsensor.h>
#include <Arduino.h>
#include <voltage>
#include <distance>

int _IRpin;
int IRdistance;
extern float voltage[];
extern float distance[];

IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

int IRsensor::readIR(){

    float v  = analogRead(_IRpin);
    v = v/1024.0*5;
    int index = 0;

    for(index=0; index<49;index++){
        if(v>=voltage[index]){
            break;
        }
    }
    if(index==0){
        IRdistance = 70;
    }else if(index == 49){
        IRdistance = 550;
    }else{
        IRdistance = map(v, voltage[index], voltage[index -1], distance[index], distance[index -1]);
    
    }

    




    return IRdistance;
}