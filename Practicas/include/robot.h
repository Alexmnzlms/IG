#ifndef R_H_INCLUDED
#define R_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "brazorobot.h"
#include "edificio.h"
#include "piernarobot.h"

class Robot{
   private:
      PiernaRobot * piernai = nullptr;
      BrazoRobot * brazoi = nullptr;
      PiernaRobot * piernad = nullptr;
      BrazoRobot * brazod = nullptr;
      Edificio * cuerpo = nullptr;
      float alfa;
      float beta;
   public:
      Robot(float a);
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};

#endif
