#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "Mazo.h"
#include "Jugador.h"
#include "Crupier.h"

/*
------------------------------------------------------------
Clase: Juego
Responsabilidades:
- Coordina el flujo del juego Blackjack.
- Inicia partidas, evalúa rondas y gestiona pagos.
- Permite agregar jugadores y controlar la partida.

Colaboraciones:
- Utiliza Crupier, Jugador, Mazo y las manos asociadas.
------------------------------------------------------------
*/

class Juego : public Crupier {
public:
    Juego();

    void iniciarPartida();
    void evaluarRonda();
    void pagoVictoria(Jugador& jugador);
    void nuevaPartida();
    void terminarJuego();
    std::vector<int> puntajesJugadores();
    void addJugador(const Jugador& jugador);
    Jugador& getJugador(int indice);
    Mazo& getMazo();
    std::vector<Jugador>& getJugadores();
    bool partidaActiva{false};

private:
    Mazo mazo;
    
    std::vector<Jugador> jugadores;
    
};

#endif // JUEGO_H