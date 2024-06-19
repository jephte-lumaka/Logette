#include <ArduinoJson.h> // Bibliothèque pour manipuler JSON
#include <HTTPClient.h>  // Bibliothèque pour les requêtes HTTP

void sendJSONData() {
  // Créer un objet JSON
  StaticJsonDocument<200> doc;
  doc["phase1_voltage"] = Voltage1;
  doc["phase2_voltage"] = Voltage2;
  doc["phase3_voltage"] = Voltage3;
  doc["relay1_state"] = (digitalRead(Relais1) == LOW) ? "ACTIVE" : "INACTIVE";
  doc["relay2_state"] = (digitalRead(Relais2) == LOW) ? "ACTIVE" : "INACTIVE";
  doc["relay3_state"] = (digitalRead(Relais3) == LOW) ? "ACTIVE" : "INACTIVE";

  // Convertir l'objet JSON en String
  String jsonString;
  serializeJson(doc, jsonString);

  // Envoyer les données JSON via une requête HTTP POST
  HTTPClient http;
  http.begin("http://your_server_endpoint_here");
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error sending POST request. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}