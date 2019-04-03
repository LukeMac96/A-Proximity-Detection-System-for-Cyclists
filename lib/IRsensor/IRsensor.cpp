
#include <IRsensor.h>
#include <Arduino.h>
#include <math.h>
#include <RunningAverage.h>

//#include "/Users/luke/Downloads/Documents/PlatformIO/Projects/FYP/lib/IRsensor/distance.ino"
//#include <voltage.ino>


int _IRpin;
float IRdistance;
//extern float voltage[];
//extern float distance[];

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

    //float z = 10000.00;
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
    //y = 0.0007x4 - 0.074x3 + 2.5337x2 - 37.406x + 567.72

   // Fdistance = pow(a,x) -0.06628*x^3 +2.2824*x^2 -34.4338*x +558.604;
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

    //Run1  y = 550.72x-0.152
    //Run2  y = 540.74x-0.145
    //Run3  y = 550.45x-0.153
    //Run4  

    float p = -0.15;
    float expow = pow(x1,p);
    POWDistance = 547*expow;


    return POWDistance;
}

float IRsensor::AreadIR(){
    IRdistance = analogRead(_IRpin);
    return IRdistance;
}