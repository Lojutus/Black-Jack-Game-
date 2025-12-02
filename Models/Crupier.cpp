#include "Crupier.h"
#include <iostream>


Crupier::Crupier() : Jugador("Crupier") {}

void Crupier::barajarMazo(Mazo& mazo) {
    mazo.barajar();
}
void Crupier::repartirTusCartas(Mazo& mazo){ // esta funcion es para que el crupier se reparta sus dos cartas iniciales
    this->recibirCarta(mazo.repartirCarta());
    this->recibirCarta(mazo.repartirCarta());
}


void Crupier::repartirInicial(Mazo& mazo, Jugador& jugador) { // Reparte dos cartas al jugador que se le pasa por parametro
    jugador.recibirCarta(mazo.repartirCarta());
    jugador.recibirCarta(mazo.repartirCarta());
}

std::string Crupier::mostrarManoParcial() const {// muestra la mano parcial del crupier (solo la primera carta)
    if (mano.getCantidad() > 0) {
        std::string carta =  mano.mostrar().substr(0, mano.mostrar().find("|") + 1) ;
        return carta;
    }
    return "";

}

bool Crupier::tieneAsBlando(const Mano& mano) {
    int valor = mano.calcularValor();
    int ases = 0;
    // Contar Ases
    std::vector<Carta> cartas = mano.getCartas();
    for (const auto& carta : mano.getCartas()) {
        if (carta.getNombre() == "A") ases++;
    }

    // Un As cuenta como 11 si no te pasa de 21
    while (valor > 21 && ases > 0) {
        valor -= 10; // convertir un As de 11 a 1
        ases--;
    }

    // Si sigue habiendo un As valiendo 11, es blando
    return (ases > 0 && valor <= 21);
}

std::string Crupier::determinarGanador(Jugador& jugador) {
    int valorJugador = jugador.getValorMano();
    int valorCrupier = mano.calcularValor();
    std::string resultado;
    std::cout << "\nResultado final:\n";
    std::cout << jugador.getNombre() << ": " << valorJugador << " | Crupier: " << valorCrupier << std::endl;
    resultado = resultado + jugador.getNombre() + ": " + std::to_string(valorJugador) + " | Crupier: " + std::to_string(valorCrupier) +  "\n";
    if (valorJugador > 21) {
        std::cout << "El jugador se pasa. Pierde la apuesta.\n";
        resultado =+ "El jugador " + jugador.getNombre() +  " se pasa. Pierde la apuesta.\n";
    } else if (valorCrupier > 21 || valorJugador > valorCrupier) {
        std::cout << "El jugador gana!\n";
        resultado =+  "El jugador "+ jugador.getNombre() +  " gana!\n";
    } else if (valorJugador == valorCrupier) {
        std::cout << "Empate. Se devuelve la apuesta. "+ jugador.getNombre() +" \n";
        resultado =+ "Empate. Se devuelve la apuesta. "+ jugador.getNombre() +" \n";
    } else {
        std::cout << "El crupier gana a "+ jugador.getNombre() +" . \n";
        resultado = resultado + "El crupier gana.\n";
    }
    return resultado;
}
std::string Crupier::jugar(Mazo& mazo){
    std::string respuesta =  "El crupier comienza su turno...\n";
     std::cout << "El crupier comienza su turno...\n";
    
    while (true) {
        int valor = mano.calcularValor();
        bool blando = tieneAsBlando(mano);
        respuesta =  respuesta + "Crupier tiene: " + mano.mostrar()
                  + " (valor: " + std::to_string(valor) + (blando ? ", blando" : "") + ")\n";

        std::cout << "Crupier tiene: " << mano.mostrar()
                  << " (valor: " << valor << (blando ? ", blando" : "") << ")\n";

        if (valor >= 21) {
            break; // 21 o más → se planta o pierde
        }

        // --- Estrategia experta ---
        bool pedir = false;

        if (valor < 17) {
            pedir = true;
        } else if (valor == 17 && blando) {
            // Probabilidad del 40% de plantarse si es 17 blando
            pedir = (rand() % 100 >= 40);
        } else if (valor >= 18 && valor <= 20) {
            // A veces puede arriesgar si es blando
            if (blando) {
                pedir = (rand() % 100 < 20); // 20% de riesgo extra
            }
        }

        if (!pedir) {
            respuesta =  respuesta + "Crupier se planta con " +  std::to_string(valor)+ ".\n"; 

            std::cout << "Crupier se planta con " << valor << ".\n";
            break;
        }

        // Pedir carta
        this->recibirCarta(mazo.repartirCarta());
        
    }

    int valorFinal = mano.calcularValor();
    respuesta = respuesta + "Crupier termina con: " + std::to_string(valorFinal) + ".\n \n";
    respuesta = "El crupier comienza su turno...\n Crupier termina con: " + std::to_string(valorFinal) + ".\n \n"; // En la vercion web solo se muestra el resultado final
    std::cout << "Crupier termina con: " << valorFinal << "\n";
    return respuesta; 
}