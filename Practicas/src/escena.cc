

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


   int num_rot = 20;
   cubo = new Cubo(10);
   tetraedro = new Tetraedro(10);
   objply = new ObjPLY(ply,10);
   objrot = new ObjRevolucion(plyrot);
   esfera = new Esfera(100);
   cilindro = new Cilindro(150, 50);
   cono = new Cono(150,50);
   torre = new Torre();
   robot = new Robot(45.0,-45.0,0.0);
   cuadro = new Cuadro(10);

   Tupla4f amb = {0.0,0.0,0.0,1.0};
   Tupla4f dif = {1.0,1.0,1.0,1.0};
   Tupla4f esp = {1.0,1.0,1.0,1.0};
   Tupla3f dir = {0.0,1.0,0.0};
   luzdir = new LuzDireccional(dir, GL_LIGHT1, amb, dif, esp);
   Tupla3f pos = {0.0,0.0,500.0};
   luzpos = new LuzPosicional(pos, GL_LIGHT2, amb, dif, esp);

   esmeralda = new Material(coldifesmeralda, colespesmeralda, colambesmeralda, brilloesmeralda);
   rubi = new Material(coldifrubi,colesprubi,colambrubi, brillorubi);
   negro = new Material(coldifnegro,colespnegro,colambnegro, brillonegro);
   blanco = new Material(coldifblanco,colespblanco,colambblanco, brilloblanco);
   bronce = new Material(coldifbronce,colespbronce,colambbronce, brillobronce);
   perla = new Material(coldifperla,colespperla,colambperla, brilloperla);
   blancop = new Material(Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),128.0);

   robot->setMaterial(*bronce);
   cuadro->setMaterial(*blancop);
   torre->setMaterial(*rubi);
   cilindro->setMaterial(*blancop);

   cuadro->setTextura(madera);
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
   glEnable( GL_NORMALIZE );

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   cout << "Seleccione menu" << endl;
   cout << "O: Seleccion de objeto" << endl;
   cout << "V: seleccion de visualizacion" << endl;
   cout << "D: seleccion de dibujado" << endl;
   cout << "I: seleccion de iluminacion" << endl;
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
   glDisable(GL_LIGHT1);
   glDisable(GL_LIGHT2);
   ejes.draw();
   for(int i = 0; i < 3; i++){
      if(bool_dibujado[i]){
         switch (i) {
            case 0:
               modo_dibujado = GL_POINT;
               col = CIAN;
               break;
            case 1:
               modo_dibujado = GL_LINE;
               col = AZUL;
               break;
            case 2:
               modo_dibujado = GL_FILL;
               col = NARANJA;
               break;
         }

         if(actluzdir){
            luzdir->activar();
         }

         if(actluzpos){
            glPushMatrix();
               glRotatef(luzm, 0,1,0);
               luzpos->activar();
            glPopMatrix();
         }

         glPushMatrix();

            glPushMatrix();
               glScalef(500.0,1.0,500.0);
               glRotatef(-90,1,0,0);
               cuadro->draw(tipo_draw,BLANCO,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glScalef(0.7,0.7,0.7);
               glTranslatef(0,0,180);
               torre->draw(tipo_draw,col,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0.0,10.0,0.0);
               robot->draw(tipo_draw,col,modo_dibujado);
            glPopMatrix();

         glPopMatrix();
      }
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
         if (modoMenu!=NADA && modoMenu != SELANGULO){
            cout << "Seleccione menu" << endl;
            cout << "O: Seleccion de objeto" << endl;
            cout << "V: seleccion de visualizacion" << endl;
            cout << "D: seleccion de dibujado" << endl;
            cout << "I: seleccion de iluminacion" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            modoMenu=NADA;
         } else if(modoMenu == SELANGULO){
            cout << "Seleccione modo de iluminacion" << endl;
            cout << "0: Activar luz 0" << endl;
            cout << "1: Activar luz 1" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            modoMenu=ILUMINACION;
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
         cout << "N: Cono" << endl;
         cout << "M: Cilindro" << endl;
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
            if(tipo_draw == DIFER){
               tipo_draw = DIFER;
            } else {
               tipo_draw = INMED;
            }
            iluminacion = false;
            bool_dibujado[0] = !bool_dibujado[0];
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
            if(tipo_draw == DIFER){
               tipo_draw = DIFER;
            } else {
               tipo_draw = INMED;
            }
            iluminacion = false;
            bool_dibujado[1] = !bool_dibujado[1];
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
            if(tipo_draw == DIFER){
               tipo_draw = DIFER;
            } else {
               tipo_draw = INMED;
            }
            iluminacion = false;
            bool_dibujado[2] = !bool_dibujado[2];
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
            tipo_draw = CHESS;
            bool_dibujado[0] = false;
            bool_dibujado[1] = false;
            bool_dibujado[2] = true;
         } else if(modoMenu == ILUMINACION){
            cout << "Seleccionado angulo alfa" << endl;
            cout << ">: Aunmentar angulo" << endl;
            cout << "<: Decrementar angulo" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            ang = ALFA;
            modoMenu = SELANGULO;
         }
         break;
      case 'B':
         if(modoMenu == ILUMINACION){
            cout << "Seleccionado angulo beta" << endl;
            cout << ">: Aunmentar angulo" << endl;
            cout << "<: Decrementar angulo" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            ang = BETA;
            modoMenu = SELANGULO;
         }
         break;
      case '>':
         if(modoMenu == SELANGULO){
            cout << "Incrementado angulo" << endl;
            cout << ">: Aunmentar angulo" << endl;
            cout << "<: Decrementar angulo" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            if(ang == ALFA){
               luzdir->variarAnguloAlpha(5.0);
            }else if(ang == BETA){
               luzdir->variarAnguloBeta(5.0);
            }
         }
         break;
      case '<':
         if(modoMenu == SELANGULO){
            cout << "Decrementado angulo" << endl;
            cout << ">: Aunmentar angulo" << endl;
            cout << "<: Decrementar angulo" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            if(ang == ALFA){
               luzdir->variarAnguloAlpha(-5.0);
            }else if(ang == BETA){
               luzdir->variarAnguloBeta(-5.0);
            }
         }
         break;
      case 'I':
            cout << "Seleccione modo de iluminacion" << endl;
            cout << "0: Activar luz 0 (direccional)" << endl;
            cout << "1: Activar luz 1 (posicional)" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            if(tipo_draw == SMUZ && iluminacion && modoMenu == ILUMINACION){
               tipo_draw = PLAIN;
            } else {
               tipo_draw = SMUZ;
            }
            modoMenu = ILUMINACION;
            iluminacion = true;
            bool_dibujado[0] = false;
            bool_dibujado[1] = false;
            bool_dibujado[2] = true;


         break ;
      case 'C':
         if(modoMenu == SELOBJETO){
            cout << "Seleccionado cubo" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
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
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
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
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
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
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
            cout << "+: Alternar tapas" << endl;
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
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
            cout << "+: Alternar tapas" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            esfera->alternar_vista();
         }
         break ;
      case 'N':
         if(modoMenu == SELOBJETO){
            cout << "Seleccionado cono" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
            cout << "+: Alternar tapas" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            cono->alternar_vista();
         }
         break ;
      case 'M':
            if(modoMenu == SELOBJETO){
            cout << "Seleccionado cilindro" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
            cout << "+: Alternar tapas" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            cilindro->alternar_vista();
         }
         break ;
      case '0':
         if(modoMenu == ILUMINACION){
            cout << "Luz 0 activada (direccional)" << endl;
            cout << "0: Activar luz 0 (direccional)" << endl;
            cout << "1: Activar luz 1 (posicional)" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            actluzdir = !actluzdir;
            }
            break;
      case '1':
         if(modoMenu == SELDIBUJADO){
            cout << "Seleccionado modo inmediato" << endl;
            cout << "1: Modo inmediato" << endl;
            cout << "2: Modo diferido" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            tipo_draw = INMED;
            bool_dibujado[0] = false;
            bool_dibujado[1] = false;
            bool_dibujado[2] = true;
         } else if(modoMenu == ILUMINACION){
            cout << "Luz 1 activada (posicional)" << endl;
            cout << "0: Activar luz 0 (direccional)" << endl;
            cout << "1: Activar luz 1 (posicional)" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            actluzpos = !actluzpos;
         } else if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado brazo izquierdo" << endl;
            gl = CODOI;
            modoMenu = GRADOLIB;
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
            bool_dibujado[0] = false;
            bool_dibujado[1] = false;
            bool_dibujado[2] = true;
         }else if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado brazo derecho" << endl;
            gl = CODOD;
            modoMenu = GRADOLIB;
         }
         break ;
      case '3':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado piernas" << endl;
            gl = PIERNAS;
            modoMenu = GRADOLIB;
         }
         break;
      case '4':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado taladro izquierdo" << endl;
            gl = TALADROI;
            modoMenu = GRADOLIB;
         }
         break;
      case '5':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado taladro derecho" << endl;
            gl = TALADROD;
            modoMenu = GRADOLIB;
         }
         break;
      case '6':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado antena" << endl;
            gl = ANTENA;
            modoMenu = GRADOLIB;
         }
         break;
      case '+':
         if(modoMenu == SELOBJETO){
            cout << "Q  uitada tapa superior" << endl;
            cout << "C: Cubo" << endl;
            cout << "T: Tetraedro" << endl;
            cout << "Y: Archivo PLY" << endl;
            cout << "R: Archivo PLY rotacion" << endl;
            cout << "E: Esfera" << endl;
            cout << "N: Cono" << endl;
            cout << "M: Cilindro" << endl;
            cout << "+: Alternar tapas" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            objrot->tapas();
            cilindro->tapas();
            cono->tapas();
            esfera->tapas();
         } else if (modoMenu == ANIMA){
            vel = vel + 1.0;
            if(vel >= 15.0){
               vel = 15.0;
            }
            taladro = taladro + 1.0;
         } else if(modoMenu == GRADOLIB){
            switch(gl){
               case CODOD:
                  robot->incrementarAnguloBrazoDer(1.0);
               break;
               case CODOI:
                  robot->incrementarAnguloBrazoIzq(1.0);
               break;
               case PIERNAS:
                  robot->incrementarAnguloPiernas(1.0);
               break;
               case TALADROD:
                  robot->incrementarTaladroDer(1.0);
               break;
               case TALADROI:
                  robot->incrementarTaladroIzq(1.0);
               break;
               case ANTENA:
                  robot->incrementarAlturaAntena(1.0);
               break;
            }
         }
         break;
      case 'J':
         modoMenu = ANIMA;
         cout << "Modo animacion:" << endl;
         cout << "+: animacion mas rapida" << endl;
         cout << "-: animacion mas lenta" << endl;
         cout << "8: parar" << endl;
         break;
      case '-':
         if(modoMenu == ANIMA){
            if(!(vel <= 0.0)){
               vel = vel - 1.0;
            }
            if(!(taladro <= 0.0)){
               taladro = taladro - 1.0;
            }
         } else if(modoMenu == GRADOLIB){
            switch(gl){
               case CODOD:
                  robot->incrementarAnguloBrazoDer(-1.0);
               break;
               case CODOI:
                  robot->incrementarAnguloBrazoIzq(-1.0);
               break;
               case PIERNAS:
                  robot->incrementarAnguloPiernas(-1.0);
               break;
               case TALADROD:
                  robot->incrementarTaladroDer(-1.0);
               break;
               case TALADROI:
                  robot->incrementarTaladroIzq(-1.0);
               break;
               case ANTENA:
                  robot->incrementarAlturaAntena(-1.0);
               break;
            }
         }
         break;
      case '8':
         vel = 0.0;
         taladro = 0.0;
         robot->setAlfas(0.0,0.0,0.0);
         break;
      }

   return salir;
}
//*********************************-*****************************************
void Escena::animarModeloJerarquico(){
   robot->incrementarAnguloPiernas(vel);
   robot->incrementarAnguloBrazoIzq(vel);
   robot->incrementarAnguloBrazoDer(vel);
   robot->incrementarTaladroIzq(taladro);
   robot->incrementarTaladroDer(taladro);
   robot->incrementarAlturaAntena(taladro*0.25);
   luzm+=1.0;
   if(luzm > 360.0){
      luzm = 0.0;
   }
   std::cout << "Angulo:" << luzm << std::endl;
}

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
