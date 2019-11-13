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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, int mult, eje eje_rotacion, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo, v, mult);
   if(perfilInverso(v)){
      invertirPerfil();
   }

   quitarPolos();

   vertices_perfil = v.size();
   instancias = num_instancias;
   tapaSup = !tapa_sup;
   tapaInf = !tapa_inf;

   crearMalla(v, eje_rotacion);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, eje eje_rotacion, bool tapa_sup, bool tapa_inf) {
   v = archivo;
   if(perfilInverso(v)){
      invertirPerfil();
   }

   quitarPolos();

   vertices_perfil = v.size();
   instancias = num_instancias;
   tapaSup = !tapa_sup;
   tapaInf = !tapa_inf;

   crearMalla(v, eje_rotacion);

}

bool ObjRevolucion::perfilInverso(std::vector<Tupla3f> archivo){
   if(v.front()(1) < v.back()(1)){
      return false;
   }
   return true;
}

void ObjRevolucion::invertirPerfil(){
   std::vector<Tupla3f> aux(v.rbegin(),v.rend());
   v = aux;
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, eje eje_rotacion) {
   float alfa, coor_x, coor_y, coor_z;
   int a, b;
   int num_vertices = perfil_original.size();
   for(int i = 1; i < instancias; i++){
      alfa = ((2*M_PI*i)/instancias);
      for(int j = 0; j < num_vertices; j++){
         switch (eje_rotacion) {
            case RY:
               coor_x = perfil_original[j](0) * cos(alfa) + perfil_original[j](2) * sin(alfa);
               coor_z = perfil_original[j](0)* -1 * sin(alfa) + perfil_original[j](2) * cos(alfa);
               v.push_back({coor_x, perfil_original[j](1), coor_z});
               break;
            case RX:
               coor_y = perfil_original[j](1) * cos(alfa) - perfil_original[j](2) * sin(alfa);
               coor_z = perfil_original[j](1) * sin(alfa) + perfil_original[j](2) * cos(alfa);
               v.push_back({perfil_original[j](0), coor_y, coor_z});
               break;
            case RZ:
               coor_x = perfil_original[j](0) * cos(alfa) - perfil_original[j](1) * sin(alfa);
               coor_y = perfil_original[j](0) * sin(alfa) + perfil_original[j](1) * cos(alfa);
               v.push_back({coor_x, coor_y, perfil_original[j](2)});
               break;
         }
      }
   }
   for(int i = 0; i < instancias; i++){
      for(int j = 0; j < num_vertices-1; j++){
         a = num_vertices*i + j;
         b = num_vertices*((i+1)%instancias)+j;
         f.push_back(Tupla3i(a,b,b+1));
         f.push_back(Tupla3i(a,b+1,a+1));
      }
   }

   coor_y = v.back()(1);
   v.push_back({0,coor_y,0}); //Añado polo superior
   coor_y = v.front()(1);
   v.push_back({0,coor_y,0}); //Añado polo inferior

   ponTapaSup();
   ponTapaInf();

}

void ObjRevolucion::quitarPolos(){
   if(v.front()(0) == 0.0 && v.front()(2) == 0.0){
         v.erase(v.begin());
   }
   if(v.back()(0) == 0.0 && v.back()(2) == 0.0){
      v.pop_back();
   }
}

void ObjRevolucion::ponTapaSup(){
   if(!tapaSup){
      std::vector<Tupla3i>::iterator cara = f.begin();
      for(int i = 0; i < instancias*(vertices_perfil-1)*2; i++){
         ++cara;
      }
      for(int i = 1; i <= instancias; i++){
         Tupla3i aux(i*vertices_perfil-1, ((i+1)*vertices_perfil-1)%(v.size()-2), v.size()-2);
         cara = f.insert(cara,aux);
      }
      tapaSup = true;
   }
}

void ObjRevolucion::quitTapaSup(){
   if(tapaSup){
      std::vector<Tupla3i>::iterator cara = f.begin();
      for(int i = 0; i < instancias*(vertices_perfil-1)*2; i++){
         ++cara;
      }
      for(int j = 0; j < instancias; j++){
         cara = f.erase(cara);
      }
      tapaSup = false;
   }
}

void ObjRevolucion::ponTapaInf(){
   if(!tapaInf){
      for(int i = 0; i < instancias; i++){
         Tupla3i aux(v.size()-1, ((i+1)%instancias)*vertices_perfil, i*vertices_perfil);
         f.push_back(aux);
      }
      tapaInf = true;
   }
}

void ObjRevolucion::quitTapaInf(){
   if(tapaInf){
      for(int i = 0; i < instancias; i++){
         f.pop_back();
      }
      tapaInf = false;
   }
}

void ObjRevolucion::tapaSuperior(){
   if(tapaSup){
      quitTapaSup();
   }
   else{
      ponTapaSup();
   }
}

void ObjRevolucion::tapaInferior(){
   if(tapaInf){
      quitTapaInf();
   }
   else{
      ponTapaInf();
   }
}
