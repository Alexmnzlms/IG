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
   for(float i = num_vert_perfil; i >= 0; i--){
      coor_x = - radio*(i/num_vert_perfil);
      coor_y = - altura*(i/num_vert_perfil) + altura;
      std::cout << coor_x << "," << coor_y << std::endl;
      v.push_back({coor_x, coor_y, 0});
   }
}
