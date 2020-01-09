#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"
#include <vector>
#include <cmath>


Esfera::Esfera(const float radio)
{
   vertices_perfil = 20;
   instancias = 40;
   GenerarPerfil(vertices_perfil,radio);
   crearMalla(v, RY);
   tipo_text = 0;
   std::cout << "--------" << std::endl;
   for(int i = 0; i < v.size(); i++){
      std::cout << v[i] << std::endl;
   }
   std::cout << "---------" << std::endl;
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
   }
}
