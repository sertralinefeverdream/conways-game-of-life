#include <stdio.h>
#include "../include/cgol.h"
#include "../include/render.h"
#include <time.h>

int main(int argc, char **argv) {
    render_init();
    
    struct renderer r = {
        .cell_char = 'O',
    };
    
    struct cgol_state s = cgol_state_create(80, 80);
    cgol_state_set(s, 5, 5, 1);
    cgol_state_set(s, 6, 6, 1);
    cgol_state_set(s, 6, 7, 1);
    cgol_state_set(s, 5, 7, 1);
    cgol_state_set(s, 4, 7, 1);
    
    for (;;) {
       render_cgol(r, s); 
       struct cgol_state next_s = cgol_state_generate_next(s);
       cgol_state_free(s);
       s = next_s;
    }
}