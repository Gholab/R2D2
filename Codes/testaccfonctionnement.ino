

#include<Wire.h>
#include<SoftwareSerial.h>
const int MPU=0x68;//MPU6050 IC2 Adress
float Acc_X, Acc_Y, Acc_Z,angle_x,angle_y;
const int bouton=7;// declaration du bouton
int val=1;
int etat=1;
int ancien_val=1;
#define RX 9
#define TX 10
SoftwareSerial BlueT(RX,TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(38400);
  delay(500);
 
  Wire.begin();//initialize commucation
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(B00000000);
  Wire.endTransmission();
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  val=digitalRead(bouton); //lecture de la valeur du bouton
  if ((val==LOW)&&(ancien_val==HIGH)){etat=1-etat;}
  ancien_val=val;
  //PARTIE ACC
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);
  //PARTIE ACC
  //acceleration selon les 3axes x,y,z
  Acc_X=(Wire.read()<<8|Wire.read())/16384.0;
  Acc_Y=(Wire.read()<<8|Wire.read())/16384.0;
  Acc_Z=(Wire.read()<<8|Wire.read())/16384.0;
  //calcul de l'angle selon x et y
  angle_x = (atan((Acc_X) / sqrt(pow((Acc_Y),2) + pow((Acc_Z),2))) * 180/PI);
  angle_y = (atan((Acc_Y) / sqrt(pow((Acc_X),2) + pow((Acc_Z),2))) * 180/PI);


  
  Serial.print("angle X: "); //print des angles
  Serial.print(angle_x);
  Serial.print(" |angle Y: ");
  Serial.print(angle_y);
  if (etat==HIGH){// si le bouton n'est pas encore appuye
    Serial.println("pas appuye");
    BlueT.write("B\n");; //envoie B a la partie receptrice pr le robot s'arrete
  }
  else{
    //allume
  if((angle_x<=25)&&(angle_x>=-25)){
    if((angle_y<-25)&&(angle_y>=-90)){
      Serial.println("  DROITE");
      BlueT.write("D\n");//tourne a droite
    }
    if((angle_y<=90)&&(angle_y>25)){
      Serial.println("   GAUCHE");
      BlueT.write("G\n");//tourne a gauche
    }
    if((angle_y>=-25)&&(angle_y<=25)){
      Serial.println("  STOP");
      BlueT.write("S\n");//s'arrete
    
    }
    
  }
  if((angle_x<-25)&&(angle_x>=-90)){
    Serial.println("  AVANCE");
    BlueT.write("A\n");//envoie la commande avance
   
    }

  if((angle_x<=90)&&(angle_x>25)){
    Serial.println("  RECULE");
    BlueT.write("R\n");//envoie la commande recule
    }
    

  
  

}

}
