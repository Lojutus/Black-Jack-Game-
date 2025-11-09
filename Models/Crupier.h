#ifndef CRUPIER_H
#define CRUPIER_H

#include "Jugador.h"
#include "Mazo.h"

/*
------------------------------------------------------------
Clase: Crupier
Responsabilidades:
- Barajar el mazo y repartir cartas a los jugadores.
- Mostrar parcialmente su mano.
- Determinar el ganador de la ronda según las reglas del juego.

Colaboraciones:
- Interactúa con Mazo, Jugador y Mano.
------------------------------------------------------------
*/

class Crupier : public Jugador {
public:
    Crupier();

    void barajarMazo(Mazo& mazo);
    void repartirInicial(Mazo& mazo, Jugador& jugador);
    std::string mostrarManoParcial() const;
    void repartirTusCartas(Mazo& mazo);
    void determinarGanador(Jugador& jugador);
    void jugar(Mazo& mazo); // sid evuelve true es que quiere seguir jugando 
    bool tieneAsBlando(const Mano& mano);
};

#endif // CRUPIER_H