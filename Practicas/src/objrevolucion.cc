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

ObjRevolucion::ObjRevolucion(const std::string & archivo) {
   ply::read_vertices(archivo, v, 1);
   vertices_perfil = v.size();
   instancias = 20;
   crearMalla(v, RY);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo) {
   vertices_perfil = v.size();
   instancias = 20;
   crearMalla(archivo, RY);
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

void ObjRevolucion::crearMalla(std::vector<Tupla3f> &perfil_original, eje eje_rotacion) {
   float alfa, coor_x, coor_y, coor_z;
   int a, b;
   int num_vertices = perfil_original.size();
   Tupla3f polo;
   tapa = true;

   if(perfilInverso(perfil_original)){
      invertirPerfil();
   }

   if(num_vertices == 2 && perfil_original[num_vertices-1](0) == 0.0 && perfil_original[num_vertices-1](2) == 0.0 ){
      polo = perfil_original[num_vertices-1];
      perfil_original.pop_back();
      num_vertices--;
   }

   quitarPolos(perfil_original);

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
   if(!(num_vertices == 1 && polo(0) == 0.0 && polo(2) == 0.0 )){
      for(int i = 0; i < instancias; i++){
         for(int j = 0; j < num_vertices-1; j++){
            a = num_vertices*i + j;
            b = num_vertices*((i+1)%instancias)+j;
            f.push_back(Tupla3i(a,b,b+1));
            f.push_back(Tupla3i(a,b+1,a+1));
         }
      }
   }
   if(num_vertices == 1 && polo(0) == 0.0 && polo(2) == 0.0 ){
      v.push_back(polo);
   } else {
      coor_y = v.back()(1);
      v.push_back({0,coor_y,0}); //Añado polo superior
   }
   coor_y = v.front()(1);
   v.push_back({0,coor_y,0}); //Añado polo inferior

   for(int i = 1; i <= instancias; i++){
      Tupla3i aux(i*num_vertices-1, ((i+1)*num_vertices-1)%(v.size()-2), v.size()-2);
      f.push_back(aux);
   }
   for(int i = 0; i < instancias; i++){
      Tupla3i aux(v.size()-1, ((i+1)%instancias)*num_vertices, i*num_vertices);
      f.push_back(aux);
   }

   pos_tapas = instancias;
   calcular_colores();
   calcular_normales();
}

void ObjRevolucion::quitarPolos(std::vector<Tupla3f> &perfil_original){
   if(perfil_original.front()(0) == 0.0 && perfil_original.front()(2) == 0.0){
         perfil_original.erase(perfil_original.begin());
   }
   if(perfil_original.back()(0) == 0.0 && perfil_original.back()(2) == 0.0){
      perfil_original.pop_back();
   }
}

void ObjRevolucion::dibujaInmediato(int tamanio, const void * indice){
   if(!tapa){
      glDrawElements( GL_TRIANGLES, (tamanio - 2*pos_tapas)*3, GL_UNSIGNED_INT, indice);
   } else {
      glDrawElements( GL_TRIANGLES, (tamanio)*3, GL_UNSIGNED_INT, indice);
   }
}

void ObjRevolucion::dibujaDiferido(int tamanio, GLvoid * indice){
   if(!tapa){
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*(tamanio-2*pos_tapas) * sizeof(int), indice);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
      glDrawElements( GL_TRIANGLES, (tamanio-pos_tapas)*3, GL_UNSIGNED_INT, 0);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
   } else {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*tamanio * sizeof(int), indice);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
      glDrawElements( GL_TRIANGLES, tamanio*3, GL_UNSIGNED_INT, 0);
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
   }
}

void ObjRevolucion::dibujaAjedrez(int tamanio, const void * indice1, const void * indice2){
   if(!tapa){
      glColorPointer(3, GL_FLOAT, 0, c.data() );
      glDrawElements( GL_TRIANGLES, (tamanio/2 - pos_tapas)*3, GL_UNSIGNED_INT,indice1);
      glColorPointer(3, GL_FLOAT, 0, c_aux.data() );
      glDrawElements( GL_TRIANGLES, (tamanio/2 - pos_tapas)*3, GL_UNSIGNED_INT,indice2);
   } else {
      glColorPointer(3, GL_FLOAT, 0, c.data() );
      glDrawElements( GL_TRIANGLES, (tamanio/2)*3, GL_UNSIGNED_INT,indice1);
      glColorPointer(3, GL_FLOAT, 0, c_aux.data() );
      glDrawElements( GL_TRIANGLES, (tamanio/2)*3, GL_UNSIGNED_INT,indice2);
   }
}

void ObjRevolucion::tapas(){
   tapa = !tapa;
}
