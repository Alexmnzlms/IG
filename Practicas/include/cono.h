#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"

class Cono: public ObjRevolucion
{
   public:
   Cono( const int num_vert_perfil,
            const int num_instancias_perf,
            const float altura,
            const float radio );

   private:
      void GenerarPerfil(const int num_vert_perfil, const float altura, const float radio);
} ;




#endif
