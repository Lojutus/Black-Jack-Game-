#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Mano.h"
#include "Mazo.h"

/*
------------------------------------------------------------
Clase: Jugador
Responsabilidades:
- Representa a un participante del juego.
- Puede realizar apuestas, pedir cartas o plantarse.
- Conoce su mano, su nombre y su apuesta actual.
- Determina si tiene Blackjack.

Colaboraciones:
- Interactúa con Mazo, Mano y Crupier.
------------------------------------------------------------
*/

class Jugador {
public:
    explicit Jugador(const std::string& nombre = "");

    void apostar(double cantidad);
    void recibirCarta(const Carta& carta);
    void pedirCarta(Mazo& mazo);
    bool tieneBlackjack() const;

    std::string mostrarMano() const;
    int getValorMano() const;
    bool tomaDecision() const;
    void nuevaMano();

    std::string getNombre() const;
    double getApuesta() const;
    void setApuesta(double cantidad);
    std::string getId() const { return id; }

    void setId(const std::string& nuevoId) { id = nuevoId; }
    

protected:
    std::string nombre;
    Mano mano;
    double apuesta{0.0};
    bool blackjack{false};
    std::string id;
};

#endif // JUGADOR_H