#include <iostream>
#include <limits>
#include "ControladorJuego.h"
#include "MostrarInformacion.h"
/* Link al repositorio: https://github.com/Lojutus/Black-Jack-Game- 
Trabajo de :
Integrantes: 
Jhenyl Abrahan Ybañez Montilla – 2418114  
José David Hurtado Gómez – 2519500  
Juan Sebastián Duarte Quintero – 2516473  
Santiago Torres Martínez - 2521423  
*/
int main() {
    std::cout << "=== Bienvenido al juego de Blackjack ===\n";
    // Creamos un jeugo
    ControladorJuego juego;
    // Crear jugador
    std::string nombre;
    std::cout << "Ingrese su nombre: ";
    std::getline(std::cin, nombre);
    Jugador jugador(nombre);

    // Añadimos el jugador al juego

    juego.juegoActivo.addJugador(jugador);
    
    // inicializamos el juego

     juego.juegoActivo.iniciarPartida(); 

    // Listo para jugar
    
    while(juego.juegoActivo.partidaActiva){
        std::cout<<juego.juegoActivo.mostrarManoParcial()<<std::endl;
        
        MostrarInformacion vista ;

        int indiceJugadorActual = juego.getJuagadorActivo(); 

        Jugador& jugadorActual = juego.juegoActivo.getJugador(indiceJugadorActual);

        std::cout<< "Jugador "<< jugadorActual.getNombre()<< std::endl;

        std::cout<<jugadorActual.mostrarMano()<<std::endl;

        char eleccion = vista.pedirOrden();
        juego.enviarOrden(eleccion);

        std::cout<<jugadorActual.mostrarMano()<<std::endl;

        if(jugadorActual.getValorMano()>21 || eleccion=='d' ){
            if(!juego.cambiarJugador()){
                juego.juegoActivo.partidaActiva=0;
            }
        }
        
        
    }
    std::cout<<" PUNTAJES" << std::endl;
        for(auto puntaje : juego.juegoActivo.puntajesJugadores()){
            std::cout<< std::to_string(puntaje)<< std::endl;
        }
    Mazo& mazo =  juego.juegoActivo.getMazo();
    juego.juegoActivo.jugar(mazo);

    juego.juegoActivo.evaluarRonda(); // esto imprime quien gano 
   
}
