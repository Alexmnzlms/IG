#include "robot.h"

Robot::Robot(float a){
   alfa = 0.0;//a;
   beta = -2.0*a;
   cuerpo = new Edificio();
   piernai = new PiernaRobot(-alfa);
   brazoi = new BrazoRobot(alfa);
   piernad = new PiernaRobot(alfa);
   brazod = new BrazoRobot(-alfa);
}

void Robot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
   glTranslatef(0,-25*sin(alfa*M_PI/180.0),0);
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
