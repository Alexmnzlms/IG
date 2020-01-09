#include "camara.h"

Camara::Camara(const Tupla3f eye, const Tupla3f at, const Tupla3f up,
               const int tipo, const float left, const float right,
               const float near, const float far, const float top,
               const float bottom){
   this->eye = eye;
   this->at = at;
   this->up = up;
   this->tipo = tipo;
   this->left = left;
   this->right = right;
   this->near = near;
   this->far = far;
   this->top = top;
   this->bottom = bottom;

}
void Camara::rotarXExaminar(const float angle){}
void Camara::rotarYExaminar(const float angle){}
void Camara::rotarZExaminar(const float angle){}
void Camara::rotarXFirstPerson(const float angle){}
void Camara::rotarYFirstPerson(const float angle){}
void Camara::rotarZFirstPerson(const float angle){}
void Camara::mover(const float x, const float y, const float z){}
void Camara::zoom(const float factor){}
void Camara::setOberver(){
   gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}
void Camara::setProyeccion(){
   switch (tipo) {
      case 0:
         glFrustum(left,right,bottom,top,near,far);
         break;
      case 1:
         glOrtho(left,right,bottom,top,near,far);
         break;

   }
}
