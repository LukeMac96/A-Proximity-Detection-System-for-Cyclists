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
const int BufferLength = 10;
RunningAverage myRA_a(BufferLength);
RunningAverage myRA_b(BufferLength);
RunningAverage myRA_a1(BufferLength);
RunningAverage myRA_b1(BufferLength);


//Sensor Objects Instantiation  
USsensor US1(11, 12);     //Instantiate USsensor class, define pin numbers.
IRsensor IR1(A0);         //Instantiate IRsensor class, define pin numbers.
//Floats for Average Distance value for both US & IR.
float AvrUS = 0; 
float AvrIR = 0;

//Flag determines which RunningAverage queue to store readings in.
volatile bool ReadSensorsFlag;
volatile bool IRsensorFlag;      //Set HIGH when AvrIR is less than Distance Threshold
volatile bool USsensorFlag;      //Set HIGH when AvrUS is less than Distance Threshold

//Sets Digital pin 2 to trigger specific ISR on a HIGH value.
//Digital pin 6 set to trigger LED/Buzzer Warning.
const int WarningInterruptpin = 2;    //Unused external pin 
const int AudioWarningPin = 6;        //Speaker pin

//Flags=====================================================================
volatile bool Warningflag = false;  //When HIGH, Sends trigger signal to Nano Circuit

//Defines Distance Threshold for warning the User.
static float Threshold;

//Defines which set of Queues to add values to
bool queue = true;

//Method called from Setup(), prompts user to define Distance Thrshold.
void SetValues(){
  //Serial.println("Input a Threshold range");
  Threshold = 150;
  Serial.print("Distance Threshold set to:  ");
  Serial.print(Threshold);
  Serial.println("CM.");
  ReadSensorsFlag = true;
  //Clear Running Average queues
  myRA_a.clear();
  myRA_b.clear();
  myRA_a1.clear();
  myRA_b1.clear();
  //Set Threshold flags low
  IRsensorFlag = false;
  USsensorFlag = false;
}

void AddValues(bool queue){
  if(queue == true){
    
    for(int i=0; i<BufferLength; i++){
      float USreading = US1.Tread();
      float IRreading = IR1.POWRead();
      
      myRA_a.addValue(IRreading);
      myRA_b.addValue(USreading);

      Serial.print("IR: ");
      Serial.println(IRreading);
      
      Serial.print("US: ");
      Serial.println(USreading);
    }
    queue = false;
    AvrIR = myRA_a.getAverage();
    AvrUS = US1.Tread();
    if(AvrIR < Threshold){
      IRsensorFlag = true;

    }else{noTone(AudioWarningPin);}
    if(AvrUS <= Threshold){
      USsensorFlag = true;

    }else{noTone(AudioWarningPin);}
    myRA_a.clear();
    myRA_b.clear();
  }else{

    for(int i=0; i<BufferLength; i++){
      float USreading = US1.Tread();
      float IRreading = IR1.POWRead();
      
      myRA_a1.addValue(IRreading);
      myRA_b1.addValue(USreading);

      Serial.print("IR: ");
      Serial.println(IRreading);
      
      Serial.print("US: ");
      Serial.println(USreading);
    }
    queue = true;
    AvrIR = myRA_a1.getAverage();
    AvrUS = US1.Tread();
    if(AvrIR < Threshold){
      IRsensorFlag = true;

    }else{noTone(AudioWarningPin);}
    if(AvrUS <= Threshold){
      USsensorFlag = true;

    }else{noTone(AudioWarningPin);}
    myRA_a1.clear();
    myRA_b1.clear();

  }
}



void CheckVal(){

  if(USsensorFlag == true || IRsensorFlag == true){

    //Double check Averaged values
    if(AvrIR < Threshold || AvrUS < Threshold)
    {
      //Tone Function generates a 500 Hertz PWM signal
      //Audio warning signal
      tone(AudioWarningPin, 600);
      digitalWrite(WarningInterruptpin, HIGH);
    }
    //If Averaged values are above Threshold reset flags low  
    else if(AvrIR > Threshold){
      noTone(AudioWarningPin);
      digitalWrite(WarningInterruptpin, LOW);
      IRsensorFlag = false;
    }
    else if(AvrUS > Threshold){
      noTone(AudioWarningPin);
      digitalWrite(WarningInterruptpin, LOW);
      USsensorFlag = false;
    }
  }
}


//-----------------------------Setup & Loop-------------------------------------------------------
void setup() {

  pinMode(AudioWarningPin, OUTPUT); 
  digitalWrite(AudioWarningPin, LOW);
  //attachInterrupt(WarningInterruptpin, UserWarning ,HIGH);  //ISR assignment, triggered on HIGH, ISR = UserWarning.
   
  Serial.begin(9600);
 
  Serial.println("Device Powered On.");
  delay(1000);
  SetValues();
  delay(5000);
//-----------------------------------Setup() END.
}


void loop() {
  noTone(AudioWarningPin);
  CheckVal();
  

  AddValues(ReadSensorsFlag);

    //Two if loops check if the Averaged sensor readings are below the Threshold 
  if(AvrIR > Threshold){
    IRsensorFlag = false;
  }
  if(AvrUS > Threshold){
    USsensorFlag = false;
  }
  
  CheckVal();

  /*If Sensor Threshold flags are set 
  if(IRsensorFlag == true || USsensorFlag == true){
    CheckVal();
  }
  */
    Serial.print("Average IR & US:  ");
    Serial.print(AvrIR);
    Serial.print(", ");
    Serial.println(AvrUS);
    
    delay(1000);
    
  //---------------------------------------------Loop() END.---------------------------------
}