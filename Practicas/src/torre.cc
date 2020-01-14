#include "torre.h"

Torre::Torre(){
   cilindro = new Cilindro(10,10);
   esfera = new Esfera(5);
   altura = 0.0;
   animacion_neg = false;
   cilindro->setTextura("jpg/edificio.jpg");
}

void Torre::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
   glPushMatrix();
      glPushMatrix();
         glScalef(8,8,8);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80,0);
         glScalef(6,12,6);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,200,0);
         glScalef(4,4,4);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,240,0);
         glScalef(2,2,2);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,altura+255,0);
         glScalef(0.3,3,0.3);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,altura+285,0);
         esfera->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void Torre::setMaterial(Material mat){
   cilindro->setMaterial(mat);
   esfera->setMaterial(mat);
}

void Torre::incrementarAltura(float inc){
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
