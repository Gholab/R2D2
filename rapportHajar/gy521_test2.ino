
#include <Wire.h> //indiquer a la carte qu'om communique en I^2C
const int MPU_addr=0x68;
float Acc_X,Acc_Y,Acc_Z;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1c);
  Wire.write(B00000000);
  Wire.endTransmission();
  
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
 
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true);
  Acc_X=(Wire.read()<<8|Wire.read())/16384;
  Acc_Y=(Wire.read()<<8|Wire.read())/16384;
  Acc_Z=(Wire.read()<<8|Wire.read())/16384;

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(Acc_X);
  Serial.print(" | Y = "); Serial.print(Acc_Y);
  Serial.print(" | Z = "); Serial.println(Acc_Z); 
  

}
