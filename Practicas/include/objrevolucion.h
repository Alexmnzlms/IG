// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

typedef enum {RX, RY, RZ} eje;

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
       ObjRevolucion(const std::string & archivo) ;

       ObjRevolucion(std::vector<Tupla3f> archivo) ;
       void setTextura(Textura * tex);
       void tapas();

   protected:
      int instancias;
      int vertices_perfil;
      bool tapa;
      int pos_tapas;
      bool perfilInverso(std::vector<Tupla3f> perfil_original);
      void invertirPerfil();
      void crearMalla(std::vector<Tupla3f> & perfil_original, eje eje_rotacion);
      void dibujaInmediato(int tamanio, const void * indice) override;
      void dibujaAjedrez(int tamanio, const void * indice1, const void * indice2) override;
      void dibujaDiferido(int tamanio, GLvoid * indice) override;
      void calcularCoorTex(float vertices, float instancias);
} ;




#endif
