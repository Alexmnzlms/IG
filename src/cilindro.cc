#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include <vector>
#include <cmath>


Cilindro::Cilindro(const float altura, const float radio)
{
   GenerarPerfil(altura,radio);
   vertices_perfil  = 2;
   instancias = 40;
   crearMalla(v, RY);
   tipo_text = 1;
}

void Cilindro::GenerarPerfil(const float altura, const float radio){
   v.push_back({radio,0,0});
   v.push_back({radio,altura,0});
}
