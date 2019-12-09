#ifndef EDIF_H_INCLUDED
#define EDIF_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"

class Edificio{
   private:
      Cubo * cubo = nullptr;
      Cilindro * cilindro = nullptr;
      Esfera * esfera = nullptr;
   public:
      Edificio();
      void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
      void setMaterial(Material mat);
};

#endif
