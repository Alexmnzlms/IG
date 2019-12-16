#include "brazorobot.h"

BrazoRobot::BrazoRobot(float a){
   alfa = a;
   beta = -2.0*a;
   pierna = new PiernaRobot(alfa);
   cono = new Cono(50,10);
}

void BrazoRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      pierna->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         glTranslatef(-10.5,-60*cos(alfa*M_PI/180.0),0);
         glRotatef(180,1,0,0);
         cono->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void BrazoRobot::setMaterial(Material mat){
   pierna->setMaterial(mat);
   cono->setMaterial(mat);
}

void BrazoRobot::incrementarAngulo(float inc){
   pierna->incrementarAngulo(inc);
   alfa += inc;
}
