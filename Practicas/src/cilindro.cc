#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include <vector>
#include <cmath>


Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
   GenerarPerfil(num_vert_perfil,altura,radio);
   crearMalla(v, num_instancias_perf);
}

void Cilindro::GenerarPerfil(const int num_vert_perfil, const float altura, const float radio){
   float coor_x, coor_y;
   for(float i = 0; i <= num_vert_perfil; i++){
      coor_y = altura*(i/num_vert_perfil);
      v.push_back({radio, coor_y, 0});
   }
}
