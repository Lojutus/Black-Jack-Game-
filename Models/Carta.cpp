#include "Carta.h"
#include <sstream>

Carta::Carta(const std::string& nombre, const std::string& palo, int valor) //Constructor
    : nombre(nombre), palo(palo), valor(valor) {}

int Carta::getValor() const {  // Funcion destinada para obtener el valor de la carta
    return valor;
}

std::string Carta::getNombre() const {  // Funcion destinada para obtener el nombre de la carta
    return nombre;
}

std::string Carta::getPalo() const {  // Funcion destinada para obtener el palo de la carta
    return palo;
}

std::string Carta::mostrar() const { // Funcion destinada para mostrar a carta 
    std::ostringstream salida;
    salida << nombre << " de " << palo;
    return salida.str();
}