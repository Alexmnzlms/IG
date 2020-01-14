

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 3000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   Camara camara0(Tupla3f(0.0,300.0,700.0),Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0),
                  0, -50.0, 50.0, Front_plane, Back_plane, 50.0, -50.0);
   Camara camara1(Tupla3f(0.0,300.0,700.0),Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0),
                  1, -50.0, 50.0, Front_plane, Back_plane, 50.0, -50.0);
   Camara camara2(Tupla3f(0.0,450.0,-150.0),Tupla3f(0.0,300.0,0.0), Tupla3f(0.0,1.0,0.0),
                  0, -50.0, 50.0, Front_plane, Back_plane, 50.0, -50.0);

   camaras.push_back(camara0);
   camaras.push_back(camara1);
   camaras.push_back(camara2);


   int num_rot = 20;
   cubo = new Cubo(100);
   tetraedro = new Tetraedro(10);
   objply = new ObjPLY(ply,10);
   objrot = new ObjRevolucion(plyrot);
   esfera = new Esfera(100);
   cilindrod = new Cilindro(150, 50);
   cilindroi = new Cilindro(150, 50);
   cono = new Cono(150,50);
   torre = new Torre();
   robot = new Robot(45.0,-45.0,0.0);
   suelo = new Cuadro(10);
   fondo = new Cuadro(10);

   Tupla4f amb = {0.0,0.0,0.0,1.0};
   Tupla4f dif = {1.0,1.0,1.0,1.0};
   Tupla4f esp = {1.0,1.0,1.0,1.0};
   Tupla3f dir = {0.0,1.0,0.0};
   luzdir = new LuzDireccional(dir, GL_LIGHT1, amb, dif, esp);
   Tupla3f pos = {0.0,0.0,1000.0};
   luzpos = new LuzPosicional(pos, GL_LIGHT2, amb, dif, esp);

   esmeralda = new Material(coldifesmeralda, colespesmeralda, colambesmeralda, brilloesmeralda);
   rubi = new Material(coldifrubi,colesprubi,colambrubi, brillorubi);
   negro = new Material(coldifnegro,colespnegro,colambnegro, brillonegro);
   blanco = new Material(coldifblanco,colespblanco,colambblanco, brilloblanco);
   bronce = new Material(coldifbronce,colespbronce,colambbronce, brillobronce);
   perla = new Material(coldifperla,colespperla,colambperla, brilloperla);
   blancop = new Material(Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),128.0);

   suelo->setTextura(ground);
   fondo->setTextura(back);
   cilindrod->setTextura(edificio);
   cilindroi->setTextura(edificio);
   cubo->setTextura(edificio);
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

   cout << endl;
   cout << endl;
   cout << "Seleccione menu" << endl;
   cout << "O: Seleccion de objeto" << endl;
   cout << "V: seleccion de visualizacion" << endl;
   cout << "D: seleccion de dibujado" << endl;
   cout << "I: seleccion de iluminacion" << endl;
   cout << "J: seleccion de animacion" << endl;
   cout << "C: seleccion de camara" << endl;
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
               coltex = CIAN;
               break;
            case 1:
               modo_dibujado = GL_LINE;
               col = VERDE;
               coltex = VERDE;
               break;
            case 2:
               modo_dibujado = GL_FILL;
               col = NARANJA;
               coltex = BLANCO;
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

         robot->setMaterial(*bronce);
         suelo->setMaterial(*blancop);
         fondo->setMaterial(*blancop);
         torre->setMaterial(*blancop);
         cilindrod->setMaterial(*blancop);
         cilindroi->setMaterial(*blancop);
         cubo->setMaterial(*blancop);

         glPushMatrix();

            glPushMatrix();
               glScalef(500.0,1.0,250.0);
               glRotatef(-90,1,0,0);
               colfig = coltex;
               suelo->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0.0,1250.0,-1250.0);
               glScalef(500.0,250.0,1.0);
               colfig = coltex;
               fondo->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(1250.0,1250.0,0.0);
               glScalef(1.0,250.0,500.0);
               glRotatef(-90.0,0,1,0);
               colfig = coltex;
               fondo->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(-1250.0,1250.0,0.0);
               glScalef(1.0,250.0,500.0);
               glRotatef(90.0,0,1,0);
               colfig = coltex;
               fondo->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glScalef(2.0,2.0,2.0);
               glTranslatef(0,0,100);
               if(seleccionado == TORRE){
                  colfig = AMARILLO;
                  torre->setMaterial(*rubi);
               } else {
                  colfig = coltex;
               }
               torre->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0.0,0.0,-100.0);
               glScalef(2.0,2.0,2.0);
               if(seleccionado == ROBOT){
                  colfig = AMARILLO;
                  robot->setMaterial(*rubi);
               } else {
                  colfig = col;
               }
               robot->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(-300.0,0.0,-500.0);
               glScalef(1.5,2.0,1.5);
               if(seleccionado == EDIFI){
                  colfig = AMARILLO;
                  cilindrod->setMaterial(*rubi);
               } else {
                  colfig = coltex;
               }
               cilindrod->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(300.0,0.0,-500.0);
               glScalef(1.5,2.0,1.5);
               if(seleccionado == EDIFD){
                  colfig = AMARILLO;
                  cilindroi->setMaterial(*rubi);
               } else {
                  colfig = coltex;
               }
               cilindroi->draw(tipo_draw,colfig,modo_dibujado);
            glPopMatrix();

            glPushMatrix();
               glTranslatef(0.0,150.0,-500.0);
               glScalef(1.5,3.0,1.5);
               if(seleccionado == EDIFC){
                  colfig = AMARILLO;
                  cubo->setMaterial(*rubi);
               } else {
                  colfig = coltex;
               }
               cubo->draw(tipo_draw,colfig,modo_dibujado);
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

