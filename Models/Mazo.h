#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"

/*
------------------------------------------------------------
Clase: Mazo
Responsabilidades:
- Almacena y gestiona los objetos Carta.
- Permite barajar el orden de las cartas y repartirlas.
- Conoce cuántas cartas quedan en el mazo.

Colaboraciones:
- Interactúa con Crupier, Jugador y Carta.
------------------------------------------------------------
*/

class Mazo {
public:
    Mazo();
    void barajar();
    Carta repartirCarta();
    int cartasRestantes() const;
    void reiniciar();

private:
    std::vector<Carta> cartas;
};

#endif // MAZO_H