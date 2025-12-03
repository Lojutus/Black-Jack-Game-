#include "ControladorJuego.h"
#include "../Models/Jugador.h"
#include "../views/MostrarInformacion.h"
#include <iostream>

ControladorJuego::ControladorJuego(){
    
}
void ControladorJuego::ejecutarPartidaCLI() {
    std::cout << "=== Bienvenido al juego de Blackjack ===\n";

    // Inicializa la partida (suponiendo que los jugadores ya se agregaron externamente)
    juegoActivo.iniciarPartida();

    MostrarInformacion vista;

    // Bucle principal (igual que tenías en main pero aquí integrado)
    while (juegoActivo.partidaActiva) {
        std::cout << juegoActivo.mostrarManoParcial() << std::endl;

        int indiceJugadorActual = getJuagadorActivo();

        Jugador& jugadorActual = juegoActivo.getJugador(indiceJugadorActual);

        std::cout << "Jugador " << jugadorActual.getNombre() << std::endl;
        std::cout << jugadorActual.mostrarMano() << std::endl;

        char eleccion = vista.pedirOrden();    // 'p' o 'd' por ejemplo
        enviarOrden(eleccion);                 // ejecuta la orden (hit/stand)

        std::cout << jugadorActual.mostrarMano() << std::endl;

        if (jugadorActual.getValorMano() > 21 || eleccion == 'd') {
            if (!cambiarJugador()) {
                juegoActivo.partidaActiva = 0; // termina la partida
            }
        }
    }

    // turno del crupier (usa tu implementación de Crupier::jugar)
    Mazo& mazo = juegoActivo.getMazo();
    juegoActivo.jugar(mazo);  // asumo que esto hace que el crupier juegue
    juegoActivo.evaluarRonda(); // imprime quien ganó (como en tu main)
}


bool ControladorJuego::enviarOrden(char orden){
    try
    {
        // p == PEDIR ; d== Dejar 
        Jugador* jugador = &juegoActivo.getJugador(jugadorActivo);
        if (orden == 'p'){
            jugador->pedirCarta(juegoActivo.getMazo());
            return 1;

        }
        return 1;
        

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    
    

}
int ControladorJuego::getJuagadorActivo(){
    return jugadorActivo;
}
bool ControladorJuego::cambiarJugador(){
    try {
    Jugador& j = juegoActivo.getJugador(jugadorActivo+ 1);
    jugadorActivo =+ 1;
    std::cout<< "JUGADOR "<< j.getNombre() << " ACTIVO " <<std::endl;
    return 1;
    } catch (const std::out_of_range& e) {
        jugadorActivo = 0;
        std::cout<<" FIN DE LA RONDA" << std::endl;
        return 0;
    }
    

}
