#define _POSIX_C_SOURCE 199309L // Bizarre feature macro definition found on stack overflow needed for CLOCK_MONOTONIC

#include "../include/render.h"
#include "../include/cgol.h"
#include <stdio.h>
#include <time.h>

#define HIDE_CURSOR fputs("\033[2J", stdout) 
#define CURSOR_TO_HOME fputs("\033[H", stdout) 
#define CURSOR_NEXT_LINE fputs("\033[1E", stdout)
#define FLUSH fflush(stdout)
#define ERASE_SCREEN fputs("\033[2J", stdout)
#define ALT_BUFFER_ENTER fputs("\033[?1049h", stdout)
#define ALT_BUFFER_EXIT fputs("\033[?1049l", stdout)

void render_cgol(const struct renderer r, const struct cgol_state s) {
    CURSOR_TO_HOME;
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            char c = cgol_state_index(s, j, i) ? r.cell_char : ' ';
            fputc(c, stdout);
        }
        CURSOR_NEXT_LINE;
    }
    FLUSH;
}

void render_init(void) {
    ALT_BUFFER_ENTER;
    HIDE_CURSOR;// Hide cursor
    ERASE_SCREEN;
    CURSOR_TO_HOME;
    FLUSH;
}

struct renderer renderer_create(char cell_char, unsigned framerate) {
   return (struct renderer) {
       .cell_char = cell_char,
       .framerate = framerate,
       .last_update = {0},
   };
}

void wait_and_render(struct renderer *r, const struct cgol_state s) {
    /*for (;;) {
       clock_t now = clock() / CLOCKS_PER_SEC * 1000; // Time elapsed in miliseconds
       if (now - r->last_update >= 1000.0/r->framerate) {
           r->last_update = now; 
           break;
       } 
    } */
   
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
