#include "aux.h"
#include "luz.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional( const Tupla3f & pos, GLenum idLuzOpenGL, Tupla4f colorA, Tupla4f colorD, Tupla4f colorE){
   id = idLuzOpenGL;
   colorAmbiente = colorA;
   colorDifuso = colorD;
   colorEspecular = colorE;

   posicion = {pos(0),pos(1),pos(2),1.0};
   activada = false;
}
