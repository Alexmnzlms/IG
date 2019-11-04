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

       void tapaSuperior();
       void tapaInferior();

   protected:
      int instancias;
      int vertices_perfil;
      bool tapaSup;
      bool tapaInf;
      bool perfilInverso(std::vector<Tupla3f> perfil_original);
      void invertirPerfil();
      void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, eje eje_rotacion);
      void quitarPolos();
      void ponTapaSup(int num_instancias, int num_vertices);
      void ponTapaInf(int num_instancias, int num_vertices);
      void quitTapaSup(int num_instancias);
      void quitTapaInf(int num_instancias);
} ;




#endif
