#include "web.h"
#include "Controllers/ControladorJuego.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <ctime>
#include <cstdlib>

// ----- Estado global (una sola partida en memoria) -----
static std::unique_ptr<ControladorJuego> partidaGlobal = nullptr;
static bool reiniciandoPartida = false;
std::string jsonFinal = "";

// ----- Helpers -----
static std::string leerArchivo(const std::string &ruta) { // abre un archivo y devuelve su contenrido en un string
    std::ifstream f(ruta);
    if (!f) return "";
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}
std::string escapeJsonString(const std::string &input) {
    std::string output;
    for (char c : input) {
        switch (c) {
            case '\"': output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\b': output += "\\b"; break;
            case '\f': output += "\\f"; break;
            case '\n': output += "\\n"; break;
            case '\r': output += "\\r"; break;
            case '\t': output += "\\t"; break;
            default:
                if ('\x00' <= c && c <= '\x1f') {
                    // control character: represent as \u00XX
                    char buf[7];
                    snprintf(buf, sizeof(buf), "\\u%04x", c);
                    output += buf;
                } else {
                    output += c;
                }
        }
    }
    return output;
}
static std::string generarIdSimple() { // dos nuemros aleatorios concatenados 
    // id simple, suficiente para demo 
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    unsigned a = std::rand();
    unsigned b = std::rand();
    std::ostringstream os;
    os << std::hex << a << b;
    return os.str();
}
static std::string generarIdJugador() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string id;
    id.reserve(12);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);
    for (int i = 0; i < 12; ++i) id += alphanum[dist(gen)];
    return id;
}



