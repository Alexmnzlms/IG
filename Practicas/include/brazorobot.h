#ifndef BR_H_INCLUDED
#define BR_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cono.h"
#include "piernarobot.h"
#include <cstdlib>

class BrazoRobot{
   private:
      PiernaRobot * pierna = nullptr ;
      Cono * cono = nullptr;
      float alfa;
      float delta;
      bool animacion_neg;
      bool izquierda;
   public:
      BrazoRobot(float a, bool izq);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
      void incrementarAngulo(float inc);
      void incrementarTaladro(float inc);
};

#endif
