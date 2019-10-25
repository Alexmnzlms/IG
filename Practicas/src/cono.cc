#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"
#include <vector>
#include <cmath>


Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
   GenerarPerfil(num_vert_perfil,altura,radio);
   crearMalla(v, num_instancias_perf);
}

void Cono::GenerarPerfil(const int num_vert_perfil, const float altura, const float radio){
   float coor_x, coor_y;
   for(float i = 1; i < num_vert_perfil; i++){
      coor_x = -radio*(i/num_vert_perfil) + radio;
      coor_y = altura*(i/num_vert_perfil);
      v.push_back({coor_x, coor_y, 0});
   }
}
