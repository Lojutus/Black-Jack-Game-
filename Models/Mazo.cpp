#include "Mazo.h"
#include <algorithm>
#include <random>
#include <ctime>


Mazo::Mazo() {
    reiniciar();
}

void Mazo::barajar() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(cartas.begin(), cartas.end(), std::default_random_engine(std::rand()));
}

Carta Mazo::repartirCarta() {
    if (cartas.empty()) {
        reiniciar();
        barajar();
        
    }
    Carta carta = cartas.back();
    cartas.pop_back();
    return carta;
}

int Mazo::cartasRestantes() const {
    return static_cast<int>(cartas.size());
}

void Mazo::reiniciar() {
    cartas.clear();
    std::vector<std::string> palos = {"Corazones", "Diamantes", "Tréboles", "Picas"};
    std::vector<std::string> nombres = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    for (const auto& palo : palos) {
        for (const auto& nombre : nombres) {
            int valor = 0;
            if (nombre == "A") valor = 11;
            else if (nombre == "J" || nombre == "Q" || nombre == "K") valor = 10;
            else valor = std::stoi(nombre);
            cartas.emplace_back(nombre, palo, valor);
        }
    }
    barajar();
}