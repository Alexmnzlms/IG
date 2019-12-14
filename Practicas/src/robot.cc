#include "robot.h"

Robot::Robot(){
   cuerpo = new Edificio();
   pierna = new PiernaRobot();
   brazo = new BrazoRobot();
}

void Robot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      glPopMatrix();
         glTranslatef(0,50 ,0);
         glScalef(0.5,0.5,0.5);
         cuerpo->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-25,0,0);
         pierna->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(25,0,0);
         glRotatef(180,0,1,0);
         pierna->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-25,100,0);
         glRotatef(-90,1,0,0);
         glTranslatef(0,-60,0);
         brazo->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(25,100,0);
         glRotatef(-90,1,0,0);
         glRotatef(180,0,1,0);
         glTranslatef(0,-60,0);
         brazo->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void Robot::setMaterial(Material mat){
   pierna->setMaterial(mat);
   brazo->setMaterial(mat);
   cuerpo->setMaterial(mat);
}
