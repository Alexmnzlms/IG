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
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
typedef enum {INMED, DIFER, CHESS, SMUZ, PLAIN} dibujo;
typedef enum {BLANCO, NEGRO, AZUL, VERDE, CIAN, NARANJA, ROSA, AMARILLO, MORADO, SEL} color;

class Malla3D{
public:
   Malla3D();

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool iluminacion, bool suave);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   void draw_ModoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(dibujo tipo, color col, GLenum modo) ;
   void alternar_vista();
   void setMaterial(Material mat);
   virtual void setTextura(const std::string tex);
   void setColorSeleccion(color col);

protected:
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );
   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)
   void calcular_colores();
   virtual void dibujaInmediato(int tamanio, const void * indice);
   virtual void dibujaAjedrez(int tamanio, const void * indice1, const void * indice2);
   virtual void dibujaDiferido(int tamanio,  GLvoid * indice);
   dibujo tipo_draw;
   bool ver = true;
   GLuint id_vbo_ver = 0, id_vbo_tri = 0;
   Material m;
   Textura * textura = nullptr;
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv ;

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> c ;
   std::vector<Tupla3f> c_aux;
   std::vector<Tupla3f> c_seleccion;
   Tupla3f cnegro;
   Tupla3f cazul;
   Tupla3f cverde;
   Tupla3f ccian;
   Tupla3f cnaranja;
   Tupla3f crosa;
   Tupla3f camarillo;
   Tupla3f cmorado;
   Tupla3f cblanco;
   std::vector<Tupla2f> ct;
   //float colorArray[8];
} ;


#endif
