#include "aux.h"
#include "textura.h"
#include "jpg_imagen.h"

using namespace jpg;

Textura::Textura(string archivo){
   glGenTextures(1, &textura_id);

   Imagen * pimg = nullptr;
   pimg = new Imagen(archivo);
   unsigned tamx = pimg->tamX();
   unsigned tamy = pimg->tamY();
   unsigned char * texels = pimg->leerPixels();
}

void Textura::activar(){
   glBindTexture( GL_TEXTURE_2D, textura_id);
   gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tamx, tamy, GL_RGB,
   GL_UNSIGNED_BYTE, texels);
}
