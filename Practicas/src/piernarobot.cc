#include "piernarobot.h"

PiernaRobot::PiernaRobot(){
   pie = new ObjPLY("ply/pie",10);
   pierna = new ObjPLY("ply/pierna",10);
   femur = new ObjPLY("ply/femur",10);
}

void PiernaRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      pie->draw(tipo_draw,col,modo_dibujado);
      glPushMatrix();
         float a = 0.0;
         float b = 0.0;
         glTranslatef(11,60.0*cos(a*M_PI/180.0),0);
         glRotatef(a,1,0,0);
         femur->draw(tipo_draw,col,modo_dibujado);
         glPushMatrix();
            glTranslatef(-11,-25,0);
            glRotatef(b,1,0,0);
            pierna->draw(tipo_draw,col,modo_dibujado);
         glPopMatrix();
      glPopMatrix();
   glPopMatrix();
}

void PiernaRobot::setMaterial(Material mat){
   pie->setMaterial(mat);
   pierna->setMaterial(mat);
   femur->setMaterial(mat);
}
