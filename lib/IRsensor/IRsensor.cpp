
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




IRsensor::IRsensor(int IRpin){

    pinMode(IRpin, INPUT);
    _IRpin = IRpin;

};

float IRsensor::formulaRead(){
    float Fdistance;
    float read = analogRead(_IRpin);

    for(int i=0;i<20;i++){
       
        IRBuffer.addValue(read);

    }
    float x = IRBuffer.getAverage();
    IRBuffer.clear();

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
    float x1 = d*pow(x,1);

    Fdistance = ((x4)-(x3)+(x2)-(x1)-e)/100000;
    

    return Fdistance;
   // Fdistance = pow(a,x) -0.06628*x^3 +2.2824*x^2 -34.4338*x +558.604;
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