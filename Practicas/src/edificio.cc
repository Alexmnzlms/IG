#include "edificio.h"

Edificio::Edificio(){
   cubo = new Cubo(10);
   cilindro = new Cilindro(10,5);
   esfera = new Esfera(5);
}

void Edificio::draw(dibujo tipo_draw, color col, GLenum modo_dibujado){
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
         glTranslatef(0,80+120+40+20,0);
         glScalef(0.3,3,0.3);
         cilindro->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+120+40+20+30,0);
         esfera->draw(tipo_draw, col, modo_dibujado);
      glPopMatrix();
   glPopMatrix();
}

void Edificio::setMaterial(Material mat){
   cubo->setMaterial(mat);
   cilindro->setMaterial(mat);
   esfera->setMaterial(mat);
}
