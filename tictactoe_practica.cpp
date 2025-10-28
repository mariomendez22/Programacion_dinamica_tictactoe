#include <iostream>
#include <cstdlib>  // Para usar rand() y srand()
#include <ctime>    // Para generar una semilla aleatoria con time()
using namespace std;

// Matriz global que representa el tablero del juego
char tablero[3][3];

// Variable para guardar el turno del jugador actual ('X' o 'O')
char jugadorActual;

// ------------------------------------------------------------
// Función: inicializarTablero()
// Descripción: llena el tablero con los números del 1 al 9 para
// representar las posiciones disponibles al inicio del juego.
// ------------------------------------------------------------
void inicializarTablero() {
    char c = '1'; // empezamos en '1' para numerar las casillas
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = c++;
        }
    }
}

// ------------------------------------------------------------
// Función: mostrarTablero()
// Descripción: imprime el tablero en consola con formato visual.
// ------------------------------------------------------------
void mostrarTablero() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << tablero[i][j];
            if (j < 2) cout << " | "; // separador entre columnas
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n"; // separador entre filas
    }
    cout << "\n";
}

// ------------------------------------------------------------
// Función: hayGanador()
// Descripción: revisa todas las posibles combinaciones ganadoras.
// Devuelve true si el jugador actual tiene 3 en línea.
// ------------------------------------------------------------
bool hayGanador() {
    // Revisa filas y columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == jugadorActual && tablero[i][1] == jugadorActual && tablero[i][2] == jugadorActual)
            return true;
        if (tablero[0][i] == jugadorActual && tablero[1][i] == jugadorActual && tablero[2][i] == jugadorActual)
            return true;
    }

    // Revisa diagonales
    if (tablero[0][0] == jugadorActual && tablero[1][1] == jugadorActual && tablero[2][2] == jugadorActual)
        return true;
    if (tablero[0][2] == jugadorActual && tablero[1][1] == jugadorActual && tablero[2][0] == jugadorActual)
        return true;

    return false; // si no hay coincidencias, nadie gana aún
}

// ------------------------------------------------------------
// Función: tableroLleno()
// Descripción: determina si ya no quedan movimientos válidos.
// ------------------------------------------------------------
bool tableroLleno() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O')
                return false;
    return true; // todas las casillas están ocupadas
}

// ------------------------------------------------------------
// Función: hacerJugada()
// Parámetro: movimiento -> número de casilla (1 al 9)
// Descripción: coloca la marca del jugador actual en el tablero
// si la posición está libre. Devuelve true si el movimiento es válido.
// ------------------------------------------------------------
bool hacerJugada(int movimiento) {
    int fila = (movimiento - 1) / 3;   // se calcula fila (0-2)
    int columna = (movimiento - 1) % 3; // se calcula columna (0-2)

    // Validar si la jugada es válida
    if (movimiento < 1 || movimiento > 9 || tablero[fila][columna] == 'X' || tablero[fila][columna] == 'O') {
        cout << "Movimiento invalido. Intenta de nuevo.\n";
        return false;
    }

    // Si la casilla está libre, colocamos la marca
    tablero[fila][columna] = jugadorActual;
    return true;
}

// ------------------------------------------------------------
// Función: jugadaCPU()
// Descripción: genera una jugada aleatoria para la computadora.
// Nota: es una lógica básica sin "inteligencia", solo aleatoria.
// ------------------------------------------------------------
void jugadaCPU() {
    int movimiento;
    do {
        movimiento = rand() % 9 + 1; // genera un número entre 1 y 9
    } while (!hacerJugada(movimiento)); // repite hasta que encuentre una jugada válida
    cout << "La computadora elige la casilla " << movimiento << "\n";
}

// ------------------------------------------------------------
// Función: cambiarJugador()
// Descripción: alterna entre 'X' y 'O' después de cada turno.
// ------------------------------------------------------------
void cambiarJugador() {
    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
}

// ------------------------------------------------------------
// Función: jugar()
// Parámetro: modo -> 1 (jugador vs jugador) o 2 (jugador vs CPU)
// Descripción: controla el flujo del juego completo.
// ------------------------------------------------------------
void jugar(int modo) {
    inicializarTablero(); // limpia el tablero
    jugadorActual = 'X';  // siempre empieza el jugador X
    bool fin = false;     // bandera para saber si el juego termina

    while (!fin) {
        mostrarTablero();

        // Si el modo es contra la computadora y es turno de 'O', el CPU juega
        if (modo == 2 && jugadorActual == 'O') {
            jugadaCPU();
        } else {
            int movimiento;
            cout << "Turno del jugador " << jugadorActual << ". Ingresa el numero de casilla (1-9): ";
            cin >> movimiento;

            // Si la jugada no es válida, repetimos el turno
            if (!hacerJugada(movimiento))
                continue;
        }

        // Después de cada jugada, se revisa si hay ganador o empate
        if (hayGanador()) {
            mostrarTablero();
            cout << "¡Jugador " << jugadorActual << " gana!\n";
            fin = true;
        } else if (tableroLleno()) {
            mostrarTablero();
            cout << "¡Empate!\n";
            fin = true;
        } else {
            cambiarJugador(); // si no hay ganador, cambiamos de turno
        }
    }
}

// ------------------------------------------------------------
// Función principal
// Muestra el menú del juego y permite jugar múltiples partidas.
// ------------------------------------------------------------
int main() {
    srand(time(0)); // se inicializa la semilla para movimientos aleatorios

    int opcion;

    do {
        cout << "\n===== TIC TAC TOE =====\n";
        cout << "1. Jugar 1 vs 1\n";
        cout << "2. Jugar contra la computadora\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        // Switch para manejar el menú principal
        switch (opcion) {
            case 1:
                jugar(1); // modo jugador vs jugador
                break;
            case 2:
                jugar(2); // modo jugador vs CPU
                break;
            case 3:
                cout << "Saliendo del juego...\n";
                break;
            default:
                cout << "Opcion invalida, intenta de nuevo.\n";
        }
    } while (opcion != 3); // el juego continúa hasta que el usuario elija salir

    return 0;
}