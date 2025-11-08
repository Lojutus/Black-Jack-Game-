#include "Juego.h"
#include <iostream>

/*
------------------------------------------------------------
Implementación de la clase: Juego
Responsabilidades:
- Controlar el flujo del juego.
- Iniciar partida, repartir, evaluar y pagar resultados.
------------------------------------------------------------
*/

Juego::Juego() : partidaActiva(false) {}

Mazo& Juego::getMazo(){
    return mazo;
}
Jugador& Juego::getJugador(int indice){
    if (jugadores.empty()) {
        throw std::out_of_range("No hay jugadores registrados.");
    }
    if (indice < static_cast<int>(jugadores.size())){
        return jugadores[indice];
    }
    throw std::out_of_range("Índice de jugador fuera de rango.");
}
void Juego::addJugador(const Jugador& jugador) {
    jugadores.push_back(jugador);
}

void Juego::iniciarPartida() {
    if (jugadores.empty()) {
        std::cout << "No hay jugadores registrados.\n";
        return;
    }

    partidaActiva = true;
    mazo.reiniciar();
    barajarMazo(mazo);
    repartirTusCartas(mazo); // te da tus dos cartas
    for (auto& jugador : jugadores) {
        repartirInicial(mazo, jugador); // les da a cada jugador dos cartas
    }

    
}
std::vector<int> Juego::puntajesJugadores(){
    std::vector<int> resultado;
    for( auto jugador : jugadores){
        resultado.push_back(jugador.getValorMano());
    }
    return resultado;
}

void Juego::evaluarRonda() {
    for (auto& jugador : jugadores) {
        
        determinarGanador(jugador);
    }
    
}

void Juego::pagoVictoria(Jugador& jugador) {
    // Lógica de pago (simplificada)
    if (jugador.getValorMano() <= 21)
        std::cout << jugador.getNombre() << " gana $" << jugador.getApuesta() * 2 << "\n";
}

void Juego::nuevaPartida() {
    for (auto& jugador : jugadores) {
        jugador.nuevaMano();
    }
    nuevaMano();
    partidaActiva = false;
}

void Juego::terminarJuego() {
    jugadores.clear();
    partidaActiva = false;
    std::cout << "Juego terminado.\n";
}

