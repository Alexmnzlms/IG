#include "brazorobot.h"

BrazoRobot::BrazoRobot(float a){
   alfa = a;
   beta = -2.0*a;
   pie = new ObjPLY("ply/pie",10);
   pierna = new ObjPLY("ply/pierna",10);
   femur = new ObjPLY("ply/femur",10);
   cono = new Cono(50,10);
   animacion_neg = false;
}

void BrazoRobot::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
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
      glPushMatrix();
         glTranslatef(-10.5,-60*cos(alfa*M_PI/180.0),0);
         glRotatef(180,1,0,0);
         cono->draw(tipo_draw,col,modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void BrazoRobot::setMaterial(Material mat){
   pie->setMaterial(mat);
   pierna->setMaterial(mat);
   femur->setMaterial(mat);
   cono->setMaterial(mat);
}

void BrazoRobot::incrementarAngulo(float inc){
   if(comparefloat(alfa + inc,45.0)){
      animacion_neg = true;
      std::cout << "Bajo: " << alfa << std::endl;
   } else if(comparefloat(alfa + inc,0.0)){
      animacion_neg = false;
      std::cout << "Subo: " << alfa << std::endl;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   alfa += inc;
   beta = -2.0*alfa;
   std::cout << "Angulo brazo: " << alfa << std::endl;
}