// ----- Rutas -----
void definirRutas(httplib::Server &svr) {
    



        // Servir index.html
        svr.Get("/", [](const httplib::Request&, httplib::Response &res) {
            auto html = leerArchivo("views/index.html");
            if (html.empty()) {
                res.status = 404;
                res.set_content("Index no encontrado (views/index.html)", "text/plain");
                return;
            }
            res.set_content(html, "text/html");
        });

        // Servir la vista de partida (frontend)
        svr.Get("/partida", [](const httplib::Request&, httplib::Response &res) {
            auto html = leerArchivo("views/partida.html");
            if (html.empty()) {
                res.status = 404;
                res.set_content("Partida no encontrada (views/partida.html)", "text/plain");
                return;
            }
            res.set_content(html, "text/html");
        });

        // Crear usuario y devolver cookie user_id
        svr.Get("/crear-usuario", [](const httplib::Request&, httplib::Response &res) {
            std::string id_usuario = generarIdSimple();
            // Cookie simple (HttpOnly)
            res.set_header("Set-Cookie", std::string("user_id=") + id_usuario + "; Path=/; HttpOnly");
            res.set_content(std::string("{\"user_id\":\"") + id_usuario + "\"}", "application/json");
        });



        // Crear partida simple y agregar un jugador (usa query ?nombre=TuNombre)

        //  partidaGlobal->juegoActivo.iniciarPartida(); // esto no debe de ser asi 

            

        // Ejemplo: GET /crear-partida?nombre=Jose
        svr.Get("/unirse-partida", [](const httplib::Request &req, httplib::Response &res) {
           

            // 1. Obtener nombre
            std::string nombre;
            try { nombre = req.get_param_value("nombre"); } catch(...) { nombre = ""; }

            if (nombre.empty()) {
                res.status = 400;
                res.set_content("{\"error\":\"falta parametro nombre\"}", "application/json");
                return;
            }

            // 2. Crear partida si no existe
            if (!partidaGlobal)
                partidaGlobal = std::make_unique<ControladorJuego>();
             // Si la partida esta corriendo no puede jugar
            if (partidaGlobal->juegoActivo.partidaActiva) {
            res.status = 400;
            res.set_content("{\"error\":\"partida iniciada no se puede entrar\"}", "application/json");
            return;
        }

            // 3. Verificar si el jugador ya existe
            bool jugadorExiste = false;
            for (const auto& j : partidaGlobal->juegoActivo.getJugadores()) {
                if (j.getNombre() == nombre) {
                    jugadorExiste = true;
                    break;
                }
            }

            if (jugadorExiste) {
                res.status = 400;
                res.set_content("{\"error\":\"usuario con ese nombre ya creado\"}", "application/json");
                return;
            }

            // 4. Crear y añadir nuevo jugador
            Jugador jugador(nombre);

            // 🔹 generar un ID único para el jugador
            std::string idJugador = generarIdJugador();
            jugador.setId(idJugador); // necesitas agregar este campo + setter en Jugador

            partidaGlobal->juegoActivo.addJugador(jugador);
            int i = 0;
            std::string indice = "";
            for(const auto& jugadorI : partidaGlobal->juegoActivo.getJugadores() ){
                if(jugadorI.getNombre() == jugador.getNombre()){
                    indice = std::to_string(i);
                }
                i++;
            }
            nombre = indice + " " + nombre;

            jsonFinal = "";
            // 5. Devolver respuesta
            std::string json =
                "{"
                "\"ok\":true,"
                "\"msg\":\"jugador añadido correctamente\","
                "\"jugador\":\"" + nombre + "\","
                "\"id\":\"" + idJugador + "\""
                "}";
            reiniciandoPartida = false;
            res.status = 200;
            res.set_content(json, "application/json");
        });
        svr.Get("/estado-partida", [](const httplib::Request& req, httplib::Response& res) {
            std::string json = "{\"reiniciando\":";
            json += reiniciandoPartida ? "true" : "false";
            json += "}";
            res.set_content(json, "application/json");
        });
        svr.Post("/reiniciar-partida", [](const httplib::Request &req, httplib::Response &res) {
                
                if (!partidaGlobal) {
                    res.status = 400;
                    res.set_content("{\"ok\":false, \"error\":\"No hay partida activa.\"}", "application/json");
                    return;
                }

                /* Copia segura de los jugadores (no referencia)
                auto jugadores = partidaGlobal->juegoActivo.getJugadores();

                if (jugadores.empty()) {
                    res.status = 400;
                    res.set_content("{\"ok\":false, \"error\":\"No hay jugadores en la partida.\"}", "application/json");
                    return;
                }

                std::string nombreJugador;
                if (req.has_param("nombre")) {
                    nombreJugador = req.get_param_value("nombre");
                } else {
                    res.status = 400;
                    res.set_content("{\"ok\":false, \"error\":\"Falta el parámetro 'nombre'.\"}", "application/json");
                    return;
                }

                const std::string nombreCreador = jugadores[0].getNombre();

                if (nombreJugador != nombreCreador) {
                    res.status = 403;
                    res.set_content("{\"ok\":false, \"error\":\"Solo el creador (" + nombreCreador + ") puede reiniciar la partida.\"}", "application/json");
                    return;
                }*/
                reiniciandoPartida = true;
                try
                {
                    partidaGlobal.reset();
                    partidaGlobal = std::make_unique<ControladorJuego>();

                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            
                
                res.status = 200;
                res.set_content("{\"ok\":true, \"msg\":\"Partida reiniciada correctamente.\"}", "application/json");
                
            });




    // Acción del jugador: ?accion=pedir  o ?accion=plantar
    // Ejemplo: GET /accion?accion=pedir
    svr.Get("/iniciar-partida", [](const httplib::Request &req, httplib::Response &res) {
    // 1 Crear el controlador si no existe
    if (!partidaGlobal){
        partidaGlobal = std::make_unique<ControladorJuego>();}
        
    // 2 Verificar si ya hay una partida activa
    if (partidaGlobal->juegoActivo.partidaActiva) {
        res.status = 400;
        res.set_content(
            "{\"error\":\"La partida ya está iniciada, no se puede reiniciar.\"}",
            "application/json"
        );
        return;
    }

    // 3 Iniciar la partida
    partidaGlobal->juegoActivo.iniciarPartida();

    // 4 Confirmar al cliente
    res.status = 200;
    res.set_content(
        "{\"ok\":true, \"msg\":\"La partida ha sido iniciada correctamente.\"}",
        "application/json"
    );
});

    //Aqui se configuran las acciones 

   svr.Get("/accion", [](const httplib::Request &req, httplib::Response &res) {

        if (!partidaGlobal) {
            res.status = 400;
            res.set_content("{\"error\":\"no hay partida\"}", "application/json");
            return;
        }
         if (!partidaGlobal->juegoActivo.partidaActiva) {
            res.status = 400;
            res.set_content("{\"error\":\"partida no iniciada\"}", "application/json");
            return;
        }
        if (reiniciandoPartida) {
            res.status = 409; // o 503
            res.set_content("{\"reload\":true}", "application/json");
            return;
        }


        std::string accion, idJugador;
        try { accion = req.get_param_value("accion"); } catch(...) { accion = ""; }
        try { idJugador = req.get_param_value("id"); } catch(...) { idJugador = ""; }

        if (accion.empty() || idJugador.empty()) {
            res.status = 400;
            res.set_content("{\"error\":\"faltan parametros (accion o id)\"}", "application/json");
            return;
        }

        // Obtener el jugador actual (por índice)
        int indiceActual = partidaGlobal->getJuagadorActivo();
        const auto& jugadorActual = partidaGlobal->juegoActivo.getJugadores()[indiceActual];

        // Verificar que el ID corresponda al jugador del turno
        if (jugadorActual.getId() != idJugador) {
            res.status = 403;
            res.set_content("{\"error\":\"no es tu turno o ID invalido\"}", "application/json");
            return;
        }

        // Ejecutar acción
        if (accion == "pedir") {

            partidaGlobal->enviarOrden('p');

        } else if (accion == "plantar") {
            
            if( !partidaGlobal->cambiarJugador()){
                try{
                Mazo mazo = partidaGlobal->juegoActivo.getMazo();
                std::string respuesta = partidaGlobal->juegoActivo.jugar(mazo);
                respuesta = respuesta +  partidaGlobal->juegoActivo.evaluarRonda();
                std::string json = "{\"mensaje\":\"" + escapeJsonString(respuesta) + "\"}";
                jsonFinal = json;
                res.set_content(json, "application/json");
                partidaGlobal->juegoActivo.partidaActiva = false;
                
                return;
            
            }
                
                
                catch (...) {
                res.status = 500;
                 
                res.set_content("{\"error\":\"la partida fue reiniciada durante la consulta\"}", "application/json");
                return;
            }
                
            }

        } else {
            res.status = 400;
            res.set_content("{\"error\":\"accion no reconocida\"}", "application/json");
            return;
        }

        // Devolver estado
        std::string manos = partidaGlobal->juegoActivo.mostrarManoParcial();
        auto &jugadores = partidaGlobal->juegoActivo.getJugadores();
        const std::string nombrejugador = jugadores[partidaGlobal->getJuagadorActivo()].getNombre();

        // Construir string de manos (escapando saltos de línea y comillas)
        std::string manosJugadores = "[";
        for (size_t i = 0; i < jugadores.size(); ++i) {
            std::string mano = "player " +std::to_string(i) + " " + jugadores[i].mostrarMano();

            // Escapar comillas dobles y saltos de línea
            size_t pos = 0;
            while ((pos = mano.find("\"", pos)) != std::string::npos) {
                mano.replace(pos, 1, "\\\"");
                pos += 2;
            }
            while ((pos = mano.find("\n", pos)) != std::string::npos) {
                mano.replace(pos, 1, "\\n");
                pos += 2;
            }

            manosJugadores += "\"" + mano + "\"";
            if (i < jugadores.size() - 1) manosJugadores += ",";
        }
        manosJugadores += "]";

        std::string json = "{";
        json += "\"mano_visible_crupier\":\"" + manos + "\",";
        json += "\"manos_jugadores\":" + manosJugadores + ",";
        json += "\"jugador_activo\":\"" + nombrejugador + "\"";
        json += "}";

        res.set_content(json, "application/json");
    });


    // Estado actual (GET /estado)
    svr.Get("/estado", [](const httplib::Request&, httplib::Response &res) {
        if (!partidaGlobal) {
            res.status = 400;
            res.set_content("{\"error\":\"no hay partida activa\"}", "application/json");
            return;
        }
        if (reiniciandoPartida) {
                res.status = 409; // o 503
                res.set_content("{\"reload\":true}", "application/json");
                return;
        }
        if (!jsonFinal.empty()) {
            res.set_content(jsonFinal, "application/json");
            return;
        } 

        
        try{
             std::string manos = partidaGlobal->juegoActivo.mostrarManoParcial();
            auto &jugadores = partidaGlobal->juegoActivo.getJugadores();
            const std::string nombrejugador = jugadores[partidaGlobal->getJuagadorActivo()].getNombre();

            // Construir string de manos (escapando saltos de línea y comillas)
            std::string manosJugadores = "[";
            for (size_t i = 0; i < jugadores.size(); ++i) {
                std::string mano = "player " +std::to_string(i) + " " + jugadores[i].mostrarMano();

                // Escapar comillas dobles y saltos de línea
                size_t pos = 0;
                while ((pos = mano.find("\"", pos)) != std::string::npos) {
                    mano.replace(pos, 1, "\\\"");
                    pos += 2;
                }
                while ((pos = mano.find("\n", pos)) != std::string::npos) {
                    mano.replace(pos, 1, "\\n");
                    pos += 2;
                }

                manosJugadores += "\"" + mano + "\"";
                if (i < jugadores.size() - 1) manosJugadores += ",";
            }
            manosJugadores += "]";

            std::string json = "{";
            json += "\"mano_visible_crupier\":\"" + manos + "\",";
            json += "\"manos_jugadores\":" + manosJugadores + ",";
            json += "\"jugador_activo\":\"" + nombrejugador + "\"";
            json += "}";

            res.set_content(json, "application/json");
        }
        catch (...) {
        res.status = 500;
        res.set_content("{\"error\":\"la partida fue reiniciada durante la consulta\"}", "application/json");
    }
       
        
    });

    // Reiniciar / nueva partida (GET /nueva-partida)
    svr.Get("/nueva-partida", [](const httplib::Request&, httplib::Response &res) {
        if (!partidaGlobal) {
            res.status = 400;
            res.set_content("{\"error\":\"no hay partida\"}", "application/json");
            return;
        }
        partidaGlobal->juegoActivo.nuevaPartida();
        res.set_content("{\"ok\":true,\"msg\":\"partida reiniciada\"}", "application/json");
    });

    // Ruta para detener servidor (solo demo; en producción no deberia de estar)
    svr.Get("/shutdown", [](const httplib::Request&, httplib::Response &res) {
        res.set_content("{\"ok\":true,\"msg\":\"apagando\"}", "application/json");
        // El main puede detectar esta respuesta y detener el servidor si lo necesitas.
    });
}
