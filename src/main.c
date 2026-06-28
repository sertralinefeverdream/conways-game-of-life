#include "../include/cgol.h"
#include "../include/render.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

static volatile sig_atomic_t running = 1;

static void signal_handler(int sig) {
    running = 0;
}

int main(int argc, char **argv) {
    render_init();
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    
    struct renderer r = renderer_create('O', 12); // Set to 12 generations per second. Feel free to modify.
    struct cgol_state s = cgol_state_create(80, 80);
    
    /* Instructions for user modification of hard-coded grid:
     *  cgol_state_set(s, 21, 30, 1) will add a live cell to the state "s"
     *  at row 21, column 30. 1 as the last parameter will make the cell at
     *  this position live while 0 will make the cell dead. 
     *  Using any value other than 1 will 
     */

    cgol_state_set(s, 5, 5, 1); // Basic glider cell pattern
    cgol_state_set(s, 6, 6, 1);
    cgol_state_set(s, 6, 7, 1);
    cgol_state_set(s, 5, 7, 1);
    cgol_state_set(s, 4, 7, 1); 
    
    while (running) {
       wait_and_render(&r, s);
       struct cgol_state next_s = cgol_state_generate_next(s);
       cgol_state_free(s);
       s = next_s;
    }
    
    exit(EXIT_SUCCESS);
}