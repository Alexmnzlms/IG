#ifndef BR_H_INCLUDED
#define BR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cono.h"
#include "piernarobot.h"

class BrazoRobot{
   private:
      PiernaRobot * pierna = nullptr ;
      Cono * cono = nullptr;
   public:
      BrazoRobot();
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};

#endif
