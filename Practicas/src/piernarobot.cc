#include "piernarobot.h"

PiernaRobot::PiernaRobot(float a){
   alfa = a;
   beta = -2.0*a;
   pie = new ObjPLY("ply/pie",10);
   pierna = new ObjPLY("ply/pierna",10);
   femur = new ObjPLY("ply/femur",10);

}

void PiernaRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      /*
      pie->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         float a = 0.0;
         float b = -2.0*a;
         glTranslatef(11,60.0*cos(a*M_PI/180.0),0);
         glRotatef(a,1,0,0);
         femur->draw(tipo_draw,col,modo_dibujado);
         glPushMatrix();
            glTranslatef(-11,-25,0);
            glRotatef(b,1,0,0);
            pierna->draw(tipo_draw,col,modo_dibujado);
         glPopMatrix();
      glPopMatrix();
      */
      glPushMatrix();
         glRotatef(alfa,1,0,0);
         femur->draw(tipo_draw,col,modo_dibujado);
         glPushMatrix();
            glTranslatef(-10.5,-25,0);
            glRotatef(beta,1,0,0);
            pierna->draw(tipo_draw,col,modo_dibujado);
         glPopMatrix();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(-10.5,-60*cos(alfa*M_PI/180.0),0);
         pie->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void PiernaRobot::setMaterial(Material mat){
   pie->setMaterial(mat);
   pierna->setMaterial(mat);
   femur->setMaterial(mat);
}
void PiernaRobot::incrementarAngulo(float inc){
   alfa += inc;
   beta = 2.0*-1*alfa;
}
