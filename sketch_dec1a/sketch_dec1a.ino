// Définition des broches 
const int flamePin = 2; // Broche D0 du capteur de flamme connecté à la broche numérique 2
const int buzzerPin = 8; // Broche du buzzer connecté à la broche numérique 8

void setup() {
  pinMode(flamePin, INPUT);  // Configurer la broche du capteur de flamme comme entrée 
  pinMode(buzzerPin, OUTPUT); // Configurer la broche du buzzer comme sortie 
  Serial.begin(9600);        // Initialiser la communication série
}

void loop() {
  int flameState = digitalRead(flamePin); // Lire l'état du capteur (HIGH ou LOW)
  
  if (flameState == LOW) {  // LOW signifie que la flamme est détectée 
    Serial.println("Flamme détectée !");
  } else {
    Serial.println("Pas de flamme.");
  }

  // Lire la commande envoyée par Qt pour contrôler le buzzer
  if (Serial.available() > 0) {
    char command = Serial.read(); // Lire la commande envoyée depuis Qt

    if (command == '1') {  // Si la commande est '1', allumer le buzzer
      digitalWrite(buzzerPin, HIGH);  // Activer le buzzer
    } else if (command == '0') {  // Si la commande est '0', éteindre le buzzer
      digitalWrite(buzzerPin, LOW);  // Désactiver le buzzer
    }
  }

  delay(100); // Pause pour éviter une boucle trop rapide
}
