#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_COLS 100

void clear_screen() {
    printf("\033[2J");
    fflush(stdout);
}

void move_cursor(int line, int col) {
    printf("\033[%d;%dH", line, col);
    fflush(stdout);
}

void draw_char(char ch, int bold) {
    if (bold) {
        printf("\033[1m%c\033[0m", ch);
    } else {
        printf("%c", ch);
    }
    fflush(stdout);
}

int main() {
    srand(time(NULL));

    int cols_array[MAX_COLS] = {0};

    int lines, cols;
    char ch;
    while (1) {
        // Get terminal size
        printf("\033[18t");
        scanf("\033[%d;%dR", &lines, &cols);

        clear_screen();

        for (int col = 0; col < cols; ++col) {
            int rnum = rand() % 20;

            if (cols_array[col] >= 0) {
                int line = cols_array[col];

                move_cursor(line, col + 1);
                draw_char((rnum < 3) ? '1' : '0', (rnum < 3));

                cols_array[col]++;

                if (cols_array[col] >= lines) {
                    if (rnum < 2) {
                        cols_array[col] = 0;
                    } else {
                        cols_array[col] = -1;
                    }
                }
            } else {
                int line = -cols_array[col];
                cols_array[col]--;

                move_cursor(line, col + 1);
                draw_char(' ', 0);

                if (cols_array[col] < -lines) {
                    cols_array[col] = 0;
                } else if (rnum < 1) {
                    cols_array[col] = 0;
                }
            }
        }

        fflush(stdout);
        usleep(40000);
    }

    return 0;
}
