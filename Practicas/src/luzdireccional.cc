#include "aux.h"
#include "luz.h"
#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional(const Tupla3f & direccion, GLenum idLuzOpenGL, Tupla4f colorA, Tupla4f colorD,Tupla4f colorE){
   id = idLuzOpenGL;
   colorAmbiente = colorA;
   colorDifuso = colorD;
   colorEspecular = colorE;
   alpha = atan((sqrt(pow(direccion(0),2) + pow(direccion(1),2))) / direccion(2));
   beta = atan(direccion(1)/direccion(0));
   posicion = {direccion(0),direccion(1),direccion(2),0.0};
   posicion_original = posicion;
   activada = false;
   std::cout << "Alpha: " << alpha*180.0/M_PI << std::endl;
   std::cout << "Beta: " << beta*180.0/M_PI << std::endl;
   std::cout << "Posicion direccional: " << direccion(0) << ", " << direccion(1) << ", " << direccion(2) << std::endl;
}

void LuzDireccional::variarAnguloAlpha( float incremento ){
   alpha = fmod((alpha + incremento*M_PI/180.0),2*M_PI);
   if(alpha < 0.0){
      alpha = 2*M_PI;
   }
   float x, y, z;
   x = sin(alpha)*cos(beta)*sqrt(posicion_original.lengthSq());
   y = sin(alpha)*sin(beta)*sqrt(posicion_original.lengthSq());
   z = cos(alpha)*sqrt(posicion_original.lengthSq());
   posicion = {x,y,z,0.0};
   glLightfv(id, GL_POSITION, posicion);
   std::cout << "Alpha: " << alpha*180.0/M_PI << std::endl;
   std::cout << "Beta: " << beta*180.0/M_PI << std::endl;
   std::cout << "Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
}
void LuzDireccional::variarAnguloBeta( float incremento ){
   beta = beta + incremento*M_PI/180.0;
   if(beta > M_PI/2){
      beta = -M_PI/2;
   } else if(beta < -M_PI/2){
      beta = M_PI/2;
   }
   float x, y, z;
   x = sin(alpha)*cos(beta)*sqrt(posicion_original.lengthSq());
   y = sin(alpha)*sin(beta)*sqrt(posicion_original.lengthSq());
   z = cos(alpha)*sqrt(posicion_original.lengthSq());
   posicion = {x,y,z,0.0};
   glLightfv(id, GL_POSITION, posicion);
   std::cout << "Alpha: " << alpha*180.0/M_PI << std::endl;
   std::cout << "Beta: " << beta*180.0/M_PI << std::endl;
   std::cout << "Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
}
