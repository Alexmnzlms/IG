#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"
#include <vector>
#include <cmath>


Cono::Cono(const float altura, const float radio)
{
   v.push_back({radio,0,0});
   v.push_back({0,altura,0});
   vertices_perfil  = 2;
   instancias = 40;
   crearMalla(v, RY);
   pos_tapas = instancias/2;
   tipo_text = 0;
}
