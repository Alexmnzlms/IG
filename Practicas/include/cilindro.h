#ifndef CIL_H_INCLUDED
#define CIL_H_INCLUDED

#include "aux.h"

class Cilindro: public ObjRevolucion
{
   public:
   Cilindro( const int num_vert_perfil,
            const int num_instancias_perf,
            const float altura,
            const float radio );

   private:
      void GenerarPerfil(const int num_vert_perfil, const float altura, const float radio);
} ;




#endif
