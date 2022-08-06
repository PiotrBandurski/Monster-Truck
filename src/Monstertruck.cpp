#include <OTAHandler.h>
#include <WifiHandler.h>
#include <Engines.h>
#include <SteeringListener.h>
#include <Logger.h>
//#include <Wire.h>

#ifdef cam
#include "CameraHandler.h"
#endif

int motur = 0;
int kiera = 0;
bool handleOta = true;
bool cameraResult = false;

void setup() {
  //Wire.begin(1,3);
  Serial.begin(115200);
  connectToFifi();
  setupOTA();
  #ifdef cam
   cameraResult = setupHttpCamera();
  #endif
  attachVariablesToListen(&motur, &kiera, &handleOta, &cameraResult);
  startListening();
}

void loop() {
  if(handleOta) { 
    handleOTA(); //This is very cpu consuming so I need possibility to turn it off so camera can produce more fps.
  }
  setSpeed(motur);
  setWheelRotation(kiera);
}

