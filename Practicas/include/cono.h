#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"

class Cono: public ObjRevolucion
{
   public:
   Cono(    const int num_instancias_perf,
            const float altura,
            const float radio,
            bool tapa_inf=true);
} ;




#endif
