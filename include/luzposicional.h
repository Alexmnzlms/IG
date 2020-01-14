#ifndef LUZP_H_INCLUDED
#define LUZP_H_INCLUDED

class LuzPosicional : public Luz{
public:
   LuzPosicional( const Tupla3f & pos,GLenum idLuzOpenGL,
                  Tupla4f colorA,Tupla4f colorD,Tupla4f colorE) ;
};

#endif
