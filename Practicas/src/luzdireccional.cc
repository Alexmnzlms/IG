#include "aux.h"
#include "luz.h"
#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional(const Tupla2f & orientacion, GLenum idLuzOpenGL, Tupla4f colorA, Tupla4f colorD,Tupla4f colorE){
   id = idLuzOpenGL;
   colorAmbiente = colorA;
   colorDifuso = colorD;
   colorEspecular = colorE;

   float x, y, z;
   alpha = orientacion(0)*M_PI/180.0;
   beta = orientacion(1)*M_PI/180.0;
   x = sin(alpha)*cos(beta);
   y = cos(alpha)*sin(beta);
   z = cos(beta);
   posicion = {x,y,z,0.0};
   std::cout << "Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
   for(float i = 0.0; i <= 180.0; i +=90.0){
      for(float j = 0.0; j <=180.0; j+=90.0){
         float rad_a = i*M_PI/180.0;
         float rad_b = j*M_PI/180.0;
         x = sin(rad_a)*cos(rad_b);
         y = cos(rad_a)*sin(rad_b);
         z = cos(rad_b);
         if(x < 0.0000){
            x = 0;
         }
         if(y < 0.0000){
            y = 0;
         }
         if(z < 0.0000){
            z = 0;
         }
         std::cout << "Angulos: " << i << ", " << j << " Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
      }
   }
}

void LuzDireccional::variarAnguloAlpha( float incremento ){
   alpha = (alpha + incremento*M_PI/180);
   if(alpha > M_PI){
      alpha = 0;
   } else if(alpha < 0){
      alpha = M_PI;
   }
   float x, y, z;
   x = sin(alpha)*cos(beta);
   y = cos(alpha)*sin(beta);
   z = cos(beta);
   posicion = {x,y,z,0.0};
   std::cout << "Alpha: " << alpha*180/M_PI << std::endl;
   std::cout << "Beta: " << beta*180/M_PI << std::endl;
   std::cout << "Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
}
void LuzDireccional::variarAnguloBeta( float incremento ){
   beta = (beta + incremento*M_PI/180);
   if(beta > M_PI){
      beta = -M_PI;
   } else if(beta < -M_PI){
      beta = M_PI;
   }
   float x, y, z;
   x = sin(alpha)*cos(beta);
   y = cos(alpha)*sin(beta);
   z = cos(beta);
   posicion = {x,y,z,0.0};
   std::cout << "Alpha: " << alpha*180/M_PI << std::endl;
   std::cout << "Beta: " << beta*180/M_PI << std::endl;
   std::cout << "Posicion direccional: " << x << ", " << y << ", " << z << std::endl;
}
