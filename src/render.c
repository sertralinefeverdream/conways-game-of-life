#include "../include/render.h"
#include "../include/cgol.h"
#include <stdio.h>

void render_cgol(const struct renderer r, const struct cgol_state s) {
    //fputs("\033[2J", stdout);
    fputs("\033[H", stdout); // Return cursor to home position
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            char c = cgol_state_index(s, j, i) ? r.cell_char : ' ';
            fputc(c, stdout);
        }
        fputs("\033[1E", stdout);
    }
    fflush(stdout);
}

void render_init(void) {
    fputs("\033[?1049h", stdout); // Alternate buffer mode & hide cursor
    fputs("\033[?25l", stdout); // Hide cursor
    fputs("\033[2J", stdout); // Erase screen
    fputs("\033[H", stdout);
}