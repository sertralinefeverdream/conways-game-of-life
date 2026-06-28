#define _POSIX_C_SOURCE 199309L // Bizarre feature macro definition found on stack overflow needed for CLOCK_MONOTONIC

#include "../include/render.h"
#include "../include/cgol.h"
#include <stdio.h>
#include <time.h>

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CURSOR_TO_HOME "\033[H"
#define CURSOR_NEXT_LINE "\033[1E"
#define ERASE_SCREEN "\033[2J"
#define ALT_BUFFER_ENTER "\033[?1049h"
#define ALT_BUFFER_EXIT "\033[?1049l"

void render_cgol(const struct renderer r, const struct cgol_state s) {
    fputs(CURSOR_TO_HOME, stdout);
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            char c = cgol_state_index(s, j, i) ? r.cell_char : ' ';
            fputc(c, stdout);
        }
        fputs(CURSOR_NEXT_LINE, stdout);
        fflush(stdout);
    }
}

static void render_atexit(void) { 
    fputs(ALT_BUFFER_EXIT, stdout);
    fputs(SHOW_CURSOR, stdout); 
    printf("Exited from Conway's Game Of Life!\n");
    fflush(stdout);
}

void render_init(void) {
    atexit(render_atexit);
    fputs(ALT_BUFFER_ENTER, stdout);
    fputs(HIDE_CURSOR, stdout);// Hide cursor
    fputs(ERASE_SCREEN, stdout);
    fputs(CURSOR_TO_HOME, stdout);
    fflush(stdout);
}

struct renderer renderer_create(char cell_char, unsigned framerate) {
   return (struct renderer) {
       .cell_char = cell_char,
       .framerate = framerate,
       .last_update = {0},
   };
}

void wait_and_render(struct renderer *r, const struct cgol_state s) {
    for (;;) {
        struct timespec now = {0};
        clock_gettime(CLOCK_MONOTONIC, &now);

        double now_seconds = now.tv_sec + now.tv_nsec / 1e9;
        double last_update_seconds = r->last_update.tv_sec + r->last_update.tv_nsec / 1e9;
        if (now_seconds - last_update_seconds >= 1.0/(double)r->framerate) {
            r->last_update = now;
            break;
        }
    }
    
    render_cgol(*r, s);
}
