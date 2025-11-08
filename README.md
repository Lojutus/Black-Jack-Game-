## PLANTILLA PARA GOOGLE-TESTING CON DOCKER PARA PROYECTOS EN C++

## 🔹 Descripcion basica del proyecto

Rellenar

## Funcionamiento:

ControladorJuego tiene:

un juego

Juego hereda de crupier y tiene:

un vector de jugadores

un mazo



Mazo tiene:

muchas cartas

jugador tiene:

una sola mano

mano tiene : 

un vector de cartas relacionadas con el mazo


¿Como se ejecuta la partida?

Controladorjuego instancia un juego 


La clase juego, añade los jugadores 

iniciar partida de clase juego hace :


le reparte a cada jugador dos carta y al crupier tambien

usa los metodos de la claseCrupier para barajar el mazo 

de acuerdo al orden que tiene los jugadores se le pide a Controlador juego que reciba la orden de cada uno

si alguien no a perdido se llama al algoritmo de crumpier , para que intente ganar al jugador que aun no pierde

se llama a determinar ganador al final de cada ronda y se le dice que gano 



## 🔹 COMO HACER Debugging en VS Code
El archivo `.vscode/launch.json` ya incluye la configuración de depuración:
- Debug (gdbserver :2345) → Permite depuración remota con `gdbserver`.
1. En una terminal del contenedor, compila y lanza `gdbserver`:
```bash
make gdbserver
```
Esto mostrará algo como:
```bash
Listening on port 2345
Waiting for gdb connection...
```
2. En VS Code pulsa **F5**. Se conectará al puerto *2345* y podrás depurar de forma remota.

## 🔹 Google Testing
Se debe modificar el archivo `tests/test_main.cpp` con los test que requeridos.

Dentro del Dev Container:

```bash
make google-test       # Ejecuta los test con la librería gtest de google
```

El binario generado es `test_runner`.

# NOTAS
Es Posible que se pierda acceso a modificar diversos archivos dentro del contanier, si es asi se debe de ejecutar
estando en la carpeta raíz del proyecto
```bash
sudo chown -R $(whoami):$(whoami) .
sudo chmod -R u+rw .
```
