#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "iot-devfest22-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rouR1NwEizID86eAxcEJVsCFb0o9j3C2Ob2YM7kd"
#define WIFI_SSID "Tecno L9"
#define WIFI_PASSWORD "12345678"

const int Sala = 2;

void setup()
{
  Serial.begin(115200);
  pinMode(Sala, OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (Firebase.failed())
  {
    Serial.print(Firebase.error());
  }
  else {
    Serial.print("Firebase Connected");
  }

  
}
void loop()
{
  Firebase.setInt("Teste", random(1,100));
  
  FirebaseObject casa = Firebase.get("/SALA/");
  String LuzSala = casa.getString("estado");
  if (LuzSala == "LIGADA") {
    digitalWrite(Sala, LOW);
  }
  else if (LuzSala == "DESLIGADA") {
    digitalWrite(Sala, HIGH);
  }
}
