#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include <vector>

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   Tupla3f v0(-lado,-lado,-lado);
   v.push_back(v0);
   Tupla3f v1(-lado,-lado,lado);
   v.push_back(v1);
   Tupla3f v2(-lado,lado,-lado);
   v.push_back(v2);
   Tupla3f v3(-lado,lado,lado);
   v.push_back(v3);
   Tupla3f v4(lado,-lado,-lado);
   v.push_back(v4);
   Tupla3f v5(lado,-lado,lado);
   v.push_back(v5);
   Tupla3f v6(lado,lado,-lado);
   v.push_back(v6);
   Tupla3f v7(lado,lado,lado);
   v.push_back(v7);


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   Tupla3i c1(0,4,1);
   f.push_back(c1);
   Tupla3i c2(1,4,5);
   f.push_back(c2);
   Tupla3i c3(1,5,3);
   f.push_back(c3);
   Tupla3i c4(3,5,7);
   f.push_back(c4);
   Tupla3i c5(0,1,3);
   f.push_back(c5);
   Tupla3i c6(0,3,2);
   f.push_back(c6);
   Tupla3i c7(0,2,6);
   f.push_back(c7);
   Tupla3i c8(0,6,4);
   f.push_back(c8);
   Tupla3i c9(4,6,5);
   f.push_back(c9);
   Tupla3i c10(5,6,7);
   f.push_back(c10);
   Tupla3i c11(2,7,6);
   f.push_back(c11);
   Tupla3i c12(2,3,7);
   f.push_back(c12);

   Tupla3f rgb0(255,0,0);
   c.push_back(rgb0);
   Tupla3f rgb1(0,0,255);
   c.push_back(rgb1);
   Tupla3f rgb2(255,0,0);
   c.push_back(rgb2);
   Tupla3f rgb3(0,0,255);
   c.push_back(rgb3);
   Tupla3f rgb4(255,0,0);
   c.push_back(rgb4);
   Tupla3f rgb5(0,0,255);
   c.push_back(rgb5);
   Tupla3f rgb6(255,0,0);
   c.push_back(rgb6);
   Tupla3f rgb7(0,0,255);
   c.push_back(rgb7);

}
