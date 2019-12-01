#include "aux.h"
#include "luz.h"
#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional(const Tupla2f & orientacion,
                              GLenum idLuzOpenGL,Tupla4f colorA,
                              Tupla4f colorD,Tupla4f colorE){
   id = idLuzOpenGL;
   colorAmbiente = colorA;
   colorDifuso = colorD;
   colorEspecular = colorE;

   float x, y, z;
   x = sin(orientacion(0))*cos(orientacion(1));
   y = cos(orientacion(0))*sin(orientacion(1));
   z = cos(orientacion(1));
   posicion = {x,y,z,0.0};
}

void LuzDireccional::variarAnguloAlpha( float incremento ){

}
void LuzDireccional::variarAnguloBeta( float incremento ){

}
