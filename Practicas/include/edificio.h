#ifndef EDIF_H_INCLUDED
#define EDIF_H_INCLUDED

#include "aux.h"
#include "cubo.h"


class Edificio
{
   private:
      Cubo * cubo = nullptr;
   public:
      Edificio();
      void draw(dibujo tipo, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};


#endif
