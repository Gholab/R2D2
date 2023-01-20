#include<Wire.h>
const int MPU=0x68;//MPU6050 IC2 Adress
float Acc_X, Acc_Y, Acc_Z,angle_x,angle_y;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Wire.begin();//initialize commucation
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(B00000000);
  Wire.endTransmission();

  delay(20);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);

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
  if((angle_x<=10)&&(angle_x>=-10)&&(angle_y>=-10)&&(angle_y<=10)){
    
    Serial.println("  STOP");
  }
  if((angle_x<-10)&&(angle_x>=-90)&&(angle_y>=-10)&&(angle_y<=10)){
    
    Serial.println("  AVANCE");}

  if((angle_x<=90)&&(angle_x>10)&&(angle_y>=-10)&&(angle_y<=10)){
    
    Serial.println("  RECULE");
    }
  if((angle_y<-10)&&(angle_y>=-90)&&(angle_x>=-10)&&(angle_x<=10)){
    
    Serial.println("  GAUCHE");}

  if((angle_y<=90)&&(angle_y>10)&&(angle_x>=-10)&&(angle_x<=10)){
    
    
    Serial.println("   DROITE");
    }
  else{
    Serial.println("---------");
    }
  
  

  delay(100);
}
  
  
