
#include "web.h"
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;
    definirRutas(svr);

    std::cout << "Servidor escuchando en http://0.0.0.0:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}

   

