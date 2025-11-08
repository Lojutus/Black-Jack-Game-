#include "ControladorJuego.h"
#include "Jugador.h"
#include <iostream>

ControladorJuego::ControladorJuego(){
    
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