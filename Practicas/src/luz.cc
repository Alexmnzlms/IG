#include "aux.h"
#include "luz.h"

Luz::Luz(){

}
void Luz::activar(){
      glEnable(id);
      glLightfv(id, GL_AMBIENT, colorAmbiente);
      glLightfv(id, GL_SPECULAR, colorEspecular);
      glLightfv(id, GL_DIFFUSE, colorDifuso);
      glLightfv(id, GL_POSITION, posicion);
}
