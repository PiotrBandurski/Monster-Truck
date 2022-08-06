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

// void debug_scanI2C() {
//   byte error, address;
//   int nDevices;
//   logD("Scanning...");
//   nDevices = 0;
//   for(address = 1; address < 127; address++ ) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0) {
//       logD("I2C device found at address 0x");
//       if (address<16) {
//         logD("0");
//       }
//       logD(address,HEX);
//       nDevices++;
//     }
//     else if (error==4) {
//       logD("Unknow error at address 0x");
//       if (address<16) {
//         logD("0");
//       }
//       logD(address,HEX);
//     }    
//   }
//   if (nDevices == 0) {
//     logD("No I2C devices found\n");
//   }
//   else {
//     logD("done\n");
//   }
// }

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
  if(!handleOta){
    //debug_scanI2C();
    //handleOta = true;
    //scan_i2c = false;
  }
}

