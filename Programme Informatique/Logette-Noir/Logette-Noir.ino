#include <ZMPT101B.h>
// LED clignotante de RJ45
const int LedRJ45 = 5;

// Trois capteurs de tension
const int Voltage1 = A0;
const int Voltage2 = A1;
const int Voltage3 = A2;

// Trois relais
const int Relais1 = 6;
const int Relais2 = 7;
const int Relais3 = 8;

// Capteurs supplémentaires

void setup() {





  int valeur1 = analogRead(Voltage1);
  int valeur2 = analogRead(Voltage2);
  int valeur3 = analogRead(Voltage3);

  // Conversion des valeurs en tension
  float Voltage1 = (valeur1 * 5.0) / 1023.0; 
  float tension2 = (valeur2 * 5.0) / 1023.0;
  float tension3 = (valeur3 * 5.0) / 1023.0;




// L'écran LCD 20x4
  Serial.begin(9600);
// Capteur de voltage 
  pinMode(Voltage1, INPUT); // Tension de la phase 1
  pinMode(Voltage2, INPUT); // Tension de la phase 2
  pinMode(Voltage3, INPUT); // Tension de la phase 3
// Relais
  pinMode(Relais1, OUTPUT); // Relais de la phase 1
  pinMode(Relais2, OUTPUT); // Relais de la phase 2
  pinMode(Relais3, OUTPUT); // Relais de la phase 3

  pinMode(LedRJ45, OUTPUT); // LED RJ45

}

void loop() {
  AfficherMessage();
// Afficher un message sur l'écran LCD
  Serial.print("LUMAKA  BOX");
// Attendre 2 secondes
  delay(2000);

  RJ45Led();
  ConditionsVoltage(); 

}

void AfficherMessage() {
  // Effacer l'écran LCD
    // Afficher les tensions sur l'écran LCD
  Serial.print("Phase 1: ");
  Serial.print(Voltage1);
  Serial.println(" V");

  Serial.print("Phase 2: ");
  Serial.print(Voltage2);
  Serial.println(" V");

  Serial.print("Phase 3: ");
  Serial.print(Voltage3);
  Serial.println(" V");
  
  // Vous pouvez également ajouter l'état des relais dans le moniteur série
  Serial.print("Phase 1: ");
  if (digitalRead(Relais1) == LOW) {
    Serial.println("ACTIVE");
  } else {
    Serial.println("DESACTIVE");
  }

  Serial.print("Phase 2: ");
  if (digitalRead(Relais2) == LOW) {
    Serial.println("ACTIVE");
  } else {
    Serial.println("DESACTIVE");
  }

  Serial.print("Phase 3: ");
  if (digitalRead(Relais3) == LOW) {
    Serial.println("ACTIVE");
  } else {
    Serial.println("DESACTIVE");
  }
}




void RJ45Led() {
  int randomTime = random(100, 300); // Génère un temps aléatoire entre 100 ms et 800 ms (100 à 800 ms)
  digitalWrite(LedRJ45, HIGH); // Allume la LED
  delay(randomTime); // Attend le temps aléatoire
  digitalWrite(LedRJ45, LOW); // Éteint la LED
  delay(randomTime);
}


void ConditionsVoltage() {


 /*Dans cet exemple, si Voltage1 est supérieur ou égal à 149V et en même temps inférieur
 ou égal à 249V, le relais 1 sera désactivé (LOW). Sinon, le relais 1 sera activé (HIGH).*/
  float voltage1 = measureVoltage(voltage1);
  float voltage2 = measureVoltage(Voltage2);
  float voltage3 = measureVoltage(Voltage3);

  if (voltage1 >= 220 && voltage1 <= 240) { 
    digitalWrite(Relais1, HIGH);  // Relais activé
  } else {
    digitalWrite(Relais1, LOW); // Relais désactivé
  }

  if (voltage2 >= 220 && voltage2 <= 240) {
    digitalWrite(Relais2, HIGH);
  } else {
    digitalWrite(Relais2, LOW);
  }

  if (voltage3 >= 220 && voltage3 <= 240) {
    digitalWrite(Relais3, HIGH);
  } else {
    digitalWrite(Relais3, LOW);
  }
}
  float measureVoltage(int A0) {
  // Code pour mesurer la tension avec le capteur spécifié
  // Retourne la valeur de tension mesuréefloat readVoltage(int pin) {
  int rawValue = analogRead(A0);
  float voltage = (rawValue * 250) / 1024.0;
  return voltage; 
  
}

