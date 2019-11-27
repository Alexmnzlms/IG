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
   calcular_colores();
}

void Cono::rotarPunto(std::vector<Tupla3f> perfil_original, int num_instancias){
   float alfa, coor_x, coor_z;
   int a, b;
   int num_vertices = perfil_original.size();
   for(int i = 1; i <= num_instancias; i++){
      alfa = ((2*M_PI*i)/num_instancias);
      for(int j = 0; j < num_vertices; j++){
         coor_x = perfil_original[j](0) * cos(alfa) + perfil_original[j](2) * sin(alfa);
         coor_z = perfil_original[j](0)* -1 * sin(alfa) + perfil_original[j](2) * cos(alfa);
         v.push_back({coor_x, perfil_original[j](1), coor_z});
      }
   }
}

void Cono::tapaSuperior(){
}
