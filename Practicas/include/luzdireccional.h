#ifndef LUZD_H_INCLUDED
#define LUZD_H_INCLUDED

class LuzDireccional : public Luz
{
   protected:
      float alpha;
      float beta;
   public:
   //inicializar la fuente de luz
      LuzDireccional(const Tupla2f & orientacion,
                     GLenum idLuzOpenGL,Tupla4f colorA,
                     Tupla4f colorD,Tupla4f colorE) ;
   //Cambiar ángulo:
      void variarAnguloAlpha( float incremento ) ;
      void variarAnguloBeta( float incremento ) ;
};


#endif
