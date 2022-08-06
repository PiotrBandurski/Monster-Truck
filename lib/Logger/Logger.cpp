#include <Arduino.h>
#include <ESPAsyncWebServer.h>


AsyncWebSocketClient *p_client;

void setLoggingClient(AsyncWebSocketClient * client){
    p_client = client;
}

void logD(String message){
    if(p_client != NULL){
        p_client->text(message);
    }
}

void logD(unsigned long n, uint8_t base) {
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if(base < 2) {
        base = 10;
    }

    do {
        unsigned long m = n;
        n /= base;
        char c = m - base * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

    logD(str);
}


