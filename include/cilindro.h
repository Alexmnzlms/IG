#ifndef CIL_H_INCLUDED
#define CIL_H_INCLUDED

#include "aux.h"

class Cilindro: public ObjRevolucion{
public:
   Cilindro(const float altura, const float radio);

private:
   void GenerarPerfil(const float altura, const float radio);
};

#endif
