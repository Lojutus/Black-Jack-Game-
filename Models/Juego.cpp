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
Jugador& Juego::getJugador(int indice){ // devuelve el jugador actualmente activo
    if (jugadores.empty()) {
        throw std::out_of_range("No hay jugadores registrados.");
    }
    if (indice < static_cast<int>(jugadores.size())){
        return jugadores[indice];
    }
    throw std::out_of_range("Índice de jugador fuera de rango.");
}
void Juego::addJugador(const Jugador& jugador) { // añade un jugador al juego
    jugadores.push_back(jugador);
}

void Juego::iniciarPartida() { // inicia una nueva partida
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
std::vector<int> Juego::puntajesJugadores(){ // devuelve un vector con los puntajes de todos los jugadores
    std::vector<int> resultado;
    for( auto jugador : jugadores){
        resultado.push_back(jugador.getValorMano());
    }
    return resultado;
}

std::string Juego::evaluarRonda() { // evalúa la ronda actual y devuelve un resumen de resultados
    std::string resultado = "";
    for (auto& jugador : jugadores) {
        
        resultado = resultado +  determinarGanador(jugador) + "\n" ;
    }
    return resultado;
    
}

void Juego::pagoVictoria(Jugador& jugador) {// dice cuanto gana el jugador
    // Lógica de pago (simplificada)
    if (jugador.getValorMano() <= 21)
        std::cout << jugador.getNombre() << " gana $" << jugador.getApuesta() * 2 << "\n";
}

void Juego::nuevaPartida() { // borra a todos los jugadoires
    for (auto& jugador : jugadores) {
        jugador.nuevaMano();
    }
    nuevaMano();
    terminarJuego(); // PARA LA VERCION WEB SE DEJA ASI, SE BORRAN LOS JUGADORES
    partidaActiva = false;
}

void Juego::terminarJuego() { // termina el juego y borra a los jugadores
    jugadores.clear();
    partidaActiva = false;
    std::cout << "Juego terminado.\n";
}

std::vector<Jugador>& Juego::getJugadores(){ // devuelve la lista de jugadores
    return jugadores;
}