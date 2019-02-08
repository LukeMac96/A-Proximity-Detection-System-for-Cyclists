#include <Arduino.h>
#include <USsensor.h>
#include <IRsensor.h>
//#include <QueueList.h>



//Project Library Main
//23/01/2019.

//Pin Layout
//const int irsense = A0;
//const int trigPin =3;
//const int echoPin =2;

USsensor US1(3, 2);     //Instantiate USsensor class, define pin numbers.
IRsensor IR1(A0);       //Instantiate IRsensor class, define pin numbers.

volatile bool B1flag;

//int USdistance =0;
//long duration =  pulseIn(echoPin, HIGH);


void setup() {
  //pinMode(trigPin, OUTPUT);     pinMode() call happens inside library USsensor.cpp
  //pinMode(echoPin, INPUT);

  Serial.begin(9600);
}


void loop() {

          /*US1.Trigger();   //Call function to trigger US pin 3(Yellow).
          delayMicroseconds(500);
          US1.USread();     //Call function to Read value from US, pin 2(Blue).    
          delayMicroseconds(500);
          IR1.readIR();*/
  US1.Smoothing();
  
  if(B1flag = true){



  }

 
  Serial.println(millis());
  Serial.print("US distance:  ");
  Serial.println(US1.Tread());
  Serial.println(millis());

  delay(199);

  

}

/* TimingData from millis() US1.Tread()
0
US distance:  61
4
202
US distance:  -343
381
580
US distance:  25
582
782
US distance:  -278
964
1164
US distance:  25
1166
1366
US distance:  -304
1546
1745
US distance:  24
1747
1947
US distance:  -291
2128
2328
US distance:  48
2331
2531
US distance:  62
2535
2735
US distance:  63
2740
2938
US distance:  -302
3120
*/


