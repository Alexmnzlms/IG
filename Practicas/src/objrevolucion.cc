#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, int mult, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo, v, mult);
   if(tapa_sup){
      float coor_y = v.back()(1);
      v.push_back({0,coor_y,0});
   }
   if(tapa_inf){
      std::vector<Tupla3f> aux;
      float coor_y = v.front()(1);
      aux.push_back({0,coor_y,0});
      for(int i = 0; i < v.size(); i++){
         aux.push_back(v[i]);
      }
      v = aux;
   }
   crearMalla(v, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo, num_instancias);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   std::vector<Tupla3f> aux;
   float alfa, coor_x, coor_z;
   int a, b;
   int num_vertices = perfil_original.size();
   aux=perfil_original;
   for(int i = 1; i <= num_instancias; i++){
      alfa = ((2*M_PI*i)/num_instancias);
      for(int j = 0; j < num_vertices; j++){
         coor_x = aux[j](0) * cos(alfa) + aux[j](2) * sin(alfa);
         coor_z = aux[j](0)* -1 * sin(alfa) + aux[j](2) * cos(alfa);
         v.push_back({coor_x, aux[j](1), coor_z});
      }
   }
   for(int i = 0; i < num_instancias; i++){
      for(int j = 0; j < num_vertices-1; j++){
         a = num_vertices*i + j;
         b = num_vertices*((i+1)%num_instancias)+j;
         f.push_back(Tupla3i(a,b,b+1));
         f.push_back(Tupla3i(a,b+1,a+1));
      }
   }
}
