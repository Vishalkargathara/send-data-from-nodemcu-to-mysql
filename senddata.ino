#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* ssid     ="yourssid";
const char* password = "yourpassword";

PZEM004Tv30 pzem(D1, D2); // (RX,TX)connect to TX,RX of PZEM
PZEM004Tv30 pzem2(D5, D6);  // (RX,TX) connect to TX,RX of PZEM
PZEM004Tv30 pzem3(D7, D8);  // (RX,TX) connect to TX,RX of PZEM

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
    delay(250);
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void loop() {
  // wait for WiFi connection
  //main energy meter
   float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf(); 
  //energymeter 2
  float voltage2 = pzem2.voltage();
  float current2 = pzem2.current();
  float power2 = pzem2.power();
  float energy2 = pzem2.energy();
  float frequency2 = pzem2.frequency();
  float pf2 = pzem2.pf();
  // energy meter 3
  float voltage3 = pzem3.voltage();
  float current3 = pzem3.current();
  float power3 = pzem3.power();
  float energy3 = pzem3.energy();
  float frequency3 = pzem3.frequency();
  float pf3 = pzem3.pf();
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://youripaddress/pzem/update.php?voltage=" + String(voltage) + "&current=" + String(current) + "&power1=" +String(power) + "&energy=" +String(energy) + "&frequency=" +String(frequency) + "&pf=" + String(pf) + "&currenta=" + String(current2) + "&currentb=" + String(current3) + "&voltagea=" + String(voltage2) + "&voltageb=" + String(voltage3) + "&powera=" + String(power2) + "&powerb=" + String(power3) + "&energya=" + String(energy2) + "&energyb=" + String(energy3) + "&frequencya=" + String(frequency2) + "&frequencyb=" + String(frequency3) + "&pfa=" + String(pf2) + "&pfb=" + String(pf3)) ) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(4000);
}
