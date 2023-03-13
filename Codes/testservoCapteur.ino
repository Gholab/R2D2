#include "Servo.h"
#include <NewPing.h>

Servo servo1; // declaration du premier servo
Servo servo2; // declaration du second servo



//partie capteur
const int trig=9;
const int echo=8;
unsigned int distance_cm=0;
NewPing sonar(trig,echo,400); // lecture distance en cm avec distance max fixée à 400 cm
char Data;


void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo1.attach(5); // attache le servo 1 à 10
  servo2.attach(6); // attache le servo 2 à 11
  Serial.begin(38400);
  Serial.println("Bonjour -Pret pour les commandes AT");

    
}

void loop() {
  if(Serial.available()){
    Data=Serial.read();
    if (Data=='B'){
      servo1.write(90); // demande au servo 1 de se déplacer à la position 90
      servo2.write(90); // demande au servo 2 de se déplacer à la position 90
      
      }
      
    distance_cm=sonar.ping_cm();
    Serial.print(distance_cm+" ");
    Serial.println(Data);
    
    
      if (Data=='A'){
        if (distance_cm > 10){
          servo1.write(170); // demande au servo 1 de se déplacer à la position 0
          servo2.write(10); // demande au servo 2 de se déplacer à la position 180
        }
        else{
          servo1.write(90); // demande au servo 1 de se déplacer à la position 90
          servo2.write(90); // demande au servo 2 de se déplacer à la position 90
          }
        
      }
      if (Data=='R'){
        servo1.write(0); // demande au servo 1 de se déplacer à la position 180
        servo2.write(180); // demande au servo 2 de se déplacer à la position 0
        }
      if (Data=='D'){
        servo1.write(170); // demande au servo 1 de se déplacer à la position 90
        servo2.write(90); // demande au servo 2 de se déplacer à la position 180
        }

      if (Data=='G'){
        servo1.write(90); // demande au servo 1 de se déplacer à la position 180
        servo2.write(10); // demande au servo 2 de se déplacer à la position 90
        }
      if (Data=='S' ){
        servo1.write(90); // demande au servo 1 de se déplacer à la position 90
        servo2.write(90); // demande au servo 2 de se déplacer à la position 90
        }
    

 
      
       
      }
}
