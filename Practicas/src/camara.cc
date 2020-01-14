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
void Camara::rotarXExaminar(const float angle){
   eye = eye - at;
   Tupla3f eyeOriginal = eye;
   eye(1) = eyeOriginal(1) * cos(angle) - eyeOriginal(2) * sin(angle);
   eye(2) = eyeOriginal(1) * sin(angle) + eyeOriginal(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarYExaminar(const float angle){
   eye = eye - at;
   Tupla3f eyeOriginal = eye;
   eye(0) = eyeOriginal(0) * cos(angle) + eyeOriginal(2) * sin(angle);
   eye(2) = eyeOriginal(0)* -1 * sin(angle) + eyeOriginal(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarZExaminar(const float angle){
   eye = eye - at;
   Tupla3f eyeOriginal = eye;
   eye(0) = eyeOriginal(0) * cos(angle) - eyeOriginal(2) * sin(angle);
   eye(1) = eyeOriginal(0) * sin(angle) + eyeOriginal(2) * cos(angle);
   eye = eye + at;
}

void Camara::rotarXFirstPerson(const float angle){
   at = at - eye;
   Tupla3f atOriginal = at;
   at(1) = atOriginal(1) * cos(angle) - atOriginal(2) * sin(angle);
   at(2) = atOriginal(1) * sin(angle) + atOriginal(2) * cos(angle);
   at = at + eye;
}
void Camara::rotarYFirstPerson(const float angle){
   at = at - eye;
   Tupla3f atOriginal = at;
   at(0) = atOriginal(0) * cos(angle) + atOriginal(2) * sin(angle);
   at(2) = atOriginal(0)* -1 * sin(angle) + atOriginal(2) * cos(angle);
   at = at + eye;
}
void Camara::rotarZFirstPerson(const float angle){
   at = at - eye;
   Tupla3f atOriginal = at;
   at(0) = atOriginal(0) * cos(angle) - atOriginal(2) * sin(angle);
   at(1) = atOriginal(0) * sin(angle) + atOriginal(2) * cos(angle);
   at = at + eye;
}

void Camara::mover(const float x, const float y, const float z){

}
void Camara::zoom(const float factor){
   right = right * factor;
   left = left * factor;
   top = top * factor;
   bottom = bottom * factor;
}
void Camara::girar(const float x, const float y){
   rotarXFirstPerson(y*0.25*M_PI/180.0);
   rotarYFirstPerson(x*0.25*M_PI/180.0);
   //rotarXExaminar(y*M_PI/180.0);
   //rotarYExaminar(x*M_PI/180.0);
}
void Camara::setOberver(){
   gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}
void Camara::setProyeccion(){
   std::cout << "Tipo: " << tipo << std::endl;
   switch (tipo) {
      case 0:
         glFrustum(left,right,bottom,top,near,far);
         break;
      case 1:
         glOrtho(left,right,bottom,top,near,far);
         break;

   }
}
void Camara::setLetf(const float l){
   left = l;
}

float Camara::getLeft() const{
   return left;
}

void Camara::setRight(const float l){
   right = l;
}

float Camara::getRight() const{
   return right;
}

void Camara::setTop(const float l){
   top = l;
}

float Camara::getTop() const{
   return top;
}

void Camara::setBottom(const float l){
   bottom = l;
}

float Camara::getBottom() const{
   return bottom;
}
