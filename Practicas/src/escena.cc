

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   int num_vert = 10;
   int num_rot = 20;
   cubo = new Cubo(75);
   tetraedro = new Tetraedro(75);
   objply = new ObjPLY(ply,1);
   objrot = new ObjRevolucion(plyrot, num_rot, 1, RY, true, true);
   esfera = new Esfera(num_vert, num_rot, 50, true, true);
   cono = new Cono(num_rot, 50, 50, true);
   cilindro = new Cilindro(num_rot, 50, 50, true, true);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
   using namespace std;

	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable( GL_CULL_FACE );

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   cout << "----------------------------------------------------------" << endl;
   cout << "Tetraedro -> Visualización modo solido, dibujado modo inmediato" << endl;
   cout << "Cono -> Visualización modo solido, dibujado modo diferido" << endl;
   cout << "Objeto ply de revolución -> Modo ajedrez" << endl;
   cout << "Objeto ply -> Visualización modo puntos, dibujado modo diferido" << endl;
   cout << "Esfera -> Visualización modo puntos, dibujado modo inmediato" << endl;
   cout << "Cubo -> Visualización modo lineas, dibujado modo diferido" << endl;
   cout << "Cilindro -> Visualización modo lineas, dibujado modo inmediato" << endl;
   cout << "----------------------------------------------------------" << endl;
   cout << "Seleccione menu" << endl;
   cout << "O: Seleccion de objeto" << endl;
   cout << "V: seleccion de visualizacion" << endl;
   cout << "D: seleccion de dibujado" << endl;
   cout << "Q: salir" << endl;
   cout << endl;
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{

   change_observer();
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glDisable(GL_LIGHTING);
   ejes.draw();
   glPushMatrix();
      glPushMatrix();
         glTranslatef(150,0,0);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         cilindro->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-150,0,0);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         cono->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,50,-140);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         esfera->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,40,100);
         glScalef(30,30,30);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         objrot->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(100,0,100);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         cubo->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-125,45,150);
         glScalef(0.60,0.60,0.60);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         tetraedro->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glScalef(5,5,5);
         glTranslatef(0,10,0);
         glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
         objply->draw(tipo_draw, col);
      glPopMatrix();
   glPopMatrix();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            cout << "Seleccione menu" << endl;
            cout << "O: Seleccion de objeto" << endl;
            cout << "V: seleccion de visualizacion" << endl;
            cout << "D: seleccion de dibujado" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            modoMenu=NADA;
          }
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout << "Seleccione objeto" << endl;
         cout << "C: Cubo" << endl;
         cout << "T: Tetraedro" << endl;
         cout << "Y: Archivo PLY" << endl;
         cout << "R: Archivo PLY rotacion" << endl;
         cout << "E: Esfera" << endl;
         cout << "3: Cono" << endl;
         cout << "4: Cilindro" << endl;
         cout << "M: Escena Multiple" << endl;
         cout << "Q: salir" << endl;
         cout << endl;
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Seleccione modo de visualización" << endl;
         cout << "P: Modo punto" << endl;
         cout << "L: Modo linea" << endl;
         cout << "S: Modo Solido" << endl;
         cout << "A: Modo ajedrez" << endl;
         cout << "Q: salir" << endl;
         cout << endl;
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Seleccione modo de visualización" << endl;
         cout << "1: Modo inmediato" << endl;
         cout << "2: Modo diferido" << endl;
         cout << "Q: salir" << endl;
         cout << endl;
         break ;
       case 'P':
          if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado visualización de punto" << endl;
            cout << "P: Modo punto" << endl;
            cout << "L: Modo linea" << endl;
            cout << "S: Modo Solido" << endl;
            cout << "A: Modo ajedrez" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            modo_dibujado = GL_POINT;
            if(tipo_draw == INMED){
               col = ROJO;
            } else if(tipo_draw == DIFER){
               col = AMARILLO;
            } else if(tipo_draw == CHESS){
               col = ROJO;
               tipo_draw = INMED;
            }
         }
         break ;
       case 'L':
          if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado visualización de linea" << endl;
            cout << "P: Modo punto" << endl;
            cout << "L: Modo linea" << endl;
            cout << "S: Modo Solido" << endl;
            cout << "A: Modo ajedrez" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            modo_dibujado = GL_LINE;
            if(tipo_draw == INMED){
               col = NEGRO;
            } else if(tipo_draw == DIFER){
               col = VERDE;
            } else if(tipo_draw == CHESS){
               col = NEGRO;
               tipo_draw = INMED;
            }
         }
         break ;
       case 'S':
          if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado visualización de solido" << endl;
            cout << "P: Modo punto" << endl;
            cout << "L: Modo linea" << endl;
            cout << "S: Modo Solido" << endl;
            cout << "A: Modo ajedrez" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            modo_dibujado = GL_FILL;
            if(tipo_draw == INMED){
               col = AZUL;
            } else if(tipo_draw == DIFER){
               col = ROSA;
            } else if(tipo_draw == CHESS){
               col = AZUL;
               tipo_draw = INMED;
            }
          }
         break ;
      case 'A':
         if(modoMenu == SELVISUALIZACION){
          cout << "Seleccionado visualización de ajedrez" << endl;
          cout << "P: Modo punto" << endl;
          cout << "L: Modo linea" << endl;
          cout << "S: Modo Solido" << endl;
          cout << "A: Modo ajedrez" << endl;
          cout << "Q: salir" << endl;
          cout << endl;
          modo_dibujado = GL_FILL;
          tipo_draw = CHESS;
          col = VERDE;
         }
         break ;
       case 'C':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado cubo" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            cubo->alternar_vista();
          }
          break ;
       case 'T':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            tetraedro->alternar_vista();
          }
          break ;
       case 'Y':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado archivo ply" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objply->alternar_vista();
          }
          break ;
       case 'R':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado archivo ply de rotacion" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "+: Quitar tapa superior" << endl;
            cout << "-: Quitar tapa inferior" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objrot->alternar_vista();
          }
          break ;
       case 'E':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado esfera" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "+: Quitar tapa superior" << endl;
            cout << "-: Quitar tapa inferior" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            esfera->alternar_vista();
          }
          break ;
       case '3':
         if(modoMenu == SELOBJETO){
           cout << "Seleccionado cono" << endl;
           cout << "C: Cubo" << endl;
           cout << "T: Tetraedro" << endl;
           cout << "Y: Archivo PLY" << endl;
           cout << "R: Archivo PLY rotacion" << endl;
           cout << "E: Esfera" << endl;
           cout << "3: Cono" << endl;
           cout << "4: Cilindro" << endl;
           cout << "M: Escena Multiple" << endl;
           cout << "+: Quitar tapa superior" << endl;
           cout << "-: Quitar tapa inferior" << endl;
           cout << "Q: salir" << endl;
           cout << endl;
           cono->alternar_vista();
         }
         break ;
         case '4':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado cilindro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "+: Quitar tapa superior" << endl;
            cout << "-: Quitar tapa inferior" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            cilindro->alternar_vista();
          }
          break ;
      case '1':
         if(modoMenu == SELDIBUJADO){
           cout << "Seleccionado modo inmediato" << endl;
           cout << "1: Modo inmediato" << endl;
           cout << "2: Modo diferido" << endl;
           cout << "Q: salir" << endl;
           cout << endl;
           tipo_draw = INMED;
           col = AZUL;
           modo_dibujado = GL_FILL;
         }
         break ;
       case '2':
          if(modoMenu == SELDIBUJADO){
            cout << "Seleccionado modo diferido" << endl;
            cout << "1: Modo inmediato" << endl;
            cout << "2: Modo diferido" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            tipo_draw = DIFER;
            col = ROSA;
            modo_dibujado = GL_FILL;
          }
          break ;
       case '+':
         if(modoMenu == SELOBJETO){
            cout << "Quitada tapa superior" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "+: Quitar tapa superior" << endl;
            cout << "-: Quitar tapa inferior" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objrot->tapaSuperior();
            cilindro->tapaSuperior();
            cono->tapaSuperior();
            esfera->tapaSuperior();
         }
          break ;
       case '-':
         if(modoMenu == SELOBJETO){
            cout << "Quitada tapa inferior" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "+: Quitar tapa superior" << endl;
            cout << "-: Quitar tapa inferior" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objrot->tapaInferior();
            cilindro->tapaInferior();
            cono->tapaInferior();
            esfera->tapaInferior();
         }
          break ;
       case 'M':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "M: Escena Multiple" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = MULT;
            }
          break ;
   }
   return salir;
}
//*********************************-*****************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
