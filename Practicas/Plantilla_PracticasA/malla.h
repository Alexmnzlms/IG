// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
typedef enum {INMED, DIFER, CHEST} dibujo;
class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   void draw_ModoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw() ;

   void cambiar_modo(GLenum) ;
   void cambiar_draw(dibujo);
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   GLenum modo_dibujado;
   bool ajedrez;
   dibujo tipo_draw;
   GLuint id_vbo_ver = 0, id_vbo_tri = 0;
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f1;
   std::vector<Tupla3i> f2;

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> c ;
   std::vector<Tupla3f> c_aux;
   //float colorArray[8];
} ;


#endif
