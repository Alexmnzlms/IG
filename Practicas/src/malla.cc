#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

Malla3D::Malla3D(){
}

void Malla3D::draw_ModoInmediato()
{
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glPointSize(3.0);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   dibujaInmediato(f.size(),f.data());
   glDisableClientState( GL_VERTEX_ARRAY );
}

void Malla3D::draw_ModoAjedrez()
{
   std::vector<Tupla3i> f1;
   std::vector<Tupla3i> f2;
   for(int i = 0; i < f.size(); i++){
      if(i%2==0){
         f1.push_back(f[i]);
      }
      else{
         f2.push_back(f[i]);
      }
   }
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glEnableClientState(GL_COLOR_ARRAY);
   dibujaAjedrez(f.size(),f1.data(),f2.data());
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
   glPointSize(5.0);
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer( 3, GL_FLOAT, 0, 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0);
   glEnableClientState( GL_VERTEX_ARRAY );
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   dibujaDiferido(f.size(),f.data());
}

void Malla3D::draw_ModoSuave(){
   glEnable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glNormalPointer( GL_FLOAT, 0, nv.data() );
   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_NORMAL_ARRAY );
   dibujaInmediato(f.size(),f.data());
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
}

void Malla3D::draw_ModoPlano(){
   glEnable(GL_LIGHTING);
   glShadeModel(GL_FLAT);
   glVertexPointer( 3, GL_FLOAT, 0, v.data() );
   glNormalPointer( GL_FLOAT, 0, nv.data() );
   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_NORMAL_ARRAY );
   dibujaInmediato(f.size(),f.data());
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(dibujo tipo, color col)
{
   if(ver){
      switch(col){
         case NEGRO:
            c = cnegro;
            break;
         case AZUL:
            c = cazul;
            break;
         case VERDE:
            c = cverde;
            break;
         case CIAN:
            c = ccian;
            break;
         case ROJO:
            c = crojo;
            break;
         case ROSA:
            c = crosa;
            break;
         case AMARILLO:
            c = camarillo;
            break;
         case MORADO:
            c= cmorado;
            break;
      }
      if(tipo == CHESS){
         c_aux = cnegro;
      } else {
         c_aux.clear();
      }

      //m.aplicar

      switch(tipo){
         case INMED:
            draw_ModoInmediato();
            break;
         case DIFER:
            draw_ModoDiferido();
            break;
         case CHESS:
            draw_ModoAjedrez();
            break;
         case SMUZ:
            draw_ModoSuave();
         case PLAIN:
            draw_ModoPlano();
      }
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

void Malla3D::calcular_colores(){
   Tupla3f negro(0.0f,0.0f,0.0f);
   Tupla3f azul(0.0f,0.0f,1.0f);
   Tupla3f verde(0.0f,1.0f,0.0f);
   Tupla3f cian(0.0f,1.0f,1.0f);
   Tupla3f rojo(1.0f,0.0f,0.0f);
   Tupla3f rosa(1.0f,0.0f,1.0f);
   Tupla3f amarillo(1.0f,1.0f,0.0f);
   Tupla3f morado(0.5f,0.0f,0.5f);

   for(int i = 0; i < v.size(); i++){
      cnegro.push_back(negro);
   }
   for(int i = 0; i < v.size(); i++){
      cazul.push_back(azul);
   }
   for(int i = 0; i < v.size(); i++){
      cverde.push_back(verde);
   }
   for(int i = 0; i < v.size(); i++){
      ccian.push_back(cian);
   }
   for(int i = 0; i < v.size(); i++){
      crojo.push_back(rojo);
   }
   for(int i = 0; i < v.size(); i++){
      crosa.push_back(rosa);
   }
   for(int i = 0; i < v.size(); i++){
      camarillo.push_back(amarillo);
   }
   for(int i = 0; i < v.size(); i++){
      cmorado.push_back(morado);
   }
}

void Malla3D::alternar_vista(){
   ver = !ver;
}

void Malla3D::calcular_normales(){
   nv.resize(v.size());
   Tupla3f a, b, nc;
   for(int i = 0; i < f.size(); i++){
      a = v[f[i](1)] - v[f[i](0)];
      b = v[f[i](2)] - v[f[i](0)];
      nc = a.cross(b);
      nv[f[i](0)] = nv[f[i](0)] + nc.normalized();
      nv[f[i](1)] = nv[f[i](1)] + nc.normalized();
      nv[f[i](2)] = nv[f[i](2)] + nc.normalized();
   }
   for(int i = 0; i < nv.size(); i++){
      nv[i] = nv[i].normalized();
   }

}

void Malla3D::dibujaInmediato(int tamanio, const void * indice){
   glDrawElements( GL_TRIANGLES, tamanio*3, GL_UNSIGNED_INT,indice );
}

void Malla3D::dibujaDiferido(int tamanio, GLvoid * indice){
   id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*tamanio * sizeof(int), indice);
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements( GL_TRIANGLES, tamanio*3, GL_UNSIGNED_INT, 0);
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Malla3D::dibujaAjedrez(int tamanio, const void * indice1, const void * indice2){
   glColorPointer(3, GL_FLOAT, 0, c.data() );
   glDrawElements( GL_TRIANGLES, (tamanio/2)*3, GL_UNSIGNED_INT,indice1);
   glColorPointer(3, GL_FLOAT, 0, c_aux.data() );
   glDrawElements( GL_TRIANGLES, (tamanio/2)*3, GL_UNSIGNED_INT,indice2);
}

void Malla3D::setMaterial(Material mat){
   m = mat;
}
