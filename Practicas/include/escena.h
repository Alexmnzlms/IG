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
#include "robot.h"
#include "torre.h"
#include "cuadro.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, ILUMINACION, SELANGULO, ANIMA, GRADOLIB} menu;
typedef enum {CUBO, TETRAEDRO, PLY, ROT, CON, ESF, CIL, MULT} malla;
typedef enum {ALFA, BETA} angulo;
typedef enum {CODOI, CODOD, PIERNAS, TALADROI, TALADROD, ANTENA} grado_libertad;
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
   bool iluminacion = false;
   bool bool_dibujado[3] = {false, false, true};
   bool actluzdir = false;
   bool actluzpos = false;
   angulo ang;
   grado_libertad gl;
   color col;
   float vel = 1.0;
   float taladro = 10.0;
   GLenum modo_dibujado;
   dibujo tipo_draw = INMED;
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
   Torre * torre = nullptr;
   Robot * robot = nullptr;
   Cuadro * cuadro = nullptr;


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
   Tupla4f coldifnegro = { 0.01, 0.01, 0.01,1.0};
   Tupla4f colespnegro = {0.5,0.5,0.5,0.5};
   float brillonegro = 0.25*128.0;

   Tupla4f colambblanco = {0.0, 0.0, 0.0,1.0};
   Tupla4f coldifblanco = { 0.55, 0.55, 0.55,1.0};
   Tupla4f colespblanco = {0.7,0.7,0.7,1.0};
   float brilloblanco = 0.25*128.0;

   Tupla4f colambperla = {0.25, 0.20725, 0.20725,1.0};
   Tupla4f coldifperla = { 1.0, 0.829, 0.829,1.0};
   Tupla4f colespperla = {0.296648,0.296648,0.296648,1.0};
   float brilloperla = 0.088*128.0;

   Tupla4f colambbronce = {0.2125, 0.1275, 0.054,1.0};
   Tupla4f coldifbronce = { 0.714, 0.4284, 0.18144,1.0};
   Tupla4f colespbronce = {0.393548,0.271906,0.166721,1.0};
   float brillobronce = 0.2*128.0;

   Material * esmeralda = nullptr;
   Material * rubi = nullptr;
   Material * negro = nullptr;
   Material * blanco = nullptr;
   Material * perla = nullptr;
   Material * bronce = nullptr;
   Material * blancop = nullptr;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
   void animarModeloJerarquico();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
