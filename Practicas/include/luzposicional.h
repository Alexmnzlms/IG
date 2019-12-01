#ifndef LUZP_H_INCLUDED
#define LUZP_H_INCLUDED

class LuzPosicional : public Luz
{
   public:
      LuzPosicional( const Tupla3f & posicion,
                     GLenum idLuzOpenGL,Tupla4f colorAmbiente,
                     Tupla4f colorDifuso,Tupla4f colorEspecular ) ;
};

#endif
