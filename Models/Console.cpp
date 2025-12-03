
#include "Console.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void Console::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void Console::waitForKeyPress() {
  std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
  std::cin.ignore();
  std::cin.get();
} // ESPERA A QUE EL USUARIO PRESIONE UNA TECLA
Console::Console() {}
// Funciones para mostrar mensajes (POlimorfismo al recibir string)
void Console::showInfoMessage(const std::string &message) {
  std::cout << "[                   INFO                 ] \n" << message << std::endl;
}
// Funciones para mostrar mensajes (POlimorfismo al recibir char* referencia)
void Console::showInfoMessage(const char* message) {
        std::cout << "[                   INFO                 ] \n" << message << std::endl;
    }