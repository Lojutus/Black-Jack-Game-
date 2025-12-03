#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../Models/Juego.h"
#include "../Models/Jugador.h"

// Test para el constructor de Juego
TEST(JuegoTest, Constructor) {
    Juego juego;
    EXPECT_FALSE(juego.partidaActiva);
    EXPECT_TRUE(juego.getJugadores().empty());
}

// Test para agregar jugadores
TEST(JuegoTest, AddJugador) {
    Juego juego;
    Jugador jugador("Jugador 1");
    juego.addJugador(jugador);
    EXPECT_EQ(juego.getJugadores().size(), 1);
    EXPECT_EQ(juego.getJugadores()[0].getNombre(), "Jugador 1");
}

// Test para iniciar partida
TEST(JuegoTest, IniciarPartida) {
    Juego juego;
    Jugador jugador("Jugador 1");
    juego.addJugador(jugador);
    juego.iniciarPartida();
    EXPECT_TRUE(juego.partidaActiva);
    
}

// Test para obtener puntajes de jugadores
TEST(JuegoTest, PuntajesJugadores) {
    Juego juego;
    Jugador jugador("Jugador 1");

    // Configurar el valor de la mano del jugador con cartas válidas
    jugador.recibirCarta(Carta("A", "♠", 11)); // As vale 11
    jugador.recibirCarta(Carta("9", "♦", 9)); // 9 vale 9

    juego.addJugador(jugador);
    auto puntajes = juego.puntajesJugadores();

    ASSERT_EQ(puntajes.size(), 1);
    EXPECT_EQ(puntajes[0], 20); // Ahora el puntaje será 20 correctamente
}

// Test para evaluar ronda
TEST(JuegoTest, EvaluarRonda) {
    Juego juego;
    Jugador jugador("Jugador 1");
    
    juego.addJugador(jugador);
    std::string resultado = juego.evaluarRonda();
    EXPECT_FALSE(resultado.empty());
}

// Test para nueva partida
TEST(JuegoTest, NuevaPartida) {
    Juego juego;
    Jugador jugador("Jugador 1");
    juego.addJugador(jugador);
    juego.nuevaPartida();
    EXPECT_FALSE(juego.partidaActiva);
    EXPECT_TRUE(juego.getJugadores().empty());
}

// Test para terminar juego
TEST(JuegoTest, TerminarJuego) {
    Juego juego;
    Jugador jugador("Jugador 1");
    juego.addJugador(jugador);
    juego.terminarJuego();
    EXPECT_FALSE(juego.partidaActiva);
    EXPECT_TRUE(juego.getJugadores().empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
