#ifndef MANO_H
#define MANO_H

#include <vector>
#include <string>
#include "Carta.h"

/*
------------------------------------------------------------
Clase: Mano
Responsabilidades:
- Añade y almacena las cartas obtenidas por Jugador o Crupier.
- Calcula el valor total de la mano según las reglas del Blackjack.
- Muestra las cartas y conoce su cantidad.

Colaboraciones:
- Utiliza objetos de la clase Carta.
------------------------------------------------------------
*/

class Mano {
public:
    void agregarCarta(const Carta& carta);
    int calcularValor() const;
    std::string mostrar() const;
    std::size_t getCantidad() const;
    void vaciar();
    const std::vector<Carta>& getCartas() const;

private:
    std::vector<Carta> cartas;
};

#endif // MANO_H