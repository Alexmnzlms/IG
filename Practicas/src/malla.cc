#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
   glEnable( GL_CULL_FACE );
   glPointSize(3.0);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT,f.data() );
   glDisableClientState( GL_VERTEX_ARRAY );
}

void Malla3D::draw_ModoAjedrez()
{
   glEnableClientState( GL_VERTEX_ARRAY );

   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
   glEnable( GL_CULL_FACE );
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   glDrawElements( GL_TRIANGLES, f1.size()*3, GL_UNSIGNED_INT,f1.data() );
   glColorPointer(3, GL_FLOAT, 0, c_aux.data() );
   glDrawElements( GL_TRIANGLES, f2.size()*3, GL_UNSIGNED_INT,f2.data() );
   glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
   if(id_vbo_ver == 0 || id_vbo_tri == 0){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, (3*v.size()) * sizeof(float), v.data());
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, (3*f.size()) * sizeof(int), f.data());
   }
   glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
   glEnable( GL_CULL_FACE );
   glPointSize(5.0);
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer( 3, GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0);
   glEnableClientState( GL_VERTEX_ARRAY );
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
   // completar .....(práctica 1)
   Tupla3f rgb1(0,255,0);
   Tupla3f rgb2(0,0,0);
   Tupla3f rgbpi(255,0,0);
   Tupla3f rgbpd(255,255,0);
   Tupla3f rgbli(0,0,0);
   Tupla3f rgbld(0,255,0);
   Tupla3f rgbfi(0,0,255);
   Tupla3f rgbfd(255,0,255);

   switch(modo_dibujado){
      case GL_POINT:
         c.clear();
         for(int i = 0; i < v.size(); i++){
            switch (tipo_draw) {
               case INMED:
                  c.push_back(rgbpi);
                  break;
               case DIFER:
                  c.push_back(rgbpd);
                  break;
            }
         }
         break;
      case GL_LINE:
         c.clear();
         for(int i = 0; i < v.size(); i++){
            switch (tipo_draw) {
               case INMED:
                  c.push_back(rgbli);
                  break;
               case DIFER:
                  c.push_back(rgbld);
                  break;
            }
         }
         break;
      case GL_FILL:
         c.clear();
         for(int i = 0; i < v.size(); i++){
            switch (tipo_draw) {
               case INMED:
                  c.push_back(rgbfi);
                  break;
               case DIFER:
                  c.push_back(rgbfd);
                  break;
               case CHEST:
                  c.clear();
                  c_aux.clear();
                  for(int i = 0; i < v.size(); i++){
                     c.push_back(rgb1);
                     c_aux.push_back(rgb2);
                  }
                  for(int i = 0; i < f.size(); i++){
                     if(i%2==0){
                        f1.push_back(f[i]);
                     }
                     else{
                        f2.push_back(f[i]);
                     }
                  }
                  break;
            }
         }
         break;
   }
   switch(tipo_draw){
      case INMED:
         draw_ModoInmediato();
         break;
      case DIFER:
         draw_ModoDiferido();
         break;
      case CHEST:
         draw_ModoAjedrez();
         break;
   }
}

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ){
   GLuint id_vbo;
   glGenBuffers(1, & id_vbo );
   glBindBuffer( tipo_vbo, id_vbo);
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo, 0);
   return id_vbo;
}

void Malla3D::cambiar_modo(GLenum modo){
  modo_dibujado = modo;
}

void Malla3D::cambiar_draw(dibujo draw){
  tipo_draw = draw;
}
