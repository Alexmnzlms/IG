#include "aux.h"
#include "malla.h"
#include "cuadro.h"
#include <vector>

Cuadro::Cuadro(float lado)
{
   lado = lado / 2.0;
   // inicializar la tabla de vértices
   Tupla3f v0(-lado,-lado,0);
   v.push_back(v0);
   Tupla3f v1(-lado,lado,0);
   v.push_back(v1);
   Tupla3f v2(lado,lado,0);
   v.push_back(v2);
   Tupla3f v3(lado,-lado,0);
   v.push_back(v3);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   Tupla3i c1(0,3,1);
   f.push_back(c1);
   Tupla3i c2(3,2,1);
   f.push_back(c2);

   calcular_colores();
   calcular_normales();

   Tupla2f t1(0.0,0.0);
   Tupla2f t2(0.0,1.0);
   Tupla2f t3(1.0,1.0);
   Tupla2f t4(1.0,0.0);
   ct.push_back(t2);
   ct.push_back(t1);
   ct.push_back(t4);
   ct.push_back(t3);
   //textura = new Textura("jpg/gato.jpg");
}
