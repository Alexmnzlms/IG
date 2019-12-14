#include "brazorobot.h"

BrazoRobot::BrazoRobot(){
   pierna = new PiernaRobot();
   cono = new Cono(50,10);
}

void BrazoRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      pierna->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         glRotatef(180,1,0,0);
         cono->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void BrazoRobot::setMaterial(Material mat){
   pierna->setMaterial(mat);
   cono->setMaterial(mat);
}
