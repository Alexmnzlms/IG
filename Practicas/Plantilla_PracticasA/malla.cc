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
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glColorPointer(3, GL_FLOAT, 0, c.data() );
  glPolygonMode( GL_FRONT_AND_BACK, modo_dibujado );
  glEnable( GL_CULL_FACE );
  glPointSize(5.0);
  glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT,f.data() );
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
   switch(modo_dibujado){
      case GL_POINT:
         c.clear();
         for(int i = 0; i < v.size(); i++){
            Tupla3f rgb(255,0,0);
            c.push_back(rgb);
         }
         break;
      case GL_LINE:
         c.clear();
         for(int i = 0; i < v.size(); i++){
            Tupla3f rgb(0,0,0);
            c.push_back(rgb);
         }
         break;
      case GL_FILL:
         c.clear();
         if(ajedrez){
            
         }
         else{
            for(int i = 0; i < v.size(); i++){
               Tupla3f rgb(0,0,255);
               c.push_back(rgb);
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

void Malla3D::cambiar_modo(GLenum modo, bool aj){
  modo_dibujado = modo;
  ajedrez = aj;
}

void Malla3D::cambiar_draw(dibujo draw){
  tipo_draw = draw;
}
