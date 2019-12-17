#include "aux.h"
#include <cstdlib>

bool comparefloat(float a, float b){
   float resta = a - b;
   resta = abs(resta);
   if(resta <= 0.0005){
      return true;
   }
   else{
      return false;
   }
}
