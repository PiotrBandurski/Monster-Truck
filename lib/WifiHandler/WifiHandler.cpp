#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include "WifiHandler.h"

void connectToFifi() {
  char* ssid = "fifi";
  char* password = "razdwatrzy";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}
