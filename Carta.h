#ifndef CARTA_H
#define CARTA_H

#include <string>

/*
------------------------------------------------------------
Clase: Carta
Responsabilidades:
- Conoce su valor nominal, su nombre y su tipo o palo.
- Puede mostrar su información textual.

Colaboraciones:
- Utilizada por Mano y Mazo.
------------------------------------------------------------
*/

class Carta {
public:
    Carta(const std::string& nombre, const std::string& palo, int valor);

    int getValor() const;
    std::string getNombre() const;
    std::string getPalo() const;
    std::string mostrar() const;

private:
    std::string nombre;
    std::string palo;
    int valor;
};

#endif // CARTA_H