void Escena::animarModeloJerarquico(){
   robot->incrementarAnguloPiernas(vel);
   robot->incrementarAnguloBrazoIzq(vel);
   robot->incrementarAnguloBrazoDer(vel);
   robot->incrementarTaladroIzq(taladro);
   robot->incrementarTaladroDer(taladro);
   robot->incrementarAlturaAntena(taladro*0.25);
   luzm+=veluz;
   if(luzm > 360.0){
      luzm = 0.0;
   }
}

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[camaraActiva].rotarYExaminar(-3.0*M_PI/180.0);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarYExaminar(3.0*M_PI/180.0);
         break;
	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarXExaminar(3.0*M_PI/180.0);
         break;
	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarXExaminar(-3.0*M_PI/180.0);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva].zoom(1/1.2);
         change_projection(1.0);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva].zoom(1.2);
         change_projection(1.0);
         break;
	}
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
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   for(int i = 0; i < camaras.size(); i++){
      camaras[i].setLetf(camaras[i].getBottom()*Width/Height);
      camaras[i].setRight(camaras[i].getTop()*Width/Height);
   }
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
   camaras[camaraActiva].setOberver();
}

void Escena::ratonMovido(int x, int y){
   if(ratonPulsado){
      //Mover en primera persona
      if(seleccionado == NOSEL){
         camaras[camaraActiva].girar(x-x_ant, y-y_ant);
      } else {
         camaras[camaraActiva].rotarXExaminar(-0.25*(y-y_ant)*M_PI/180.0);
         camaras[camaraActiva].rotarYExaminar(-0.25*(x-x_ant)*M_PI/180.0);
      }
      x_ant = x;
      y_ant = y;
   }
}

void Escena::clickRaton(int boton, int status, int x, int y){
   if(boton == GLUT_RIGHT_BUTTON){
      //Mover primera persona
      if(status == GLUT_DOWN){
         x_ant = x;
         y_ant = y;
         ratonPulsado = true;
      } else {
         ratonPulsado = false;
      }
   } else if (boton == GLUT_LEFT_BUTTON){
      //Seleccionar objeto
      if(status == GLUT_DOWN){
         dibujar_seleccion();
         procesar_click(x,y);
      }
   } else if (boton == 3){
      camaras[camaraActiva].zoom(1.2);
      change_projection(1.0);
   } else if (boton == 4){
      camaras[camaraActiva].zoom(1/1.2);
      change_projection(1.0);
   }
}

void Escena::dibujar_seleccion(){
   color colsec;
   GLenum modo_dibujado_sel = GL_FILL;
   dibujo tipo_draw_sel = SELECT;

   change_observer();
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   bool act_dit;
   act_dit  = false;
   glDisable(GL_LIGHTING);
   glDisable(GL_LIGHT1);
   glDisable(GL_LIGHT2);
   if(glIsEnabled(GL_DITHER)){
      glDisable(GL_DITHER);
      act_dit = true;
   }

   glPushMatrix();

      glPushMatrix();
         glScalef(2.0,2.0,2.0);
         glTranslatef(0,0,100);
         colsec = VERDE;
         torre->draw(tipo_draw_sel,colsec,modo_dibujado_sel);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.0,0.0,-100.0);
         glScalef(2.0,2.0,2.0);
         colsec = AMARILLO;
         robot->draw(tipo_draw_sel,colsec,modo_dibujado_sel);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(-300.0,0.0,-500.0);
         glScalef(1.5,2.0,1.5);
         colsec = AZUL;
         cilindrod->draw(tipo_draw_sel,colsec,modo_dibujado_sel);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(300.0,0.0,-500.0);
         glScalef(1.5,2.0,1.5);
         colsec = NEGRO;
         cilindroi->draw(tipo_draw_sel,colsec,modo_dibujado_sel);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.0,150.0,-500.0);
         glScalef(1.5,3.0,1.5);
         colsec = ROSA;
         cubo->draw(tipo_draw_sel,colsec,modo_dibujado_sel);
      glPopMatrix();

   glPopMatrix();
   if(act_dit){
      glEnable(GL_DITHER);
   }
}

