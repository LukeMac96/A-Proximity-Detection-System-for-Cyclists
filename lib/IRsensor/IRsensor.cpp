
#include <IRsensor.h>
#include <Arduino.h>

#include "/Users/luke/Downloads/Documents/PlatformIO/Projects/FYP/lib/IRsensor/distance.ino"
#include <voltage.ino>


int _IRpin;
float IRdistance;
extern float voltage[];
extern float distance[];

IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

float IRsensor::AreadIR(){
    IRdistance = analogRead(_IRpin);
    return IRdistance;
}

float IRsensor::readIR(){

    float v  = analogRead(_IRpin);
    v = v/1024.0*5;
    int index = 0;

/* https://github.com/weifengdq/Sharp_GP2Y0A  */
    for(index = 0; index < 49; index++){
        if(v >= voltage[index]){ 
            break;
        }
    }
    if(index == 0){
        IRdistance = 70.0;
    }else if(index == 49){
        IRdistance = 550.0;
    }else 
    {
        IRdistance = map(v, voltage[index], voltage[index -1], distance[index], distance[index -1]);
    }

    return IRdistance;
}