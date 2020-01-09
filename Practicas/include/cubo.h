#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "aux.h"

class Cubo : public Malla3D{
public:
   Cubo(float l=1) ;
   void setTextura(const std::string tex);
};

#endif
