#include <Arduino.h>
#include <ESPAsyncWebServer.h>


void logD(String message);
void logD(unsigned long n, uint8_t base);

void setLoggingClient(AsyncWebSocketClient * client);