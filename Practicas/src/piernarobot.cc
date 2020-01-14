#include "piernarobot.h"

PiernaRobot::PiernaRobot(float a){
   alfa = a;
   beta = -2.0*a;
   pie = new ObjPLY("ply/pie",10);
   pierna = new ObjPLY("ply/pierna",10);
   femur = new ObjPLY("ply/femur",10);
   animacion_neg = false;

}

void PiernaRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
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
   if(alfa + inc >= 45.0){
      animacion_neg = true;
   } else if(alfa + inc <= 0.0){
      animacion_neg = false;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   alfa += inc;
   beta = -2.0*alfa;
   //std::cout << "Angulo pierna: " << alfa << std::endl;
}

float PiernaRobot::getAlfa(){
   return alfa;
}

void PiernaRobot::setAlfa(float a){
   alfa = a;
   beta = -2.0*alfa;
}

void PiernaRobot::setColorSeleccion(color col){
   pie->setColorSeleccion(col);
   pierna->setColorSeleccion(col);
   femur->setColorSeleccion(col);
}
