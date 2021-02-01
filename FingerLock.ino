
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SPI.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define LOCK 0

void setup() {
  Serial.begin(115200);
  pinMode(LOCK, OUTPUT);
  digitalWrite(LOCK, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if(Firebase.getString("STATUS")=="Abierta"){
    digitalWrite(LOCK, HIGH);    
    delay(3500);  
    digitalWrite(LOCK, LOW);
    Firebase.setString("STATUS", "Cerrada");
    
  }
  if(Firebase.getString("STATUS")=="Cerrada"){
    Firebase.setString("STATUS", "Abierta");
    digitalWrite(LOCK, HIGH);
  }    
  delay(250);
}
