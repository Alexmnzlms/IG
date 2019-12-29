#include "aux.h"
#include "textura.h"
#include "jpg_imagen.h"

using namespace jpg;

Textura::Textura(string archivo){
   glGenTextures(1, &textura_id);
   glBindTexture( GL_TEXTURE_2D, textura_id);

   Imagen * pimg = nullptr;
   pimg = new Imagen(archivo);
   width = pimg->tamX();
   height = pimg->tamY();
   data = pimg->leerPixels();
}

void Textura::activar(){
   //glEnable(GL_TEXTURE_2D);
   gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
   //glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
   //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
