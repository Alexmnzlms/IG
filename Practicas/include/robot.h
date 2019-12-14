#ifndef R_H_INCLUDED
#define R_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "brazorobot.h"
#include "edificio.h"
#include "piernarobot.h"

class Robot{
   private:
      PiernaRobot * pierna = nullptr;
      BrazoRobot * brazo = nullptr;
      Edificio * cuerpo = nullptr;
   public:
      Robot();
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};

#endif
