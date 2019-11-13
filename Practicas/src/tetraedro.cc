#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   // inicializar la tabla de vértices
   Tupla3f v0(-lado,-lado,-lado);
   v.push_back(v0);
   Tupla3f v1(0,-lado,lado);
   v.push_back(v1);
   Tupla3f v2(lado,-lado,-lado);
   v.push_back(v2);
   Tupla3f v3(0,lado,0);
   v.push_back(v3);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   Tupla3i c1(0,1,3);
   f.push_back(c1);
   Tupla3i c2(1,2,3);
   f.push_back(c2);
   Tupla3i c3(2,0,3);
   f.push_back(c3);
   Tupla3i c4(0,2,1);
   f.push_back(c4);
}
