#include <stdio.h>
#include "../include/cgol.h"
#include "../include/render.h"
#include <time.h>
#include <signal.h>

static volatile sig_atomic_t running = 1;

static void signal_handler(int sig) {
    running = 0;
}

int main(int argc, char **argv) {
    render_init();
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    
    struct renderer r = renderer_create('O', 12);
    struct cgol_state s = cgol_state_create(80, 80);

    cgol_state_set(s, 5, 5, 1);
    cgol_state_set(s, 6, 6, 1);
    cgol_state_set(s, 6, 7, 1);
    cgol_state_set(s, 5, 7, 1);
    cgol_state_set(s, 4, 7, 1); 
    
    cgol_state_set(s, 10, 5, 1);
    cgol_state_set(s, 11, 6, 1);
    cgol_state_set(s, 11, 7, 1);
    cgol_state_set(s, 10, 7, 1);
    cgol_state_set(s, 9, 7, 1);
    
    cgol_state_set(s, 11, 10, 1);
    cgol_state_set(s, 11, 9, 1);
    cgol_state_set(s, 12, 9, 1);
    cgol_state_set(s, 11, 10, 1);
    
    cgol_state_set(s, 1, 5, 1);
    cgol_state_set(s, 2, 6, 1);
    cgol_state_set(s, 3, 7, 1);
    cgol_state_set(s, 4, 7, 1);
    cgol_state_set(s, 5, 7, 1); 
    
    
    while (running) {
       wait_and_render(&r, s);
       struct cgol_state next_s = cgol_state_generate_next(s);
       cgol_state_free(s);
       s = next_s;
    }
    
    exit(EXIT_SUCCESS);
}