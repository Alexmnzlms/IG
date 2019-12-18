#ifndef PR_H_INCLUDED
#define PR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"
#include <cstdlib>

class PiernaRobot{
   private:
      ObjPLY * pie = nullptr ;
      ObjPLY * pierna = nullptr ;
      ObjPLY * femur = nullptr ;
      float alfa;
      float beta;
      bool animacion_neg;
   public:
      PiernaRobot(float a);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
      void incrementarAngulo(float inc);
      float getAlfa();
      void setAlfa(float a);
};

#endif
