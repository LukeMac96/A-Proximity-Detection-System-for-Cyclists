#include <Arduino.h>
#include <IRsensor.h>
#include <USsensor.h>
#include <RunningAverage.h>

/*Project Library Main
Luke MacRedmond
L.MACREDMOND1@nuigalway.ie
Date of last modification:    15/02/2019.
*/


//Pin Layout
//const int irsense = A0;
//const int trigPin =3;
//const int echoPin =2;
const int AudioWarningPin = 6;

//Running Average Library, used for Buffer implementation.
RunningAverage myRA_a(10);
RunningAverage myRA_b(10);
RunningAverage myRA_a1(10);
RunningAverage myRA_b1(10);
uint32_t samples = 0;
uint32_t samples2 = 0;
 
USsensor US1(11, 12);     //Instantiate USsensor class, define pin numbers.
IRsensor IR1(A0);       //Instantiate IRsensor class, define pin numbers.

//Flag determines which RunningAverage queue to store readings in.
volatile bool ReadSensorsFlag;
//Sets Digital pin 2 to trigger specific ISR on a HIGH value.
const int WarningInterruptpin = 2; 

//Floats for Average Distance value for both US & IR.
float AvrUS; 
float AvrIR;
//Defines Warning Threshold for warning the User.
static float Threshold;
//Variables for ensuring noise spikes dont trigger warning.
float ThresRange; //Calculated as a fraction of Threshold value???
float ThresCheckup = Threshold + ThresRange;
float ThresCheckdn = Threshold - ThresRange;



void UserWarning(){
  noInterrupts();
  //Method to warn user.
  //ISR for Digital Pin 2.
  digitalWrite(AudioWarningPin, HIGH);
}

//Method called from Setup(), prompts user to define Distance Thrshold.
void SetValues(){
  Serial.println("Input a Threshold range");
  Threshold = Serial.read();
  Serial.print("Distance Threshold set to:  ");
  Serial.print(Threshold);
  Serial.println("CM.");
  ReadSensorsFlag = true;
}





void FirstQueue(){

  myRA_a.addValue(US1.Tread());
  myRA_b.addValue(IR1.readIR());
  samples++;

  if(samples >= 20){
    samples = 0;
    myRA_a.clear();
    myRA_b.clear();

    ReadSensorsFlag = false;
  }

}
void SecondQueue(){

  myRA_a1.addValue(US1.Tread());
  myRA_b1.addValue(IR1.readIR());
  samples2++;

  if (samples2 >= 20){
    samples2 = 0;
    myRA_a1.clear();
    myRA_b1.clear();

    ReadSensorsFlag = true;
  }

}




//-----------------------------Setup & Loop-------------------------------------------------------
void setup() {
  //Interrupt Service Routine 'UserWarning' attached to pin 2, triggers when pin is set High
  pinMode(WarningInterruptpin, OUTPUT);
  digitalWrite(WarningInterruptpin, LOW);
  attachInterrupt(digitalPinToInterrupt(2), UserWarning ,HIGH);
  SetValues();
  
  Serial.begin(9600);
  myRA_a.clear();
  myRA_b.clear();
  myRA_a1.clear();
  myRA_b1.clear();

//-----------------------------------Setup() END.
}

void loop() 
{

  if(AvrIR > Threshold || AvrUS > Threshold){
    //Get Time
    //If values are greater than Threshold for more than X amount of time trigger the ISR.
    //for loop?
    digitalWrite(WarningInterruptpin, HIGH);
  }




  if(ReadSensorsFlag == true){
    AvrUS = myRA_a1.getAverage();
    AvrIR  = myRA_b1.getAverage();
    FirstQueue(); 
  }
  else{
    AvrUS = myRA_a.getAverage();
    AvrIR  = myRA_b.getAverage();
    SecondQueue();
  }






//-----------------------------------Loop() END.
}