void Escena::procesar_click(int x, int y){
   GLint viewport[4];
   GLfloat pixel[3];
   glGetIntegerv(GL_VIEWPORT,viewport);
   glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,pixel);

   Tupla3f color = {pixel[0],pixel[1],pixel[2]};

   if(color(0) == 0.0 && color(1) == 1.0 && color(2) == 0.0){
      std::cout << "Seleccionada la torre" << std::endl;
      seleccionado = TORRE;
      camaras[camaraActiva].mover(0.0,50.0,150.0);
   } else if(color(0) == 0.0 && color(1) == 0.0 && color(2) == 0.0){
      std::cout << "Seleccionado el edificio derecho" << std::endl;
      seleccionado = EDIFD;
      camaras[camaraActiva].mover(300.0,50.0,-500.0);
   } else if(color(0) == 0.0 && color(1) == 0.0 && color(2) == 1.0){
      std::cout << "Seleccionado el edificio izquierdo" << std::endl;
      seleccionado = EDIFI;
      camaras[camaraActiva].mover(-300.0,50.0,-500.0);
   } else if(color(0) == 1.0 && color(1) == 0.0 && color(2) == 1.0){
      std::cout << "Seleccionado el edificio central" << std::endl;
      seleccionado = EDIFC;
      camaras[camaraActiva].mover(0.0,50.0,-500.0);
   } else if(color(0) == 1.0 && color(1) == 1.0 && color(2) == 0.0){
      std::cout << "Seleccionado el robot" << std::endl;
      seleccionado = ROBOT;
      camaras[camaraActiva].mover(0.0,50.0,-100.0);
   } else {
      seleccionado = NOSEL;
   }
}

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
            cout << "J: seleccion de animacion" << endl;
            cout << "C: seleccion de camara" << endl;
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
         cout << "1: Seleccionar brazo izquierdo" << endl;
         cout << "2: Seleccionar brazo derecho" << endl;
         cout << "3: Seleccionar piernas" << endl;
         cout << "4: Seleccionar taladro izquierdo" << endl;
         cout << "5: Seleccionar taladro derecho" << endl;
         cout << "6: Seleccionar antena" << endl;
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
            cout << "1: Seleccionar brazo izquierdo" << endl;
            cout << "2: Seleccionar brazo derecho" << endl;
            cout << "3: Seleccionar piernas" << endl;
            cout << "4: Seleccionar taladro izquierdo" << endl;
            cout << "5: Seleccionar taladro derecho" << endl;
            cout << "6: Seleccionar antena" << endl;
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
            cout << "1: Seleccionar brazo izquierdo" << endl;
            cout << "2: Seleccionar brazo derecho" << endl;
            cout << "3: Seleccionar piernas" << endl;
            cout << "4: Seleccionar taladro izquierdo" << endl;
            cout << "5: Seleccionar taladro derecho" << endl;
            cout << "6: Seleccionar antena" << endl;
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
            cout << "1: Seleccionar brazo izquierdo" << endl;
            cout << "2: Seleccionar brazo derecho" << endl;
            cout << "3: Seleccionar piernas" << endl;
            cout << "4: Seleccionar taladro izquierdo" << endl;
            cout << "5: Seleccionar taladro derecho" << endl;
            cout << "6: Seleccionar antena" << endl;
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
            cout << "1: Seleccionar brazo izquierdo" << endl;
            cout << "2: Seleccionar brazo derecho" << endl;
            cout << "3: Seleccionar piernas" << endl;
            cout << "4: Seleccionar taladro izquierdo" << endl;
            cout << "5: Seleccionar taladro derecho" << endl;
            cout << "6: Seleccionar antena" << endl;
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
         modoMenu=CAMARA;
         cout << "Seleccione la camara que quiere ver" << endl;
         cout << "0: Camara perspectiva" << endl;
         cout << "1: Camara ortogonal" << endl;
         cout << "2: Camara perspectiva 2" << endl;
         cout << "Q: salir" << endl;
         cout << endl;
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
            cilindrod->alternar_vista();
            cilindroi->alternar_vista();
         }
         break ;
      case '0':
         if(modoMenu == ILUMINACION){
            cout << "Luz 0 activada (direccional)" << endl;
            cout << "0: Activar luz 0 (direccional)" << endl;
            cout << "1: Activar luz 1 (posicional)" << endl;
            cout << "2: Parar luz poscional" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            actluzdir = !actluzdir;
         } else if( modoMenu == CAMARA){
            cout << "Seleccionada camara perspectiva" << endl;
            cout << "Seleccione la camara que quiere ver" << endl;
            cout << "0: Camara perspectiva" << endl;
            cout << "1: Camara ortogonal" << endl;
            cout << "2: Camara perspectiva 2" << endl;
            cout << "Q: salir" << endl;
            camaraActiva = 0;
            change_projection(1.0);
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
            cout << "2: Parar luz poscional" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            actluzpos = !actluzpos;
         } else if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado brazo izquierdo" << endl;
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            gl = CODOI;
            modoMenu = GRADOLIB;
         } else if( modoMenu == CAMARA){
            cout << "Seleccionada camara ortogonal" << endl;
            cout << "Seleccione la camara que quiere ver" << endl;
            cout << "0: Camara perspectiva" << endl;
            cout << "1: Camara ortogonal" << endl;
            cout << "2: Camara perspectiva 2" << endl;
            cout << "Q: salir" << endl;
            camaraActiva = 1;
            change_projection(1.0);
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
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            cout << "Q: salir" << endl;
            gl = CODOD;
            modoMenu = GRADOLIB;
         } else if(modoMenu == ILUMINACION){
            cout << "Luz posicional detenida" << endl;
            cout << "0: Activar luz 0 (direccional)" << endl;
            cout << "1: Activar luz 1 (posicional)" << endl;
            cout << "2: Parar luz poscional" << endl;
            cout << "A: Seleccionar Alfa" << endl;
            cout << "B: Selecionar Beta" << endl;
            cout << "Q: salir" << endl;
            cout << endl;
            veluz = 0;
         } else if( modoMenu == CAMARA){
            cout << "Seleccionada camara ortogonal" << endl;
            cout << "Seleccione la camara que quiere ver" << endl;
            cout << "0: Camara perspectiva" << endl;
            cout << "1: Camara ortogonal" << endl;
            cout << "2: Camara perspectiva 2" << endl;
            cout << "Q: salir" << endl;
            camaraActiva = 2;
            change_projection(1.0);
         }
         break ;
      case '3':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado piernas" << endl;
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            cout << "Q: salir" << endl;
            gl = PIERNAS;
            modoMenu = GRADOLIB;
         }
         break;
      case '4':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado taladro izquierdo" << endl;
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            cout << "Q: salir" << endl;
            gl = TALADROI;
            modoMenu = GRADOLIB;
         }
         break;
      case '5':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado taladro derecho" << endl;
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            cout << "Q: salir" << endl;
            gl = TALADROD;
            modoMenu = GRADOLIB;
         }
         break;
      case '6':
         if(modoMenu == SELVISUALIZACION){
            cout << "Seleccionado antena" << endl;
            cout << "+: Aumentar grado de libertad" << endl;
            cout << "-: Decrementar grado de libertad" << endl;
            cout << "Q: salir" << endl;
            gl = ANTENA;
            modoMenu = GRADOLIB;
         }
         break;
      case '+':
         if(modoMenu == SELOBJETO){
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
            cilindrod->tapas();
            cilindroi->tapas();
            cono->tapas();
            esfera->tapas();
         } else if (modoMenu == ANIMA){
            cout << "+: animacion mas rapida" << endl;
            cout << "Q: salir" << endl;
            vel = vel + 1.0;
            if(vel >= 15.0){
               vel = 15.0;
            }
            taladro = taladro + 1.0;
         } else if(modoMenu == GRADOLIB){
            cout << "+: aumentar grado de libertad" << endl;
            cout << "Q: salir" << endl;
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
         cout << "Q: salir" << endl;
         break;
      case '-':
         if(modoMenu == ANIMA){
            cout << "-: animacion mas lenta" << endl;
            cout << "Q: salir" << endl;
            if(!(vel <= 0.0)){
               vel = vel - 1.0;
            }
            if(!(taladro <= 0.0)){
               taladro = taladro - 1.0;
            }
         } else if(modoMenu == GRADOLIB){
            cout << "-: decremetar grado de libertad" << endl;
            cout << "Q: salir" << endl;
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
         cout << "Animacion deteniada" << endl;
         cout << "Q: salir" << endl;
         vel = 0.0;
         taladro = 0.0;
         robot->setAlfas(0.0,0.0,0.0);
         break;
      }

   return salir;
}
