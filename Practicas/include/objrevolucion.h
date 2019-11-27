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
       ObjRevolucion(const std::string & archivo,
                     int num_instancias,
                     int mult,
                     eje eje_rotacion,
                     bool tapa_sup=true,
                     bool tapa_inf=true) ;

       ObjRevolucion(std::vector<Tupla3f> archivo,
                     int num_instancias,
                     eje eje_rotacion,
                     bool tapa_sup=true,
                     bool tapa_inf=true) ;

       void tapas();

   protected:
      int instancias;
      int vertices_perfil;
      bool tapa;
      bool perfilInverso(std::vector<Tupla3f> perfil_original);
      void invertirPerfil();
      void crearMalla(std::vector<Tupla3f> & perfil_original, eje eje_rotacion);
      void quitarPolos(std::vector<Tupla3f> & perfil_original);
      void dibujaInmediato(int tamanio, const void * indice);
      void dibujaDiferido(int tamanio);
} ;




#endif
