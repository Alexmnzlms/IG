#ifndef R_H_INCLUDED
#define R_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "brazorobot.h"
#include "edificio.h"
#include "piernarobot.h"
#include <cstdlib>

class Robot{
   private:
      PiernaRobot * piernai = nullptr;
      BrazoRobot * brazoi = nullptr;
      PiernaRobot * piernad = nullptr;
      BrazoRobot * brazod = nullptr;
      Edificio * cuerpo = nullptr;
      float alfa_brazoi;
      float alfa_brazod;
      float alfa_piernas;
      bool animacion_neg;
   public:
      Robot(float a, float b, float c);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
      void incrementarAnguloBrazoIzq(float inc);
      void incrementarAnguloBrazoDer(float inc);
      void incrementarAnguloPiernas(float inc);
};

#endif
