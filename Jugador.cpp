#include "Jugador.h"
#include <iostream>



Jugador::Jugador(const std::string& nombre) : nombre(nombre) {}

void Jugador::apostar(double cantidad) {
    apuesta = cantidad;
}

void Jugador::recibirCarta(const Carta& carta) {
    mano.agregarCarta(carta);
}

void Jugador::pedirCarta(Mazo& mazo) {
    if(getValorMano()<21){
        Carta carta = mazo.repartirCarta();
        mano.agregarCarta(carta);
    }
    
}

bool Jugador::tieneBlackjack() const {
    return mano.getCantidad() == 2 && mano.calcularValor() == 21;
}

std::string Jugador::mostrarMano() const {
    return mano.mostrar();
}

int Jugador::getValorMano() const {
    return mano.calcularValor();
}

bool Jugador::tomaDecision() const {
    // En una versión real, se pediría entrada del jugador.
    // Aquí, el jugador pide carta si tiene menos de 17.
    return mano.calcularValor() < 17;
}

void Jugador::nuevaMano() {
    mano.vaciar();
    apuesta = 0.0;
    blackjack = false;
}

std::string Jugador::getNombre() const {
    return nombre;
}

double Jugador::getApuesta() const {
    return apuesta;
}

void Jugador::setApuesta(double cantidad) {
    apuesta = cantidad;
}