
#include "web.h"
#include "httplib.h"
#include <iostream>
/*

    Proyecto: BlackJack
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle
    Repositorio: https://github.com/Lojutus/Black-Jack-Game-.git
*/
int main() {
    try
    {
         httplib::Server svr;
        definirRutas(svr);

        std::cout << "Servidor escuchando en http://0.0.0.0:8080\n";
        svr.listen("0.0.0.0", 8080);

    return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   
}

   


