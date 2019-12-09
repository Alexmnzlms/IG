#include "edificio.h"

Edificio::Edificio(){
   cubo = new Cubo(10);
}
void Edificio::draw(dibujo tipo, color col, GLenum modo_dibujado){
   glPushMatrix();
      glPushMatrix();
         glTranslatef(0,40,0);
         glScalef(8,8,8);
         glPolygonMode( GL_FRONT, modo_dibujado );
         cubo->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+60,0);
         glScalef(6,12,6);
         glPolygonMode( GL_FRONT, modo_dibujado );
         cubo->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+120+20,0);
         glScalef(4,4,4);
         glPolygonMode( GL_FRONT, modo_dibujado );
         cubo->draw(tipo_draw, col);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,80+120+40+10,0);
         glScalef(2,2,2);
         glPolygonMode( GL_FRONT, modo_dibujado );
         cubo->draw(tipo_draw, col);
      glPopMatrix();
   glPopMatrix();
}

void Edificio::setMaterial(Material mat){
   cubo->setMaterial(*mat);
}
