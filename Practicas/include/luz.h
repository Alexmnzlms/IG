#ifndef LUZPOS_H_INCLUDED
#define LUZPOS_H_INCLUDED


class Luz {
   protected:
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;
   public:
      Luz();
      void activar();
};

#endif
