#include "brazorobot.h"

BrazoRobot::BrazoRobot(float a, bool izq){
   alfa = a;
   delta = 0.0;
   pierna = new PiernaRobot(a);
   cono = new Cono(50,10);
   animacion_neg = false;
   izquierda = izq;
   Tupla4f amb = {0.0,0.0,0.0,1.0};
   Tupla4f dif = {1.0,1.0,1.0,1.0};
   Tupla4f esp = {1.0,1.0,1.0,1.0};
   Tupla3f dir = {0.0,1.0,0.0};
   Tupla3f pos = {0.0,0.0,0.0};
   luzpos = new LuzPosicional(pos, GL_LIGHT3, amb, dif, esp);
   //Textura * taladro = new Textura("jpg/text-lata-1.jpg");
   //cono->setTextura(taladro);
}

void BrazoRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      pierna->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         glTranslatef(-10.5,-60*cos(pierna->getAlfa()*M_PI/180.0),0);
         glRotatef(180,1,0,0);
         glRotatef(delta,0,1,0);
         cono->draw(tipo_draw,col,modo_dibujado);
         luzpos->activar();
      glPopMatrix();
   glPopMatrix();
}

void BrazoRobot::setMaterial(Material mat){
   pierna->setMaterial(mat);
   cono->setMaterial(mat);
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
      //std::cout << "Angulo brazo: " << alfa << std::endl;
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
      //std::cout << "Angulo brazo: " << alfa << std::endl;
   }
}

void BrazoRobot::incrementarTaladro(float inc){
   delta += inc;
   if(delta >= 360.0){
      delta = 0.0;
   } else if(delta <= -360.0){
      delta = 0.0;
   }
   //std::cout << "Angulo taladro: " << delta << std::endl;
}

void BrazoRobot::setAlfa(float a){
   alfa = a;
}
