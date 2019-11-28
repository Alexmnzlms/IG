#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include <vector>
#include <cmath>


Cilindro::Cilindro(const int num_instancias_perf,const float altura, const float radio,
                   bool tapa_sup, bool tapa_inf)
{
   GenerarPerfil(altura,radio);
   vertices_perfil  = 2;
   instancias = num_instancias_perf;
   crearMalla(v, RY);
}

void Cilindro::GenerarPerfil(const float altura, const float radio){
   v.push_back({radio,0,0});
   v.push_back({radio,altura,0});
}
