#include "robot.h"

Robot::Robot(float a){
   alfa_brazoi = 0.0;//a;
   alfa_brazod = 0.0;
   alfa_piernas = 0.0;
   cuerpo = new Edificio();
   piernai = new PiernaRobot(-alfa_piernas);
   brazoi = new BrazoRobot(alfa_brazoi);
   piernad = new PiernaRobot(alfa_piernas);
   brazod = new BrazoRobot(alfa_brazod);
   animacion_neg = false;
}

void Robot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
   glTranslatef(0,-25*sin(alfa_piernas*M_PI/180.0),0);
      glPushMatrix();
         glTranslatef(0,50 ,0);
         glScalef(0.5,0.5,0.5);
         cuerpo->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-20,60,0);
         piernai->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(20,60,0);
         glRotatef(180,0,1,0);
         piernad->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-15,120,0);
         glRotatef(-90,1,0,0);
         brazoi->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(15,120,0);
         glRotatef(180,0,0,1);
         glRotatef(-90,1,0,0);
         brazod->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void Robot::setMaterial(Material mat){
   piernai->setMaterial(mat);
   brazoi->setMaterial(mat);
   piernad->setMaterial(mat);
   brazod->setMaterial(mat);
   cuerpo->setMaterial(mat);
}

void Robot::incrementarAnguloBrazoIzq(float inc){
   if(comparefloat(alfa_piernas + inc,45.0)){
      animacion_neg = true;
   } else if(comparefloat(alfa_piernas + inc,0.0)){
      animacion_neg = false;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   brazoi->incrementarAngulo(inc);
}
void Robot::incrementarAnguloBrazoDer(float inc){
   if(comparefloat(alfa_piernas + inc,45.0)){
      animacion_neg = true;
   } else if(comparefloat(alfa_piernas + inc,0.0)){
      animacion_neg = false;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   brazod->incrementarAngulo(inc);
}
void Robot::incrementarAnguloPiernas(float inc){
   if(comparefloat(alfa_piernas + inc,45.0)){
      animacion_neg = true;
   } else if(comparefloat(alfa_piernas + inc,0.0)){
      animacion_neg = false;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   piernad->incrementarAngulo(inc);
   piernai->incrementarAngulo(-inc);
   alfa_piernas += inc;
   std::cout << "Angulo piernas: " << alfa_piernas << std::endl;
}