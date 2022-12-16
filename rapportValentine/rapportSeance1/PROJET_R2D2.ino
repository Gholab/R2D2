//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5
//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin 7
void setup() {
  Serial.begin(9600);
  pinMode(ENA,OUTPUT); // Configurer
  pinMode(ENB,OUTPUT); // les broches
  pinMode(IN1,OUTPUT); // comme sortie
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
  // Direction du Moteur A
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  // Direction du Moteur B
  // NB: en sens inverse du moteur A
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
void loop() {
  //Variation de la vitesse 
  // Moteur A - Plein régime
  analogWrite(ENA,255);
  // Moteur B - Mi-régime
  analogWrite(ENB,150);

  //Moteurs en marche avant pendant 5 secondes
  //Moteur A 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //Moteur B
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(5000);

  //Moteurs en marche arrière pendant 5 secondes 
  //Moteur A 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //Moteur B
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(5000);

  //Moteurs à l'arrêt
  // Moteur A
  digitalWrite(ENA,LOW);
  // Moteur B
  digitalWrite(ENB,LOW);
  delay(5000);

  //Pour tourner à droite 
  //Moteur A à pleine vitesse en marche avant
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(ENA,HIGH);
  //Moteur B à l'arrêt
  digitalWrite(ENB,LOW);
  delay(5000);

  //Pour tourner à gauche
  //Moteur B à pleine vitesse en marche avant
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENB,HIGH);
  //Moteur A à l'arrêt
  digitalWrite(ENA,LOW);
  delay(5000);

  

  

  
  }
