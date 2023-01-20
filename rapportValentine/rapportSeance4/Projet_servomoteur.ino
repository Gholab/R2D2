#include "Servo.h"
#include<SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial BlueT(RX,TX);

Servo servo1; // declaration du premier servo
Servo servo2; // declaration du second servo
const int bouton=7;// declaration du bouton
int val=1;
int etat=1;
int ancien_val=1;
char Data;

void setup() {
   servo1.attach(5); // attache le servo 1 à 5
   servo2.attach(6); // attache le servo 2 à 6
   pinMode(bouton,INPUT); 
   Serial.begin(38400);
   delay(500);
   Serial.println("Bonjour -Pret pour les commandes AT");
   BlueT.begin(38400);
   delay(500);
}

void loop() {
  val=digitalRead(bouton); 
  while (BlueT.available()) {
    Serial.print(char(BlueT.read()));
    }
  while (Serial.available()) {
    BlueT.write(char(Serial.read()));
    }
  if ((val==LOW)&&(ancien_val==HIGH)){
    etat=1-etat;
    }
  ancien_val=val;
  if (etat==HIGH){
    servo1.write(90); // demande au servo 1 de se déplacer à la position 90
    servo2.write(90); // demande au servo 2 de se déplacer à la position 180
   
    }
  else{
    if(BlueT.available()){
      Data=BlueT.read();
    }
    if (Data=='A'){
      servo1.write(0); // demande au servo 1 de se déplacer à la position 0
      servo2.write(180); // demande au servo 2 de se déplacer à la position 180
      Serial.println("Je suis la ");
      }
      if (Data=='R'){
        servo1.write(180); // demande au servo 1 de se déplacer à la position 0
        servo2.write(0); // demande au servo 2 de se déplacer à la position 180
        }
      if (Data=='D'){
        servo1.write(90); // demande au servo 1 de se déplacer à la position 0
        servo2.write(180); // demande au servo 2 de se déplacer à la position 180
        }

      if (Data=='G'){
        servo1.write(180); // demande au servo 1 de se déplacer à la position 0
        servo2.write(90); // demande au servo 2 de se déplacer à la position 180
        }
      if (Data=='S' ){
        servo1.write(90); // demande au servo 1 de se déplacer à la position 0
        servo2.write(90); // demande au servo 2 de se déplacer à la position 180
        }
      if (Data=='X' ){
        servo1.write(90); // demande au servo 1 de se déplacer à la position 0
        servo2.write(90); // demande au servo 2 de se déplacer à la position 180
        }
      }
    
    
  
   

}
