#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include <vector>

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   Tupla3f v0(0,0,0);
   v.push_back(v0);
   Tupla3f v1(0,0,lado);
   v.push_back(v1);
   Tupla3f v2(0,lado,0);
   v.push_back(v2);
   Tupla3f v3(0,lado,lado);
   v.push_back(v3);
   Tupla3f v4(lado,0,0);
   v.push_back(v4);
   Tupla3f v5(lado,0,lado);
   v.push_back(v5);
   Tupla3f v6(lado,lado,0);
   v.push_back(v6);
   Tupla3f v7(lado,lado,lado);
   v.push_back(v7);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   Tupla3i c1(3,5,7);
   f.push_back(c1);
   Tupla3i c2(3,1,5);
   f.push_back(c2);
   Tupla3i c3(1,3,2);
   f.push_back(c3);
   Tupla3i c4(0,1,2);
   f.push_back(c4);
   Tupla3i c5(4,6,7);
   f.push_back(c5);
   Tupla3i c6(4,7,5);
   f.push_back(c6);
   Tupla3i c7(0,2,6);
   f.push_back(c7);
   Tupla3i c8(0,6,4);
   f.push_back(c8);
   Tupla3i c9(2,7,6);
   f.push_back(c9);
   Tupla3i c10(2,3,7);
   f.push_back(c10);
   Tupla3i c11(1,4,5);
   f.push_back(c11);
   Tupla3i c12(0,4,1);
   f.push_back(c12);

   calcular_colores();

}
