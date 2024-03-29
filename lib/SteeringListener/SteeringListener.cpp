#include <SteeringListener.h>
#include <ESPAsyncWebServer.h>
#include <Util.h>
#include <Logger.h>
#include <Arduino.h>


AsyncWebServer server(120);
AsyncWebSocket ws("/ws");

int* p_motur;
int* p_kiera;
bool* p_handleOta;
bool* p_cameraResult;

int s_motur = 0;
int s_kiera = 0;
void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
      if(data == NULL){
        client->text("NULL message");
        return;
      }
      String msg = String((char *) data);
      msg.trim();
      String action = explode(msg, '=', 0);
      String actionParam = explode(msg, '=', 1);
      logD(msg);
      logD(action);
      logD(actionParam);
      if (action == "setOta") {
        *p_handleOta = parseString(actionParam);
        client->text("handlingOta set to: " + boolToString(*p_handleOta));
      } else if(action == "motion"){
          s_motur = explode(actionParam, ',', 0).toInt();
          s_kiera = explode(actionParam, ',', 1).toInt();
          s_motur = normalize(s_motur, 70);
          s_kiera = normalize(s_kiera, 50);
          *p_kiera = s_kiera;
          *p_motur = s_motur;
          client->text("motur set to:" + String(*p_motur) + " kiera set to: " + String(*p_kiera));
      } else if(action == "logToMe") {
          bool b = parseString(actionParam);
          if(b){
            setLoggingClient(client);
            client->text("Started logging 2 u, camera result: " + boolToString(*p_cameraResult));
          } else {
            setLoggingClient(NULL);
            client->text("Stopped logging 2 u");
          }
      } else if(action == "setScan") {
        //scan_i2c = parseString(actionParam);
       // client->text("scan_i2c set to: " + boolToString(scan_i2c));
      } else {
          client->text("unknown command");
      }
    
  }
  }
}

void startListening(){
    // attach AsyncWebSocket
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.begin();
}

void attachVariablesToListen(int* aMotur, int* aKiera, bool* aHandleOta, bool* aCameraResult){
  p_motur = aMotur;
  p_kiera = aKiera;
  p_handleOta = aHandleOta;
  p_cameraResult = aCameraResult;
}




