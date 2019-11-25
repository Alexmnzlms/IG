#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"
#include <vector>
#include <cmath>


Cono::Cono(const int num_instancias_perf, const float altura, const float radio,bool tapa_inf)
{

   vertices_perfil  = 1;
   instancias = num_instancias_perf;

   v.push_back({radio,0,0});
   rotarPunto(v, num_instancias_perf);
   v.push_back({0,altura,0});
   v.push_back({0,0,0}); //Añado polo inferior

   for(int i = 0; i < num_instancias_perf; i++){
      f.push_back(Tupla3i(i, (i+1), v.size()-2));
   }

   tapaInf = !tapa_inf;
   ponTapaInf();
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
