#include <stdio.h>
#include "../include/cgol.h"
#include "../include/render.h"
#include <time.h>

int main(int argc, char **argv) {
    render_init();
    
    struct renderer r = renderer_create('O', 5);
    
    struct cgol_state s = cgol_state_create(80, 80);
    cgol_state_set(s, 5, 5, 1);
    cgol_state_set(s, 6, 6, 1);
    cgol_state_set(s, 6, 7, 1);
    cgol_state_set(s, 5, 7, 1);
    cgol_state_set(s, 4, 7, 1);
    
    for (;;) {
       wait_and_render(&r, s);
       struct cgol_state next_s = cgol_state_generate_next(s);
       cgol_state_free(s);
       s = next_s;
    }
}