#ifndef CIL_H_INCLUDED
#define CIL_H_INCLUDED

#include "aux.h"

class Cilindro: public ObjRevolucion
{
   public:
   Cilindro(  const int num_instancias_perf,
              const float altura,
              const float radio,
              bool tapa_sup=true, bool tapa_inf=true);

   private:
      void GenerarPerfil(const float altura, const float radio);
} ;




#endif
