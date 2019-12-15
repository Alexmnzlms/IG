#ifndef PR_H_INCLUDED
#define PR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objply.h"

class PiernaRobot{
   private:
      ObjPLY * pie = nullptr ;
      ObjPLY * pierna = nullptr ;
      ObjPLY * femur = nullptr ;
      float alfa;
      float beta;
   public:
      PiernaRobot(float a);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};

#endif
