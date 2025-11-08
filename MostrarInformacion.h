#ifndef MostrarInformacion_H
#define MostrarInformacion_H
#include "Mano.h"

/*
------------------------------------------------------------
Clase: MostrarInformacion
Responsabilidades:
- muestraInformacion sobre los jugadores

Colaboraciones:

------------------------------------------------------------
*/

class MostrarInformacion  {
public:
    MostrarInformacion();

    void mostrarManoJugador(Mano& manoMostrar);
    char pedirOrden();
};

#endif // CRUPIER_H