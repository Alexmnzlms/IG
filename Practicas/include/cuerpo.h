#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"

class Cuerpo{
private:
   Cubo * cubo = nullptr;
   Cilindro * cilindro = nullptr;
   Esfera * esfera = nullptr;
   float altura;
   bool animacion_neg;

public:
   Cuerpo();
   void draw(dibujo tipo_draw, color col, GLenum modo_dibujado) ;
   void setMaterial(Material mat);
   void incrementarAltura(float inc);
   void setColorSeleccion(color col);
};

#endif
