#include <Arduino.h>
#include <IRsensor.h>
#include <USsensor.h>
#include <RunningAverage.h>

/*
Project Library Main
Luke MacRedmond
L.MACREDMOND1@nuigalway.ie
Date of last modification:    20/03/2019.
*/


//Pin Layout
//const int irsense = A0;
//const int trigPin =11;   (Yellow)
//const int echoPin =12;   (Blue)
//const int BtTx = 1;      (Green)
//const int BtRx = 0;      (White)


//Running Average Library, used for Buffer implementation.
const int BufferLength = 20;
RunningAverage myRA_a(BufferLength);
RunningAverage myRA_b(BufferLength);
RunningAverage myRA_a1(BufferLength);
RunningAverage myRA_b1(BufferLength);
uint32_t samples = 0;
uint32_t samples2 = 0;

//Sensor Objects Instantiation  
USsensor US1(11, 12);     //Instantiate USsensor class, define pin numbers.
IRsensor IR1(A0);         //Instantiate IRsensor class, define pin numbers.

//Flag determines which RunningAverage queue to store readings in.
volatile bool ReadSensorsFlag;

//Sets Digital pin 2 to trigger specific ISR on a HIGH value.
//Digital pin 6 set to trigger LED/Buzzer Warning.
const int WarningInterruptpin = 2;    //Unused external pin 
const int AudioWarningPin = 6;        //Speaker pin

//Flags=====================================================================
volatile bool Warningflag = false;  //When HIGH, Sends trigger signal to Nano Circuit

bool IRsensorFlag = false;      //Set HIGH when AvrIR is less than Distance Threshold
bool USsensorFlag = false;      //Set HIGH when AvrUS is less than Distance Threshold


//Defines Distance Threshold for warning the User.
static float Threshold;
//Variables for ensuring noise spikes dont trigger warning.
/*--------------------------------------------------------------------------
float ThresRange; //Calculated as a fraction of Threshold value???
float ThresCheckup = Threshold + ThresRange;
float ThresCheckdn = Threshold - ThresRange;
--------------------------------------------------------------------------*/

void UserWarning(){
  noInterrupts();
  //Method to warn user.
  //ISR for Digital Pin 2.
  digitalWrite(AudioWarningPin, HIGH);
}

//Method called from Setup(), prompts user to define Distance Thrshold.
void SetValues(){
  //Serial.println("Input a Threshold range");
  Threshold = 60;
  //ThresRange = 20;
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
/*----------------------------New Method-------------------------------*/
void CheckwarningFlag(){
  unsigned long timer1 = millis();

    // if(ThresCheckup>= AvrIR && ThresCheckup>=AvrUS){
        if((millis()-timer1) > 500){
          timer1 = millis();

          Warningflag = true;


        }else{
          Warningflag = false;
        }
      
      //Get Time
      //If values are greater than Threshold for more than X amount of time trigger the ISR.
      //for loop?
      //Warningflag = true;
        //Serial.println("Distance Threshold Exceeded!!!");
        //digitalWrite(WarningInterruptpin, HIGH);
      
      //digitalWrite(WarningInterruptpin, LOW);
      if(Warningflag == true){
      Serial.println("Distance Threshold Exceeded!!!");
      digitalWrite(WarningInterruptpin, HIGH);
    }else{
      digitalWrite(WarningInterruptpin, LOW);
    }

}


//-----------------------------Setup & Loop-------------------------------------------------------
void setup() {
  //Interrupt Service Routine 'UserWarning' attached to pin 2, triggers when pin is set High
  pinMode(WarningInterruptpin, OUTPUT);
  pinMode(AudioWarningPin, INPUT);
 
  digitalWrite(WarningInterruptpin, LOW);
  digitalWrite(AudioWarningPin, LOW);
  attachInterrupt(WarningInterruptpin, UserWarning ,HIGH);  //ISR assignment, triggered on HIGH, ISR = UserWarning.
  
  
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
  float AvrUS; 
  float AvrIR;
  if(IRsensorFlag == true || USsensorFlag == true){

    if(AvrIR < Threshold || AvrUS < Threshold){
      UserWarning();
    
      CheckwarningFlag();
    }
}
  

  if(ReadSensorsFlag == true){
    for(int i=0; i<20; i++){
      float USreading = US1.Tread();
      float IRreading = IR1.formulaRead();
      //float IRreading = IR1.readIR();
      
      Serial.print("IR: ");
      Serial.println(IRreading);
      myRA_b.addValue(IRreading);

      Serial.print("US: ");
      Serial.println(USreading);
      myRA_a.addValue(USreading);

    }

    AvrUS = myRA_a.getAverage();    //Changed to myRA_a from myRA_a1.
    AvrIR  = myRA_b.getAverage();
    //FirstQueue(); 
  }
  else{
    AvrUS = myRA_a.getAverage();
    AvrIR  = myRA_b.getAverage();
    SecondQueue();
  }


  

  Serial.print("Average IR & US:  ");
  Serial.print(AvrIR);
  Serial.print(", ");
  Serial.println(AvrUS);
  /*Serial.print("Threshold:  ");
  Serial.println(Threshold);*/
  delay(3000);
//---------------------------------------------Loop() END.---------------------------------
}