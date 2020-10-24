#include "Util.h"
#include <Arduino.h>


bool parseString(String s) {
  if(s.charAt(0) == 't' || s.charAt(0) == 'T') {
    return true;
  } else { 
    return false;
  }

}

String boolToString(bool b) {
  if (b){
    return "true";
  } else {
    return "false";
  }
}


String explode(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int normalize(int i, int max) {
  if (i >= 0){
    if(i > max){
      return max;
    }
    return i;
  } else{
    if(i < -max){
      return -max;
    }
    return i;
  }
  
}