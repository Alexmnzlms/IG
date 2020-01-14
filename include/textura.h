#ifndef TEX_H_INCLUDED
#define TEX_H_INCLUDED

#include <string>
#include <vector>

class Textura {
private:
   GLuint textura_id;
   unsigned char * data;
   int width;
   int height;
   bool generada;
   
public:
   Textura(std::string archivo);
   void activar();
};

#endif
