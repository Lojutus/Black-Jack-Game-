## BLACKJACK C++

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
## Clase: Carta
**Archivo:** `Carta.cpp`

Esta clase representa una carta individual de la baraja.

### `Carta(const std::string& nombre, const std::string& palo, int valor)`
**Funcionalidad:** Es el constructor de la clase. Utiliza una lista de inicialización de miembros (`: nombre(nombre), palo(palo), valor(valor)`) para asignar directamente los argumentos (nombre, palo y valor) a las variables miembro privadas de la instancia.

### `int getValor() const`
**Funcionalidad:** Devuelve el valor numérico (entero) de la carta (ej. 10 para la 'K', 11 para el 'A').

### `std::string getNombre() const`
**Funcionalidad:** Devuelve el nombre (`string`) de la carta (ej. "A", "5", "J").

### `std::string getPalo() const`
**Funcionalidad:** Devuelve el palo (`string`) de la carta (ej. "Corazones", "Picas").

### `std::string mostrar() const`
**Funcionalidad:** Genera y devuelve una representación textual de la carta. Usa `std::ostringstream` para construir un `string` con el formato "Nombre de Palo" (ej. "As de Tréboles").

---

## Clase: Mazo
**Archivo:** `Mazo.cpp`

Esta clase gestiona la colección de cartas (la baraja), incluyendo barajar y repartir.

### `Mazo()`
**Funcionalidad:** Es el constructor. Llama inmediatamente al método `reiniciar()` para crear y poblar el mazo con las 52 cartas estándar y barajarlo.

### `void barajar()`
**Funcionalidad:** Reordena aleatoriamente las cartas dentro del vector `cartas`. Utiliza `std::shuffle` junto con un motor de números aleatorios (`std::default_random_engine`) sembrado con la hora actual (`std::time(nullptr)`) para asegurar un orden diferente en cada ejecución.

### `Carta repartirCarta()`
**Funcionalidad:** Saca y devuelve la carta superior del mazo (la última carta del vector).
* Primero comprueba si el mazo está vacío (`cartas.empty()`).
* Si está vacío, llama a `reiniciar()` y `barajar()` para crear un nuevo mazo.
* Obtiene la carta del final del vector (`cartas.back()`), la elimina del vector (`cartas.pop_back()`) y la devuelve.

### `int cartasRestantes() const`
**Funcionalidad:** Devuelve el número de cartas que quedan actualmente en el vector `cartas`.

### `void reiniciar()`
**Funcionalidad:** Restaura el mazo a su estado original de 52 cartas.
* Limpia el vector `cartas` (`cartas.clear()`).
* Define los palos y nombres estándar.
* Itera (con bucles anidados) sobre cada palo y cada nombre.
* Asigna el valor de Blackjack correspondiente a cada carta (11 para 'A', 10 para 'J', 'Q', 'K', y el valor numérico para las demás).
* Añade la nueva `Carta` al vector `cartas`.
* Finalmente, llama a `barajar()` para que el mazo recién creado esté desordenado.

---

## Clase: Mano
**Archivo:** `Mano.cpp`

Esta clase representa la colección de cartas que posee un jugador o el crupier.

### `void agregarCarta(const Carta& carta)`
**Funcionalidad:** Añade un objeto `Carta` al final del vector `cartas` de la mano.

### `int calcularValor() const`
**Funcionalidad:** Calcula y devuelve el valor total de la mano según las reglas del Blackjack.
* Suma el valor de todas las cartas y cuenta cuántos Ases hay.
* Si el total supera 21 y hay Ases en la mano, un bucle `while` se encarga de restar 10 al total por cada As (cambiando su valor de 11 a 1) hasta que el total sea 21 o menos, o se acaben los Ases.

### `const std::vector<Carta>& getCartas() const`
**Funcionalidad:** Devuelve una referencia constante al vector privado `cartas`, permitiendo a otras clases ver las cartas de la mano sin poder modificarlas.

### `std::string mostrar() const`
**Funcionalidad:** Genera y devuelve un `string` que representa todas las cartas en la mano.
* Utiliza `std::ostringstream` para concatenar el resultado de `carta.mostrar()` de cada carta, separadas por " | ".

### `std::size_t getCantidad() const`
**Funcionalidad:** Devuelve el número de cartas que hay actualmente en la mano (el tamaño del vector `cartas`).

### `void vaciar()`
**Funcionalidad:** Elimina todas las cartas de la mano llamando a `cartas.clear()`.

---

## Clase: ControladorJuego
**Archivo:** `ControladorJuego.cpp`

Esta clase parece actuar como el intermediario entre la lógica del juego (modelo) y las acciones del usuario.

### `ControladorJuego()`
**Funcionalidad:** Constructor vacío, no realiza ninguna inicialización explícita.

