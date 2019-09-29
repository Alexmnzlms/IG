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
  glPointSize(3.0);
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
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
   // completar .....(práctica 1)
   draw_ModoInmediato();
}

void Malla3D::cambiar_modo(GLenum modo){
  modo_dibujado = modo;
}
