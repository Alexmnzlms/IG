#include "aux.h"
#include "malla.h"
#include "cubo.h"
#include <vector>

Cubo::Cubo(float lado)
{
   lado = lado / 2.0;
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
   Tupla3f v8(-lado,-lado,-lado);
   v.push_back(v8);
   Tupla3f v9(-lado,-lado,lado);
   v.push_back(v9);
   Tupla3f v10(-lado,lado,-lado);
   v.push_back(v10);
   Tupla3f v11(-lado,lado,lado);
   v.push_back(v11);
   Tupla3f v12(lado,-lado,-lado);
   v.push_back(v12);
   Tupla3f v13(lado,-lado,lado);
   v.push_back(v13);
   Tupla3f v14(lado,lado,-lado);
   v.push_back(v14);
   Tupla3f v15(lado,lado,lado);
   v.push_back(v15);
   Tupla3f v16(-lado,-lado,-lado);
   v.push_back(v16);
   Tupla3f v17(-lado,-lado,lado);
   v.push_back(v17);
   Tupla3f v18(-lado,lado,-lado);
   v.push_back(v18);
   Tupla3f v19(-lado,lado,lado);
   v.push_back(v19);
   Tupla3f v20(lado,-lado,-lado);
   v.push_back(v20);
   Tupla3f v21(lado,-lado,lado);
   v.push_back(v21);
   Tupla3f v22(lado,lado,-lado);
   v.push_back(v22);
   Tupla3f v23(lado,lado,lado);
   v.push_back(v23);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   Tupla3i c1(3,5,7);
   f.push_back(c1);
   Tupla3i c2(3,1,5);
   f.push_back(c2);
   Tupla3i c3(9,11,10);
   f.push_back(c3);
   Tupla3i c4(8,9,10);
   f.push_back(c4);
   Tupla3i c5(12,14,15);
   f.push_back(c5);
   Tupla3i c6(12,15,13);
   f.push_back(c6);
   Tupla3i c7(0,2,6);
   f.push_back(c7);
   Tupla3i c8(0,6,4);
   f.push_back(c8);
   Tupla3i c9(18,23,22);
   f.push_back(c9);
   Tupla3i c10(18,19,23);
   f.push_back(c10);
   Tupla3i c11(17,20,21);
   f.push_back(c11);
   Tupla3i c12(16,20,17);
   f.push_back(c12);

   calcular_colores();
   calcular_normales();
}

void Cubo::setTextura(const std::string tex){
   textura = new Textura(tex);
   ct.push_back({1.0,1.0});
   ct.push_back({0.0,1.0});
   ct.push_back({1.0,0.0});
   ct.push_back({0.0,0.0});
   ct.push_back({0.0,1.0});
   ct.push_back({1.0,1.0});
   ct.push_back({0.0,0.0});
   ct.push_back({1.0,0.0});

   ct.push_back({0.0,1.0});
   ct.push_back({1.0,1.0});
   ct.push_back({0.0,0.0});
   ct.push_back({1.0,0.0});
   ct.push_back({1.0,1.0});
   ct.push_back({0.0,1.0});
   ct.push_back({1.0,0.0});
   ct.push_back({0.0,0.0});

   ct.push_back({0.0,1.0});
   ct.push_back({0.0,0.0});
   ct.push_back({0.0,0.0});
   ct.push_back({0.0,1.0});
   ct.push_back({1.0,1.0});
   ct.push_back({1.0,0.0});
   ct.push_back({1.0,0.0});
   ct.push_back({1.0,1.0});
}
