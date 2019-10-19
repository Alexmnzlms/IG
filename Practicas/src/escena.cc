

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
    cubo = new Cubo(75);
    tetraedro = new Tetraedro(75);
    objply = new ObjPLY("ply/ant.ply",10);

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
               cout << "Q: salir" << endl;
               cout << endl;
               objMalla = PLY;
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
   }
   return salir;
}
//**************************************************************************

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
