#include "brazorobot.h"

BrazoRobot::BrazoRobot(float a, bool izq){
   alfa = a;
   delta = 0.0;
   pierna = new PiernaRobot(a);
   cono = new Cono(50,10);
   cono->setTextura("jpg/text-metal.jpg");
   Material * blancop = new Material(Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),128.0);
   cono->setMaterial(*blancop);
   animacion_neg = false;
   izquierda = izq;
}

void BrazoRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      pierna->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         glTranslatef(-10.5,-60*cos(pierna->getAlfa()*M_PI/180.0),0);
         glRotatef(180,1,0,0);
         glRotatef(delta,0,1,0);
         if(modo_dibujado == GL_FILL){
            cono->draw(tipo_draw,col,modo_dibujado);
         } else {
            cono->draw(tipo_draw,col,modo_dibujado);
         }

      glPopMatrix();
   glPopMatrix();
}

void BrazoRobot::setMaterial(Material mat){
   pierna->setMaterial(mat);
}

void BrazoRobot::incrementarAngulo(float inc){
   if(izquierda){
      if(alfa + inc >= 45.0){
         animacion_neg = true;
         alfa = 45.0 - inc;
      } else if(alfa + inc <= 0.0){
         animacion_neg = false;
         alfa = 0.0 + inc;
      }
      if(animacion_neg){
         inc = -1*inc;
      }
      alfa += inc;
      pierna->setAlfa(alfa);
   } else{
      if(alfa + inc >= 0.0){
         animacion_neg = true;
         alfa = 0.0 - inc;
      } else if(alfa + inc <= -45.0){
         animacion_neg = false;
         alfa = -45.0 + inc;
      }
      if(animacion_neg){
         inc = -1*inc;
      }
      alfa += inc;
      pierna->setAlfa(alfa);
   }
}

void BrazoRobot::incrementarTaladro(float inc){
   delta += inc;
   if(delta >= 360.0){
      delta = 0.0;
   } else if(delta <= -360.0){
      delta = 0.0;
   }
}

void BrazoRobot::setAlfa(float a){
   alfa = a;
}
