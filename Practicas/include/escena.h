#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cono.h"
#include "cilindro.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
typedef enum {CUBO, TETRAEDRO, PLY, ROT, CON, ESF, CIL, MULT} malla;
class Escena
{

   private:



 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   void clear_window();

   menu modoMenu=NADA;
   bool quitar_superior = false;
   bool quitar_inferior = false;
   malla objMalla;
   color col = VERDE;
   GLenum modo_dibujado = GL_FILL;
   dibujo tipo_draw = CHESS;
   std::string ply = "ply/ant.ply";
   std::string plyrot = "ply/peon.ply";
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * objply = nullptr ;
   ObjRevolucion * objrot = nullptr;
   Esfera * esfera = nullptr;
   Cono * cono = nullptr;
   Cilindro * cilindro = nullptr;


   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
