#ifndef TEX_H_INCLUDED
#define TEX_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Textura {
   private:
      GLuint textura_id;
      unsigned char * data;
      int width;
      int height;
   public:
      Textura(string archivo);
      void activar();
};

#endif
