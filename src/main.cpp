#include <Arduino.h>
#include <IRsensor.h>
#include <USsensor.h>
#include <RunningAverage.h>

/*Project Library Main
Luke MacRedmond
L.MACREDMOND1@nuigalway.ie
Date of last modification:    17/02/2019.
*/


//Pin Layout
//const int irsense = A0;
//const int trigPin =11;
//const int echoPin =12;
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
  //Serial.println("Input a Threshold range");
  Threshold = 15;
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
  pinMode(AudioWarningPin, OUTPUT);
  digitalWrite(WarningInterruptpin, LOW);
  digitalWrite(AudioWarningPin, LOW);
  attachInterrupt(digitalPinToInterrupt(2), UserWarning ,HIGH);
  
  
  Serial.begin(9600);
  myRA_a.clear();
  myRA_b.clear();
  myRA_a1.clear();
  myRA_b1.clear();
  Serial.println("Device Powered On.");
  delay(1000);
  SetValues();
  delay(5000);
//-----------------------------------Setup() END.
}

void loop() 
{

  //Floats for Average Distance value for both US & IR.
  float AvrUS = 0; 
  float AvrIR = 0;

  if(ReadSensorsFlag == true){
    for(int i=0; i<12; i++){
      float USreading = US1.Tread();
      float IRreading = IR1.readIR();
      Serial.print("IR: ");
      Serial.println(IRreading);
      Serial.print("US: ");
      Serial.println(USreading);
      myRA_a.addValue(USreading);
      myRA_b.addValue(IRreading);

    }

    AvrUS = myRA_a.getAverage();  //Changed to myRA_a from myRA_a1.
    AvrIR  = myRA_b.getAverage();
    //FirstQueue(); 
  }
  /*else{
    AvrUS = myRA_a.getAverage();
    AvrIR  = myRA_b.getAverage();
    SecondQueue();
  }*/


  if(AvrIR < Threshold || AvrUS < Threshold){
    //Get Time
    //If values are greater than Threshold for more than X amount of time trigger the ISR.
    //for loop?
    Serial.println("Distance Threshold Exceeded!!!");
    digitalWrite(WarningInterruptpin, HIGH);

  }
  

  Serial.print("Average IR & US:  ");
  Serial.print(AvrIR);
  Serial.print(", ");
  Serial.println(AvrUS);
  /*Serial.print("Threshold:  ");
  Serial.println(Threshold);*/
  delay(3000);
//-----------------------------------Loop() END.
}