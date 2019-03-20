
#include <IRsensor.h>
#include <Arduino.h>

//#include "/Users/luke/Downloads/Documents/PlatformIO/Projects/FYP/lib/IRsensor/distance.ino"
//#include <voltage.ino>


int _IRpin;
float IRdistance;
//extern float voltage[];
//extern float distance[];
float distance[] = {
    70,
    80,
    90,
    100,
    110,
    120,
    130,
    140,
    150,
    160,
    170,
    180,
    190,
    200,
    210,
    220,
    230,
    240,
    250,
    260,
    270,
    280,
    290,
    300,
    310,
    320,
    330,
    340,
    350,
    360,
    370,
    380,
    390,
    400,
    410,
    420,
    430,
    440,
    450,
    460,
    470,
    480,
    490,
    500,
    510,
    520,
    530,
    540,
    550
};

float voltage[] = {
    2.9345703125, 
    2.67578125, 
    2.548828125, 
    2.3486328125, 
    2.2216796875, 
    2.1337890625, 
    2.0751953125, 
    2.041015625, 
    2.01171875, 
    1.97265625, 
    1.923828125, 
    1.865234375, 
    1.8115234375, 
    1.767578125, 
    1.728515625, 
    1.7138671875, 
    1.6748046875, 
    1.66015625, 
    1.62109375, 
    1.6015625, 
    1.58203125, 
    1.5625, 
    1.5478515625, 
    1.5283203125, 
    1.5087890625, 
    1.4892578125, 
    1.484375, 
    1.4794921875, 
    1.474609375, 
    1.46484375, 
    1.4501953125, 
    1.4404296875, 
    1.42578125, 
    1.416015625, 
    1.40625, 
    1.396484375, 
    1.3916015625, 
    1.38671875, 
    1.376953125, 
    1.3720703125, 
    1.3623046875, 
    1.357421875, 
    1.3525390625, 
    1.34765625, 
    1.3427734375, 
    1.337890625, 
    1.3330078125, 
    1.318359375, 
    1.3134765625, 
};

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