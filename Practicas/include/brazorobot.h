#ifndef BR_H_INCLUDED
#define BR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cono.h"
#include "objply.h"
#include <cstdlib>

class BrazoRobot{
   private:
      ObjPLY * pie = nullptr ;
      ObjPLY * pierna = nullptr ;
      ObjPLY * femur = nullptr ;
      Cono * cono = nullptr;
      float alfa;
      float beta;
      bool animacion_neg;
   public:
      BrazoRobot(float a);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
      void incrementarAngulo(float inc);
};

#endif