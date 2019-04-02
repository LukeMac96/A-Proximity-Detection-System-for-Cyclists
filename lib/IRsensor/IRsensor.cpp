
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

RunningAverage IRBuffer(20);
RunningAverage PowBuffer(20);




IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

float IRsensor::formulaRead(){
    float Fdistance;

    for(int i=0;i<20;i++){
        
        float read = analogRead(_IRpin);
        delayMicroseconds(200);
        IRBuffer.addValue(read);

    }
    float x = IRBuffer.getAverage();
    IRBuffer.clear();
    //float x = analogRead(_IRpin);

    float z = 10000.00;
    /*Equation Coefficients */
    float a = /*+*/ 0.00064;
    float b = /*-*/ 0.06628;
    float c = /*+*/ 2.2824;
    float d = /*-*/ 34.4338;
    float e = /*+*/ 558.604;
    /*X values    */
    float x4 = a*pow(x,4);
    float x3 = b*pow(x,3);
    float x2 = c*pow(x,2);
    
    float ax4 = (a*x4);
    float bx3 = (b*x3);
    float cx2 = (c*x2);
    float dx1 = (d*x);
  
    Fdistance = (x4-x3+x2-dx1+e)/z;
    //Fdistance = Fdistance/1000;
    return Fdistance;
    //y = 0.0007x4 - 0.074x3 + 2.5337x2 - 37.406x + 567.72

   // Fdistance = pow(a,x) -0.06628*x^3 +2.2824*x^2 -34.4338*x +558.604;
}

float IRsensor::POWRead(){
    float POWDistance;

    for(int i=0;i<20;i++){
        
        float read2 = analogRead(_IRpin);
        delayMicroseconds(200);
        PowBuffer.addValue(read2);

    }
    float x1 = PowBuffer.getAverage();
    PowBuffer.clear();

    float p = -0.199;
    float expow = pow(x1,p);
    POWDistance = 595.9*expow;

    return POWDistance;
}

float IRsensor::AreadIR(){
    IRdistance = analogRead(_IRpin);
    return IRdistance;
}

float IRsensor::readIR(){

    float v  = analogRead(_IRpin);
    v = v/1024.0*5.0;
    //int index = 0;

/* https://github.com/weifengdq/Sharp_GP2Y0A  */
    /*for(index = 0; index < 49; index++){
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
    }*/
    IRdistance = map(v, 0, 1024, 60, 550);

    return IRdistance;
}