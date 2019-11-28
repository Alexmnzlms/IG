#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"
#include <vector>
#include <cmath>


Cono::Cono(const int num_instancias_perf, const float altura, const float radio,bool tapa_inf)
{
   v.push_back({radio,0,0});
   v.push_back({0,altura,0});
   vertices_perfil  = 2;
   instancias = num_instancias_perf;
   crearMalla(v, RY);
   pos_tapas = instancias/2;
   calcular_colores();
}
