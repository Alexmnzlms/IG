#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include <vector>
#include <cmath>


Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
   GenerarPerfil(num_vert_perfil,radio);
   crearMalla(v, num_instancias_perf);
   bool tapa_sup = true, tapa_inf = true;
   if(tapa_sup){
      ponTapaSup(v, num_instancias_perf, num_vert_perfil);
   }
   if(tapa_inf){
      ponTapaInf(v, num_instancias_perf, num_vert_perfil);
   }
}

void Esfera::GenerarPerfil(const int num_vert_perfil, const float radio){
   Tupla3f origen(0.0, -radio, 0.0);
   std::vector<Tupla3f> perfil;
   float alfa, coor_x, coor_y;
   for(int i = 1; i <= num_vert_perfil; i++){
      alfa = ((M_PI*i)/(num_vert_perfil+1));
      coor_x = origen(0) * cos(alfa) + origen(1) * -1 * sin(alfa);
      coor_y = origen(0)* sin(alfa) + origen(1) * cos(alfa);
      v.push_back({coor_x, coor_y, origen(2)});
      std::cout << v.back() << std::endl;
   }
}
