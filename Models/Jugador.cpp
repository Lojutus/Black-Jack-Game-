#include "Jugador.h"
#include <iostream>



Jugador::Jugador(const std::string& nombre) : nombre(nombre) {} //constructor

void Jugador::apostar(double cantidad) { //FUnción para apostar
    apuesta = cantidad;
}

void Jugador::recibirCarta(const Carta& carta) { //Función para recibir carta a la mano
    mano.agregarCarta(carta);
}

void Jugador::pedirCarta(Mazo& mazo) { //Función para pedir carta al mazo
    if(getValorMano()<21){
        Carta carta = mazo.repartirCarta();
        mano.agregarCarta(carta);
    }
    
}


bool Jugador::tieneBlackjack() const { //Función para verificar si tiene blackjack
    return mano.getCantidad() == 2 && mano.calcularValor() == 21;
}

std::string Jugador::mostrarMano() const { //Función para mostrar la mano del jugador en formato string
    return mano.mostrar();
}

int Jugador::getValorMano() const { //Función para obtener el valor de la mano del jugador
    return mano.calcularValor();
}

bool Jugador::tomaDecision() const {
    // En una versión real, se pediría entrada del jugador.
    // Aquí, el jugador pide carta si tiene menos de 17.
    return mano.calcularValor() < 17;
}

void Jugador::nuevaMano() { //Función para asignar una nueva mano al jugador
    mano.vaciar();
    apuesta = 0.0;
    blackjack = false;
}

std::string Jugador::getNombre() const { //Función para obtener el nombre del jugador
    return nombre;
}

double Jugador::getApuesta() const { //Función para obtener la apuesta del jugador
    return apuesta;
}

void Jugador::setApuesta(double cantidad) { //Función para poner la apuesta del jugador
    apuesta = cantidad;
}