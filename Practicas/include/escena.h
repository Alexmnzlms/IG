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
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "material.h"

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
   bool iluminacion = true;
   malla objMalla;
   color col;
   GLenum modo_dibujado = GL_FILL;
   dibujo tipo_draw = SMUZ;
   dibujo anterior_tipo = tipo_draw;
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
   //Luces de la escena
   LuzDireccional * luzdir = nullptr;
   LuzDireccional * luzdir2 = nullptr;
   LuzPosicional * luzpos = nullptr;
   LuzPosicional * luzpos2 = nullptr;
   //Materiales de la escena
   Tupla4f colambesmeralda = {0.0215,0.1745,0.0215,1.0};
   Tupla4f coldifesmeralda = {0.07568,0.61424,0.07568,1.0};
   Tupla4f colespesmeralda = {0.633,0.727811,0.07568,1.0};
   float brilloesmeralda = 0.6*128.0;

   Tupla4f colambrubi = {0.1745, 0.01175, 0.01175,1.0};
   Tupla4f coldifrubi = { 0.61424, 0.04136, 0.04136,1.0};
   Tupla4f colesprubi = {0.727811,0.626959,0.626959,1.0};
   float brillorubi = 0.6*128.0;

   Tupla4f colambnegro = {0.0, 0.0, 0.0,1.0};
   Tupla4f coldifnegro = { 0.0, 0.0, 0.0,1.0};
   Tupla4f colespnegro = {1.0,1.0,1.0,1.0};
   float brillonegro = 0.05*128.0;

   Tupla4f colambblanco = {1.0, 1.0, 1.0,1.0};
   Tupla4f coldifblanco = { 1.0, 1.0, 1.0,1.0};
   Tupla4f colespblanco = {0.0,0.0,0.0,1.0};
   float brilloblanco = 128.0;

   Material * esmeralda = nullptr;
   Material * rubi = nullptr;
   Material * negro = nullptr;
   Material * blanco = nullptr;



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
