#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_COLS 100

void draw_char(int line, int col, char ch, int bold) {
    if (bold) {
        attron(A_BOLD);
    }

    attron(COLOR_PAIR(1));  // Activa el color verde
    mvprintw(line, col, "%c", ch);
    attroff(COLOR_PAIR(1));

    if (bold) {
        attroff(A_BOLD);
    }
}

int main() {
    initscr();
    start_color();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    timeout(0);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Define el par de colores (verde sobre negro)

    srand(time(NULL));

    int keypress;
    int fall_speed;
    int cycle_count = 0;
    int cycle_duration = 7;  // Duración de un ciclo en segundos
    int initial_cycle_lines = LINES / 2;  // Número de líneas parejas al principio de cada ciclo

    int cols_array[MAX_COLS][MAX_COLS] = {0};

    while ((keypress = getch()) != 'q') {
        int lines, cols;
        getmaxyx(stdscr, lines, cols);

        // Simula la caída de "1" y "0" por columnas como una lluvia
        for (int col = 0; col < cols; ++col) {
            fall_speed = (rand() % 5) + 1;  // Velocidad de caída aleatoria desde el principio

            int start_line = -rand() % (4 * lines);  // Comienza desde más arriba

            for (int line = 0; line < lines; ++line) {
                int adjusted_line = (start_line + line) % lines;

                if (col == 0) {
                    // La primera columna ya se inicializó previamente
                    if (line < initial_cycle_lines) {
                        cols_array[adjusted_line][col] = (rand() % 2 == 0) ? '1' : '0';
                    } else {
                        cols_array[adjusted_line][col] = ' ';
                    }
                } else if (rand() % 2 == 0) {
                    cols_array[adjusted_line][col] = (rand() % 3 == 0) ? '1' : '0';  // Probabilidad más alta de 1 y 0 unidos
                } else if (rand() % 3 == 0) {
                    cols_array[adjusted_line][col] = ' ';  // Espacio más largo
                }

                // Dibuja los caracteres
                draw_char(adjusted_line, col, cols_array[adjusted_line][col], rand() % 2);
            }
        }

        refresh();

        usleep(150000 / fall_speed);  // Ajusta el tiempo de espera para controlar la velocidad de la "lluvia"

        // Verifica si ha pasado el tiempo de un ciclo
        if (cycle_count * 150000 / fall_speed >= cycle_duration * 1000000) {
            cycle_count = 0;  // Reinicia el ciclo
            initial_cycle_lines = (rand() % (LINES / 2)) + 1;  // Número de líneas parejas al principio de cada ciclo
        } else {
            cycle_count++;
        }
    }

    endwin();
    return 0;
}
