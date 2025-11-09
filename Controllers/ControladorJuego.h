#ifndef ControladorJuego_H
#define ControladorJuego_H

#include "../Models/Juego.h"
#include "../Models/Mano.h"

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
    bool enviarOrden(char orden);  // 'p' = pedir, 'd' = plantarse (según tu convención)
    bool cambiarJugador(); // avanza al siguiente jugador; devuelve false si no hay más
    Mano obtenerManoJugadorActual() const;
    void ejecutarPartidaCLI();               // encapsula todo el flujo que estaba en main
    
};

#endif // CRUPIER_H