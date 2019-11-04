#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include <vector>
#include <cmath>


Cilindro::Cilindro(const int num_instancias_perf,const float altura, const float radio,
                   bool tapa_sup, bool tapa_inf)
{
   vertices_perfil  = 2;
   instancias = num_instancias_perf;

   GenerarPerfil(altura,radio);
   crearMalla(v, num_instancias_perf, RY);

   tapaSup = !tapa_sup;
   tapaInf = !tapa_inf;
   ponTapaSup(instancias, vertices_perfil);
   ponTapaInf(instancias, vertices_perfil);
}

void Cilindro::GenerarPerfil(const float altura, const float radio){
   v.push_back({radio,0,0});
   v.push_back({radio,altura,0});
}
