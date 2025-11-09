#include "Mano.h"
#include <sstream>



void Mano::agregarCarta(const Carta& carta) {
    cartas.push_back(carta);
}

int Mano::calcularValor() const {
    int total = 0;
    int ases = 0;

    for (const auto& carta : cartas) {
        total += carta.getValor();
        if (carta.getNombre() == "A") ases++;
    }

    // Ajuste de Ases si se pasa de 21
    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }

    return total;
}

const std::vector<Carta>& Mano::getCartas() const {
    return cartas;
}

std::string Mano::mostrar() const {
    std::ostringstream salida;
    for (const auto& carta : cartas) {
        salida << carta.mostrar() << " | ";
    }
    return salida.str();
}

std::size_t Mano::getCantidad() const {
    return cartas.size();
}

void Mano::vaciar() {
    cartas.clear();
}