#include<Wire.h>
#include<SoftwareSerial.h>
const int MPU=0x68;//MPU6050 IC2 Adress
float Acc_X, Acc_Y, Acc_Z,angle_x,angle_y;
const int bouton=7;// declaration du bouton
int val=1;
int etat=1;
int ancien_val=1;


#define RX 10
#define TX 11
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
  //PARTIE BOUTON
  val=digitalRead(bouton); 
  if ((val==LOW)&&(ancien_val==HIGH)){etat=1-etat;}
  ancien_val=val;
  
  //PARTIE ACC
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);

  //PARTIE BLUET
  while (BlueT.available()) {
    Serial.print(char(BlueT.read()));  
   }
  while (Serial.available()) {
    BlueT.write(char(Serial.read())); }
  
  //PARTIE ACC
  Acc_X=(Wire.read()<<8|Wire.read())/16384.0;
  Acc_Y=(Wire.read()<<8|Wire.read())/16384.0;
  Acc_Z=(Wire.read()<<8|Wire.read())/16384.0;

  angle_x = (atan((Acc_X) / sqrt(pow((Acc_Y),2) + pow((Acc_Z),2))) * 180/PI);
  angle_y = (atan((Acc_Y) / sqrt(pow((Acc_X),2) + pow((Acc_Z),2))) * 180/PI);


  //main a plat > stop
  Serial.print("angle X: ");
  Serial.print(angle_x);
  Serial.print(" |angle Y: ");
  Serial.print(angle_y);
  if (etat==HIGH){
    BlueT.write("B\n"); //pas allume
  }
  else{
    //allume
  if((angle_x<=15)&&(angle_x>=-15)){
    if((angle_y<-15)&&(angle_y>=-90)){
      Serial.println("  GAUCHE");
      BlueT.write("G\n");}
    if((angle_y<=90)&&(angle_y>15)){
      Serial.println("   DROITE");
      BlueT.write("D\n");
    }
    if((angle_y>=-15)&&(angle_y<=15)){
      Serial.println("  STOP");
      BlueT.write("S\n");
    
    }
    
  }
  if((angle_x<-15)&&(angle_x>=-90)){
    Serial.println("  AVANCE");
    BlueT.write("R\n");}

  if((angle_x<=90)&&(angle_x>15)){
    Serial.println("  RECULE");
    BlueT.write("A\n");
    }
  }
  
  
  
  
}
  
  
