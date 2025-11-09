#include "web.h"
#include "Controllers/ControladorJuego.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <ctime>
#include <cstdlib>

// ----- Estado global (una sola partida en memoria) -----
static std::unique_ptr<ControladorJuego> partidaGlobal = nullptr;

// ----- Helpers -----
static std::string leerArchivo(const std::string &ruta) { // abre un archivo y devuelve su contenrido en un string
    std::ifstream f(ruta);
    if (!f) return "";
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
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

static std::string getCookieValue(const httplib::Request &req, const std::string &name) {
    auto it = req.headers.find("Cookie");
    if (it == req.headers.end()) return "";
    const std::string &cookie = it->second;
    std::string key = name + "=";
    size_t pos = cookie.find(key);
    if (pos == std::string::npos) return "";
    pos += key.size();
    size_t end = cookie.find(';', pos);
    if (end == std::string::npos) end = cookie.size();
    return cookie.substr(pos, end - pos);
}

static std::string vectorIntsToJsonArray(const std::vector<int>& v) {
    std::string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s += std::to_string(v[i]);
        if (i + 1 < v.size()) s += ",";
    }
    s += "]";
    return s;
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

            // 5. Devolver respuesta
            std::string json =
                "{"
                "\"ok\":true,"
                "\"msg\":\"jugador añadido correctamente\","
                "\"jugador\":\"" + nombre + "\","
                "\"id\":\"" + idJugador + "\""
                "}";
            
            res.status = 200;
            res.set_content(json, "application/json");
        });


    // Acción del jugador: ?accion=pedir  o ?accion=plantar
    // Ejemplo: GET /accion?accion=pedir

    //Aqui se configuran las acciones 

   svr.Get("/accion", [](const httplib::Request &req, httplib::Response &res) {
        if (!partidaGlobal) {
            res.status = 400;
            res.set_content("{\"error\":\"no hay partida\"}", "application/json");
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
            partidaGlobal->cambiarJugador();
        } else {
            res.status = 400;
            res.set_content("{\"error\":\"accion no reconocida\"}", "application/json");
            return;
        }

        // Devolver estado
        std::string manos = partidaGlobal->juegoActivo.mostrarManoParcial();
        auto puntajes = partidaGlobal->juegoActivo.puntajesJugadores();

        std::string json = "{";
        json += "\"manos\":\"" + manos + "\",";
        json += "\"puntajes\":" + vectorIntsToJsonArray(puntajes);
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
        std::string manos = partidaGlobal->juegoActivo.mostrarManoParcial();
        auto puntajes = partidaGlobal->juegoActivo.puntajesJugadores();
        std::string json = "{";
        json += "\"manos\":\"" + manos + "\",";
        json += "\"puntajes\":" + vectorIntsToJsonArray(puntajes);
        json += "}";
        res.set_content(json, "application/json");
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