### `bool enviarOrden(char orden)`
**Funcionalidad:** Procesa una orden del jugador ('p' para pedir, 'd' para dejar).
* Obtiene un puntero al jugador activo (`jugadorActivo`) desde el objeto `juegoActivo`.
* Si la orden es 'p' (pedir), llama al método `pedirCarta()` de ese jugador, pasándole el mazo del juego.
* Devuelve `1` (`true`) si la operación se procesa (ya sea 'p' o 'd').
* Está envuelto en un `try...catch` que devuelve `0` (`false`) si ocurre alguna excepción.

### `int getJuagadorActivo()`
**Funcionalidad:** Devuelve el índice (entero) del jugador que tiene el turno (`jugadorActivo`). (Nota: hay un error tipográfico en el nombre del método, dice "Juagador" en lugar de "Jugador").

### `bool cambiarJugador()`
**Funcionalidad:** Intenta pasar el turno al siguiente jugador de la lista.
* Intenta obtener al jugador en la posición `jugadorActivo + 1` de `juegoActivo`.
* Si tiene éxito: Imprime el nombre del nuevo jugador, actualiza el índice `jugadorActivo` y retorna `1` (`true`). (Nota: `jugadorActivo =+ 1;` es un error tipográfico común; probablemente la intención era `jugadorActivo += 1;` o `jugadorActivo++;`. Tal como está, asigna el valor `1` a `jugadorActivo`).
* Si falla (lanza `std::out_of_range`): Significa que era el último jugador. Captura la excepción, reinicia `jugadorActivo` a `0`, imprime "FIN DE LA RONDA" y retorna `0` (`false`) para indicar que la ronda terminó.

---

## Clase: MostrarInformacion
**Archivo:** `MostrarInformacion.cpp`

Esta clase se encarga de interactuar con la consola, mostrando información y pidiendo datos al usuario.

### `MostrarInformacion()`
**Funcionalidad:** Constructor vacío, no realiza ninguna inicialización.

### `void mostrarManoJugador(Mano& manoMostrar)`
**Funcionalidad:** Recibe una referencia a un objeto `Mano`, llama al método `manoMostrar.mostrar()` y envía el `string` resultante a `std::cout` para imprimirlo en la consola.

### `char pedirOrden()`
**Funcionalidad:** Pide al usuario que elija entre pedir ('p') o dejar ('d').
* Muestra el mensaje de solicitud en la consola.
* Lee un `char` desde `std::cin`.
* Comprueba si la elección es 'p' o 'd'.
* Si es válida: Devuelve el carácter.
* Si no es válida: Muestra un mensaje de error y se llama a sí misma (recursividad) para volver a pedir la orden hasta que el usuario ingrese una opción válida.

---

## Clase: Jugador
**Archivo:** `Jugador.cpp`

Esta clase representa a un participante del juego, sea el crupier o un jugador regular.

### `Jugador(const std::string& nombre)`
**Funcionalidad:** Es el constructor. Recibe un nombre (`string`) y lo asigna a la variable miembro `nombre`.

### `void apostar(double cantidad)`
**Funcionalidad:** Asigna el valor `cantidad` a la variable miembro `apuesta`.

### `void recibirCarta(const Carta& carta)`
**Funcionalidad:** Añade una carta a la mano del jugador llamando al método `agregarCarta()` de su objeto `mano`.

### `void pedirCarta(Mazo& mazo)`
**Funcionalidad:** Permite al jugador pedir una carta. Primero comprueba si el valor actual de su mano es menor a 21. Si lo es, reparte una carta del mazo y la añade a su mano.

### `bool tieneBlackjack() const`
**Funcionalidad:** Devuelve `true` si el jugador tiene exactamente 2 cartas y su valor total es 21.

### `std::string mostrarMano() const`
**Funcionalidad:** Devuelve la representación textual de la mano del jugador, llamando al método `mostrar()` de su objeto `mano`.

### `int getValorMano() const`
**Funcionalidad:** Devuelve el valor numérico total de la mano del jugador, llamando a `calcularValor()` de su objeto `mano`.

### `bool tomaDecision() const`
**Funcionalidad:** Simula la decisión de un jugador (probablemente para un bot o una IA simple). Devuelve `true` (pedir carta) si el valor de su mano es menor a 17.

### `void nuevaMano()`
**Funcionalidad:** Reinicia el estado del jugador para una nueva ronda. Llama a `mano.vaciar()` para limpiar las cartas y reinicia la `apuesta` a `0.0`.

### `std::string getNombre() const`
**Funcionalidad:** Devuelve el nombre (`string`) del jugador.

### `double getApuesta() const`
**Funcionalidad:** Devuelve el monto de la apuesta (`double`) actual.

### `void setApuesta(double cantidad)`
**Funcionalidad:** Establece el monto de la apuesta actual. Es idéntico a `apostar()`.

---

## Clase: Crupier
**Archivo:** `Crupier.cpp`

Esta clase representa al crupier. Hereda de `Jugador` y añade lógicas específicas del repartidor.

### `Crupier()`
**Funcionalidad:** Es el constructor. Llama al constructor de la clase base (`Jugador`) y le pasa "Crupier" como nombre fijo.

