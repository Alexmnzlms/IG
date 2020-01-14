#ifndef TORRE_H_INCLUDED
#define TORRE_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "textura.h"
#include "esfera.h"

class Torre{
private:
   Cilindro * cilindro = nullptr;
   Esfera * esfera = nullptr;
   float altura;
   bool animacion_neg;

public:
   Torre();
   void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
   void setMaterial(Material mat);
   void incrementarAltura(float inc);
};

#endif
