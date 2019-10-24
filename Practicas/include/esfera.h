#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"

class Esfera : public ObjRevolucion
{
   public:
   Esfera( const int num_vert_perfil,
            const int num_instancias_perf,
            const float radio );

   private:
      void GenerarPerfil(const int num_vert_perfil, const float radio);
} ;




#endif
