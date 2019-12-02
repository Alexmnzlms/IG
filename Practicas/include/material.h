#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED


class Material {
   private:
      Tupla4f difuso;
      Tupla4f especular;
      Tupla4f ambiente;
      float brillo;
   public:
      Material ();
      Material (Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brill);
      void aplicar();
};

#endif
