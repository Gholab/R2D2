#include <NewPing.h>

const int trig=9;
const int echo=8;
unsigned int distance_cm=0;


NewPing sonar(trig,echo,400); // lecture distance en cm avec distance max fixée à 400 cm

void setup() {
  Serial.begin(9600);
  Serial.println("Souhaitez-vous la valeur en cm de la distance Y/N ?");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
    distance_cm=sonar.ping_cm();
    Serial.print(distance_cm);
    Serial.println(" cm");
    delay(60);
  }