### `void barajarMazo(Mazo& mazo)`
**Funcionalidad:** Llama al método `mazo.barajar()` para desordenar el mazo.

### `void repartirTusCartas(Mazo& mazo)`
**Funcionalidad:** Reparte las dos cartas iniciales para el propio crupier, llamando dos veces a `this->recibirCarta()`.

### `void repartirInicial(Mazo& mazo, Jugador& jugador)`
**Funcionalidad:** Reparte las dos cartas iniciales a un jugador específico. Llama dos veces a `jugador.recibirCarta()`.

### `std::string mostrarManoParcial() const`
**Funcionalidad:** Muestra solo la primera carta del crupier (la carta visible). Obtiene el `string` de la mano completa y extrae la subcadena de la primera carta (hasta encontrar el primer "|").

### `bool tieneAsBlando(const Mano& mano)`
**Funcionalidad:** Determina si la mano contiene un "As blando" (un As que vale 11 sin pasarse de 21). Calcula el valor total y cuenta los Ases. Luego, ajusta el valor restando 10 por cada As si el total supera 21. Devuelve `true` si, después del ajuste, todavía queda al menos un As (contado como 11) y el valor es 21 o menos.

### `void determinarGanador(Jugador& jugador)`
**Funcionalidad:** Compara la mano de un jugador con la del crupier y determina el resultado. Imprime en consola el puntaje de ambos y el resultado (quién gana, pierde o si hay empate) basándose en si el jugador se pasó de 21, si el crupier se pasó, o quién tiene el valor más alto.

### `void jugar(Mazo& mazo)`
**Funcionalidad:** Ejecuta el turno automático del crupier.
* Entra en un bucle `while` donde calcula su valor y si tiene un As blando.
* Estrategia:
    * Se planta (sale del bucle) si su valor es 21 o más.
    * Pide carta si el valor es menor a 17.
    * Si tiene 17 blando, tiene un 60% de probabilidad de pedir (40% de plantarse).
    * Si tiene 18-20 blando, tiene un 20% de probabilidad de pedir (arriesgarse).
* Si decide pedir, llama a `this->recibirCarta()`.
* Al final del bucle (cuando se planta o se pasa), imprime su valor final.

---

## Clase: Juego
**Archivo:** `Juego.cpp`

Esta clase (que hereda de `Crupier`) gestiona el estado general y el flujo de la partida.

### `Juego()`
**Funcionalidad:** Constructor. Inicializa la variable `partidaActiva` en `false`.

### `Mazo& Juego::getMazo()`
**Funcionalidad:** Devuelve una referencia al objeto `mazo` del juego.

### `Jugador& Juego::getJugador(int indice)`
**Funcionalidad:** Devuelve una referencia a un jugador específico del vector `jugadores` usando su `indice`.
* Realiza comprobaciones para evitar errores: lanza una excepción `std::out_of_range` si no hay jugadores o si el índice está fuera de los límites del vector.

### `void Juego::addJugador(const Jugador& jugador)`
**Funcionalidad:** Añade un objeto `Jugador` al final del vector `jugadores`.

### `void Juego::iniciarPartida()`
**Funcionalidad:** Prepara e inicia una nueva ronda.
* Comprueba si hay jugadores; si no, imprime un mensaje y termina.
* Establece `partidaActiva` en `true`.
* Llama a `mazo.reiniciar()` y `barajarMazo()` (heredado de `Crupier`).
* Reparte las dos cartas del crupier (`repartirTusCartas()`).
* Itera sobre el vector `jugadores` y reparte dos cartas a cada uno (`repartirInicial()`).

### `std::vector<int> Juego::puntajesJugadores()`
**Funcionalidad:** Devuelve un vector de enteros (`std::vector<int>`) que contiene el valor de la mano de cada jugador en el orden en que están registrados.

### `void Juego::evaluarRonda()`
**Funcionalidad:** Itera sobre todos los jugadores y llama al método `determinarGanador()` (heredado de `Crupier`) para cada uno, comparando su mano con la del crupier.

### `void Juego::pagoVictoria(Jugador& jugador)`
**Funcionalidad:** Simula el pago a un jugador. Si el valor de la mano del jugador es 21 o menos, imprime un mensaje indicando que gana el doble de su apuesta.

### `void Juego::nuevaPartida()`
**Funcionalidad:** Limpia el estado para la siguiente ronda (no para terminar el juego).
* Itera sobre todos los jugadores y llama a `jugador.nuevaMano()` para limpiar sus manos.
* Llama a `nuevaMano()` (método de `Jugador`, heredado por `Juego` vía `Crupier`) para limpiar la mano del crupier.
* Establece `partidaActiva` en `false`.

### `void Juego::terminarJuego()`
**Funcionalidad:** Finaliza el juego por completo.
* Limpia el vector de jugadores (`jugadores.clear()`).
* Establece `partidaActiva` en `false` e imprime un mensaje de "Juego terminado".

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
