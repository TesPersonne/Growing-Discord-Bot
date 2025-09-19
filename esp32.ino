#include <DHT11.h>
//#define RELAY_POMPE 25
//#define RELAY_BRUME 32
#define SOIL_PIN 34
#define DHT_PIN 23
#define TAUX_HUMIDITER 65 

DHT11 dht11(DHT_PIN);

//unsigned long arrosageStart = 0;
//bool arrosageEnCours = false;
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(115200);

  //pinMode(RELAY_POMPE, OUTPUT);
 //pinMode(RELAY_BRUME, OUTPUT);
  //digitalWrite(RELAY_POMPE, LOW);
 //digitalWrite(RELAY_BRUME, LOW);
}

void loop() {
    float temp = dht11.readTemperature();
    float hum = dht11.readHumidity();
  // Envoi toutes les 30s
  if (millis() - lastSendTime >= 300000) {
    int soil = analogRead(SOIL_PIN);

    Serial.print("DATA;");
    Serial.print(temp);
    Serial.print(";");
    Serial.print(hum);
    Serial.print(";");
    Serial.println(soil);

    lastSendTime = millis();
  }
  
 /* if( hum < TAUX_HUMIDITER - 5){
  digitalWrite(RELAY_BRUME, HIGH);
}else if (hum > TAUX_HUMIDITER + 5)
{
   digitalWrite(RELAY_BRUME, LOW);
}else if( hum == TAUX_HUMIDITER){
   digitalWrite(RELAY_BRUME, HIGH);
}
*/



  // Écoute commandes entrantes
  /*if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "ARROSAGE_ON") digitalWrite(RELAY_POMPE, HIGH);
    else if (cmd == "ARROSAGE_OFF") digitalWrite(RELAY_POMPE, LOW);
    else if (cmd == "BRUME_ON") digitalWrite(RELAY_BRUME, HIGH);
    else if (cmd == "BRUME_OFF") digitalWrite(RELAY_BRUME, LOW);
  }
  if (Serial.available()) {
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();

  if (cmd == "ARROSAGE_ON") {
    digitalWrite(RELAY_POMPE, HIGH);
    arrosageStart = millis();
    arrosageEnCours = true;
  } else if (cmd == "ARROSAGE_OFF") {
    digitalWrite(RELAY_POMPE, LOW);
    arrosageEnCours = false;
  } else if (cmd == "BRUME_ON") {
    digitalWrite(RELAY_BRUME, HIGH);
  } else if (cmd == "BRUME_OFF") {
    digitalWrite(RELAY_BRUME, LOW);
  }
}

// Vérifie si les 30 secondes d’arrosage sont écoulées
if (arrosageEnCours && millis() - arrosageStart >= 30000) {
  digitalWrite(RELAY_POMPE, LOW);
  arrosageEnCours = false;
}
  */
}
