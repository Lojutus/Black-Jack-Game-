#include "Carta.h"
#include <sstream>

Carta::Carta(const std::string& nombre, const std::string& palo, int valor)
    : nombre(nombre), palo(palo), valor(valor) {}

int Carta::getValor() const {
    return valor;
}

std::string Carta::getNombre() const {
    return nombre;
}

std::string Carta::getPalo() const {
    return palo;
}

std::string Carta::mostrar() const {
    std::ostringstream salida;
    salida << nombre << " de " << palo;
    return salida.str();
}