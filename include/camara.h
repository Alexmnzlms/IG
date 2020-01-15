#ifndef CAM_H_INCLUDED
#define CAM_H_INCLUDED

#include "aux.h"

typedef enum {ROBOT, TORRE, EDIFI, EDIFD, EDIFC, NOSEL} seleccionables;

class Camara{
private:
   Tupla3f eye;
   Tupla3f at;
   Tupla3f up;
   int tipo;
   float left, right, near, far, top, bottom;
   seleccionables seleccionado;

public:
   Camara(const Tupla3f eye, const Tupla3f at, const Tupla3f up,
          const int tipo, const float left, const float right,
          const float near, const float far, const float top,
          const float bottom);
   void rotarXExaminar(const float angle);
   void rotarYExaminar(const float angle);
   void rotarZExaminar(const float angle);
   void rotarXFirstPerson(const float angle);
   void rotarYFirstPerson(const float angle);
   void rotarZFirstPerson(const float angle);
   void mover(const float x, const float y, const float z);
   void zoom(const float factor);
   void girar(const float x, const float y);
   void setOberver();
   void setProyeccion();
   void setLetf(const float l);
   void setRight(const float l);
   void setTop(const float l);
   void setBottom(const float l);
   float getLeft() const;
   float getRight() const;
   float getTop() const;
   float getBottom() const;
   seleccionables getSeleccionado() const;
   void setSeleccionado(const seleccionables obj);
};

#endif
