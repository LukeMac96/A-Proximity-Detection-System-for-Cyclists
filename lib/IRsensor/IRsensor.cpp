
#include <IRsensor.h>
#include <Arduino.h>
#include <math.h>
#include <RunningAverage.h>


int _IRpin;
float IRdistance;
RunningAverage IRBuffer(10);
RunningAverage PowBuffer(10);

IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

float IRsensor::formulaRead(){
    float Fdistance;

    for(int i=0;i<10;i++){
        
        float read = analogRead(_IRpin);
        delayMicroseconds(200);
        IRBuffer.addValue(read);
    }
    float x = IRBuffer.getAverage();
    IRBuffer.clear();
   

    //y = 0.0004x4 - 0.0417x3 + 1.6143x2 - 28.393x + 546.19

    /*Equation Coefficients */
    float a = /*+*/ 0.0004;
    float b = /*-*/ 0.0417;
    float c = /*+*/ 1.6143;
    float d = /*-*/ 28.393;
    float e = /*+*/ 546.19;
    /*X values    */
    float x4 = a*pow(x,4);
    float x3 = b*pow(x,3);
    float x2 = c*pow(x,2);
    float x1 = (d*x);
  
    Fdistance = (x4-x3+x2-x1+e);
    
    return Fdistance;
}

float IRsensor::POWRead(){
    float POWDistance;

    for(int i=0;i<5;i++){
        
        float read2 = analogRead(_IRpin);
        delayMicroseconds(200);
        PowBuffer.addValue(read2);
    }
    float x1 = PowBuffer.getAverage();
    PowBuffer.clear();
        /*
        Run 1 y = 550.72x^-0.152
        Run 2 y = 540.74x^-0.145   
        Run 3 y = 550.45x^-0.153
        Run 4 y= 534.32 x^-0.136
        Run 5 y= 542.1 x^-0.147
        Run 6 y= 542.85 x^-0.147
        Run 7 y= 550.13 x^-0.154
        Run 8 y= 550.13 x^-0.154
        Run 9 y= 543.50 x^ -0.15
        Run 10 y= 569.58 x^-0.157
        */
    float p = -0.15;
    float expow = pow(x1,p);
    POWDistance = 547*expow;

    return POWDistance;
}

float IRsensor::AreadIR(){
    IRdistance = analogRead(_IRpin);
    return IRdistance;
}