#ifndef ControladorJuego_H
#define ControladorJuego_H

#include "Juego.h"
#include "Mano.h"

/*
------------------------------------------------------------
Clase: ControladorJuego_H
Responsabilidades:
- se encarga de iterar los jugadores
- administra las funciones de juego 
- actualiza la vista 

Colaboraciones:
- posee a jeugo
- instancia objetos de vista
------------------------------------------------------------
*/

class ControladorJuego  {

private:

int jugadorActivo= 0;



public:
    Juego juegoActivo;
    ControladorJuego();
    int  getJuagadorActivo();
    bool enviarOrden(char orden);
    bool cambiarJugador();
    Mano obtenerManoJugadorActual() const;
    
};

#endif // CRUPIER_H