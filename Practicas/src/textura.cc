#include "aux.h"
#include "textura.h"
#include "jpg_imagen.h"

using namespace jpg;

Textura::Textura(string archivo){
   generada = false;

   Imagen * pimg = nullptr;
   pimg = new Imagen(archivo);
   width = pimg->tamX();
   height = pimg->tamY();
   data = pimg->leerPixels();
}

void Textura::activar(){
   if (!generada) {
      glGenTextures(1, &textura_id);
      glBindTexture( GL_TEXTURE_2D, textura_id);
      gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
      generada = true;
   }
   glBindTexture( GL_TEXTURE_2D, textura_id);
}
