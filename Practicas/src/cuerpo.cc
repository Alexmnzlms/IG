#include "cuerpo.h"

Cuerpo::Cuerpo(){
   cubo = new Cubo(10);
   cilindro = new Cilindro(10,5);
   esfera = new Esfera(5);
   altura = 0.0;
   animacion_neg = false;
}

void Cuerpo::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      glPushMatrix();
         glTranslatef(0,40,0);
         glScalef(8,8,8);
         cubo->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+60,0);
         glScalef(6,12,6);
         cubo->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+120+20,0);
         glScalef(4,4,4);
         cubo->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+120+40+10,0);
         glScalef(2,2,2);
         cubo->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,altura+80+120+40+20-5,0);
         glScalef(0.3,3,0.3);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,altura+80+120+40+20+30-5,0);
         esfera->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void Cuerpo::setMaterial(Material mat){
   cubo->setMaterial(mat);
   cilindro->setMaterial(mat);
   esfera->setMaterial(mat);
}
void Cuerpo::incrementarAltura(float inc){
   if(altura + inc >= 5.0){
      animacion_neg = true;
   } else if(altura + inc <= -10.0){
      animacion_neg = false;
   }
   if(animacion_neg){
      inc = -1*inc;
   }
   altura += inc;
}

void Cuerpo::setColorSeleccion(color col){
   cubo->setColorSeleccion(col);
   cilindro->setColorSeleccion(col);
   esfera->setColorSeleccion(col);
}
