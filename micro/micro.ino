// Pin definiti per Wemos D1 R32 (ESP32)
#define DIR_PIN 18
#define STEP_PIN 19
#define ENABLE_PIN 5
#define REDUCTION 8
#define STEP_NUM 200 * REDUCTION

// Velocità del motore (micros tra gli step)
int step_delay = 400;  // numero più grande = più lento
bool motore_attivo = false;  // TRUE quando deve girare
bool direzione_avanti = true;

void setup() {


  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  Serial.begin(115200);
  pinMode(ENABLE_PIN, OUTPUT);
  // All'inizio il motore è spento

  digitalWrite(ENABLE_PIN, HIGH);  // HIGH = disattivato (A4988)
  
  Serial.println("Comandi: A=Avanti, I=Indietro, S=Stop");
}

void loop() {
  // ---- Controllo comando Serial ----
  if (Serial.available()) {
    char c = Serial.read();

    if (c == 'A' || c == 'a') {
      motore_attivo = true;
      direzione_avanti = true;  
      Serial.println("Motore AVVIATO in avanti");

    } else if (c == 'I' || c == 'i') {
      motore_attivo = true;
      direzione_avanti = false; 
      Serial.println("Motore AVVIATO indietro");

    } else if (c == 'S' || c == 's') {
      Serial.println("Motore FERMATO");
    }
  }
      motore_attivo = false;

  // ---- Se il motore è attivo → driver acceso + step ----
  if (motore_attivo) {

    digitalWrite(ENABLE_PIN, LOW);   // driver attivo

    digitalWrite(DIR_PIN, direzione_avanti ? HIGH : LOW);

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(step_delay);

  } else {
    // ---- Motore non attivo → driver spento ----
    digitalWrite(ENABLE_PIN, HIGH);  // disattiva l’A4988
  }
}
