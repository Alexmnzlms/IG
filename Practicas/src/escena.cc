

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

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    int num_vert = 10;
    int num_rot = 20;
    cubo = new Cubo(75);
    tetraedro = new Tetraedro(75);
    objply = new ObjPLY(ply,7);
    objrot = new ObjRevolucion(plyrot, num_rot, 65,true,true);
    esfera = new Esfera(num_vert, num_rot, 100.0);
    cono = new Cono(num_rot, 100.0, 100.0);
    cilindro = new Cilindro(num_rot, 100.0, 100.0);
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

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

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
   ejes.draw();

    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
    // cubo.draw()
    // o
    // tetraedro.draw()

   switch (objMalla) {
      case CUBO:
         if(punto && !ajedrez){
            cubo->cambiar_modo(GL_POINT);
            cubo->cambiar_draw(tipo_draw);
            cubo->draw();
         }
         if(linea && !ajedrez){
            cubo->cambiar_modo(GL_LINE);
            cubo->cambiar_draw(tipo_draw);
            cubo->draw();
         }
         if(solido){
            cubo->cambiar_modo(GL_FILL);
            cubo->cambiar_draw(tipo_draw);
            cubo->draw();
         }
         if(ajedrez){
            cubo->cambiar_modo(GL_FILL);
            cubo->cambiar_draw(CHEST);
            cubo->draw();
         }
         break;
      case TETRAEDRO:
         if(punto){
            tetraedro->cambiar_modo(GL_POINT);
            tetraedro->cambiar_draw(tipo_draw);
            tetraedro->draw();
         }
         if(linea){
            tetraedro->cambiar_modo(GL_LINE);
            tetraedro->cambiar_draw(tipo_draw);
            tetraedro->draw();
         }
         if(solido){
            tetraedro->cambiar_modo(GL_FILL);
            tetraedro->cambiar_draw(tipo_draw);
            tetraedro->draw();
         }
         if(ajedrez){
            tetraedro->cambiar_modo(GL_FILL);
            tetraedro->cambiar_draw(CHEST);
            tetraedro->draw();
         }
         break;
      case PLY:
         if(punto){
            objply->cambiar_modo(GL_POINT);
            objply->cambiar_draw(tipo_draw);
            objply->draw();
         }
         if(linea){
            objply->cambiar_modo(GL_LINE);
            objply->cambiar_draw(tipo_draw);
            objply->draw();
         }
         if(solido){
            objply->cambiar_modo(GL_FILL);
            objply->cambiar_draw(tipo_draw);
            objply->draw();
         }
         if(ajedrez){
            objply->cambiar_modo(GL_FILL);
            objply->cambiar_draw(CHEST);
            objply->draw();
         }
         break;
      case ROT:
         if(punto){
            objrot->cambiar_modo(GL_POINT);
            objrot->cambiar_draw(tipo_draw);
            objrot->tapaSuperior(quitar_superior);
            objrot->tapaInferior(quitar_inferior);
            objrot->draw();
         }
         if(linea){
            objrot->cambiar_modo(GL_LINE);
            objrot->cambiar_draw(tipo_draw);
            objrot->tapaSuperior(quitar_superior);
            objrot->tapaInferior(quitar_inferior);
            objrot->draw();
         }
         if(solido){
            objrot->cambiar_modo(GL_FILL);
            objrot->cambiar_draw(tipo_draw);
            objrot->tapaSuperior(quitar_superior);
            objrot->tapaInferior(quitar_inferior);
            objrot->draw();
         }
         if(ajedrez){
            objrot->cambiar_modo(GL_FILL);
            objrot->cambiar_draw(CHEST);
            objrot->tapaSuperior(quitar_superior);
            objrot->tapaInferior(quitar_inferior);
            objrot->draw();
         }
         break;
      case CON:
         if(punto){
            cono->cambiar_modo(GL_POINT);
            cono->cambiar_draw(tipo_draw);
            cono->tapaSuperior(quitar_superior);
            cono->tapaInferior(quitar_inferior);
            cono->draw();
         }
         if(linea){
            cono->cambiar_modo(GL_LINE);
            cono->cambiar_draw(tipo_draw);
            cono->tapaSuperior(quitar_superior);
            cono->tapaInferior(quitar_inferior);
            cono->draw();
         }
         if(solido){
            cono->cambiar_modo(GL_FILL);
            cono->cambiar_draw(tipo_draw);
            cono->tapaSuperior(quitar_superior);
            cono->tapaInferior(quitar_inferior);
            cono->draw();
         }
         if(ajedrez){
            cono->cambiar_modo(GL_FILL);
            cono->cambiar_draw(CHEST);
            cono->tapaSuperior(quitar_superior);
            cono->tapaInferior(quitar_inferior);
            cono->draw();
         }
         break;
      case ESF:
         if(punto){
            esfera->cambiar_modo(GL_POINT);
            esfera->cambiar_draw(tipo_draw);
            esfera->tapaSuperior(quitar_superior);
            esfera->tapaInferior(quitar_inferior);
            esfera->draw();
         }
         if(linea){
            esfera->cambiar_modo(GL_LINE);
            esfera->cambiar_draw(tipo_draw);
            esfera->tapaSuperior(quitar_superior);
            esfera->tapaInferior(quitar_inferior);
            esfera->draw();
         }
         if(solido){
            esfera->cambiar_modo(GL_FILL);
            esfera->cambiar_draw(tipo_draw);
            esfera->tapaSuperior(quitar_superior);
            esfera->tapaInferior(quitar_inferior);
            esfera->draw();
         }
         if(ajedrez){
            esfera->cambiar_modo(GL_FILL);
            esfera->cambiar_draw(CHEST);
            esfera->tapaSuperior(quitar_superior);
            esfera->tapaInferior(quitar_inferior);
            esfera->draw();
         }
         break;
      case CIL:
         if(punto){
            cilindro->cambiar_modo(GL_POINT);
            cilindro->cambiar_draw(tipo_draw);
            cilindro->tapaSuperior(quitar_superior);
            cilindro->tapaInferior(quitar_inferior);
            cilindro->draw();
         }
         if(linea){
            cilindro->cambiar_modo(GL_LINE);
            cilindro->cambiar_draw(tipo_draw);
            cilindro->tapaSuperior(quitar_superior);
            cilindro->tapaInferior(quitar_inferior);
            cilindro->draw();
         }
         if(solido){
            cilindro->cambiar_modo(GL_FILL);
            cilindro->cambiar_draw(tipo_draw);
            cilindro->tapaSuperior(quitar_superior);
            cilindro->tapaInferior(quitar_inferior);
            cilindro->draw();
         }
         if(ajedrez){
            cilindro->cambiar_modo(GL_FILL);
            cilindro->cambiar_draw(CHEST);
            cilindro->tapaSuperior(quitar_superior);
            cilindro->tapaInferior(quitar_inferior);
            cilindro->draw();
         }
         break;
      case MULT:
      dibujo draw = CHEST;
      GLenum tipo = GL_FILL;
         glPushMatrix();
            glPushMatrix();
               glTranslatef(100,0,0);
               cilindro->cambiar_modo(tipo);
               cilindro->cambiar_draw(draw);
               cilindro->draw();
            glPopMatrix();
            glPushMatrix();
               glTranslatef(-150,0,0);
               cono->cambiar_modo(tipo);
               cono->cambiar_draw(draw);
               cono->draw();
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,75,-150);
               esfera->cambiar_modo(tipo);
               esfera->cambiar_draw(draw);
               esfera->draw();
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,150);
               //glScalef(0.25,0.25,0.25);
               objrot->cambiar_modo(tipo);
               objrot->cambiar_draw(draw);
               objrot->draw();
            glPopMatrix();
         glPopMatrix();
      break;

   }


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
         // COMPLETAR con los diferentes opciones de teclado
       case 'P':
          if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado visualización de punto" << endl;
            cout << "P: Modo punto" << endl;
            cout << "L: Modo linea" << endl;
            cout << "S: Modo Solido" << endl;
            cout << "A: Modo ajedrez" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            punto = !punto;
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
            linea = !linea;
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
            solido = !solido;
            ajedrez = false;
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
          ajedrez = !ajedrez;
          solido = false;
          punto = false;
          linea = false;
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
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = CUBO;
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
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = TETRAEDRO;
          }
          break ;
       case 'Y':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = PLY;
          }
          break ;
       case 'R':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = ROT;
          }
          break ;
       case 'E':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = ESF;
          }
          break ;
       case '3':
         if(modoMenu == SELOBJETO){
           cout << "Seleccionado tetraedro" << endl;
           cout << "C: Cubo" << endl;
           cout << "T: Tetraedro" << endl;
           cout << "Y: Archivo PLY" << endl;
           cout << "R: Archivo PLY rotacion" << endl;
           cout << "E: Esfera" << endl;
           cout << "3: Cono" << endl;
           cout << "4: Cilindro" << endl;
           cout << "Q: salir" << endl;
           cout << endl;
           objMalla = CON;
         }
         break ;
         case '4':
          if(modoMenu == SELOBJETO){
            cout << "Seleccionado tetraedro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "3: Cono" << endl;
            cout << "4: Cilindro" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objMalla = CIL;
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
          }
          break ;
       case '+':
          if(objMalla == ROT ||
             objMalla == CIL ||
             objMalla == CON ||
             objMalla == ESF){
            quitar_superior = !quitar_superior;
          }
          break ;
       case '-':
          if(objMalla == ROT ||
             objMalla == CIL ||
             objMalla == CON ||
             objMalla == ESF){
            quitar_inferior = !quitar_inferior;
          }
          break ;
       case 'M':
          objMalla = MULT;
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
