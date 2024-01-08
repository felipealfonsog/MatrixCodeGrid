#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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

    while ((keypress = getch()) != 'q') {
        int lines, cols;
        getmaxyx(stdscr, lines, cols);

        clear();  // Limpia la pantalla en cada iteración

        // Simula la lluvia de arriba hacia abajo y de izquierda a derecha de manera desalineada
        for (int col = 0; col < cols; ++col) {
            int fall_speed = (rand() % 3) + 1;  // Velocidad de caída aleatoria
            int start_line = -rand() % 5;  // Comienza desde arriba

            for (int line = 0; line < lines; ++line) {
                int adjusted_line = (start_line + line) % lines;
                draw_char(adjusted_line, col, (rand() % 2) ? '1' : '0', 0);
            }

            refresh();
            usleep(50000 / fall_speed);  // Ajusta el tiempo de espera para controlar la velocidad de la "lluvia"
        }
    }

    endwin();
    return 0;
}
