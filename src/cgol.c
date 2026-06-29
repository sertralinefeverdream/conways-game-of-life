#include "../include/cgol.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
struct cgol_state cgol_state_create(int width, int height, int initialised) {
    if (width <= 0 || height <= 0) {
        return CGOL_STATE_NULL; 
    }

    struct cgol_state s;
    s.width = width;
    s.height = height;
    s.grid = malloc(sizeof(int) * width * height); // Initialised to 0
                                                   
    if (initialised) {
       for (int i = 0; i < s.width * s.height; ++i)  {
           s.grid[i] = 0;
       }
    }
    return s;
}*/

struct cgol_state *cgol_state_create(int width, int  height, int initialised) { 
    if (width <= 0 || height <= 0) {
        return NULL; 
    }
    
    struct cgol_state *s = malloc(sizeof(struct cgol_state) + width * height * sizeof(int));
    s->width = width;
    s->height = height;
    
    if (initialised) {
        for (int i = 0; i < s->width * s->height; ++i) {
            s->grid[i] = 0;
        }
    }
    
    return s;
}

/*
struct cgol_state cgol_state_create_randomised(int width, int height, double p) {
    struct cgol_state s = cgol_state_create(width, height, INIT); 

    if (s.grid == NULL) {
        return s;
    }

    srand(time(NULL));
    for (int i = 0; i < s.width * s.height; ++i) {
        int r = rand();
        
        if (r <= (double)RAND_MAX * p) {
           s.grid[i] = 1;
           continue; 
        }
        
        s.grid[i] = 0;
    }
    
    return s;
}
*/

struct cgol_state *cgol_state_create_randomised(int width, int height, double p) {
    struct cgol_state *s = cgol_state_create(width, height, INIT);

    if (s == NULL) {
       return s; 
    }
    
    srand(time(NULL));
    for (int i = 0; i < s->width * s->height; ++i) {
        int r = rand();
        
        if (r <= (double)RAND_MAX * p) {
            s->grid[i] = 1;
            continue;
        }
        
        s->grid[i] = 0;
    }
    
    return s;
}

/*void cgol_state_free(struct cgol_state s) {
    free(s.grid);
}*/

int cgol_state_index(const struct cgol_state *const s, int col, int row) {
    if (s == NULL || col < 0 || col >= s->width || row < 0 || row >= s->height) {
        return 0;
    }
    
    return s->grid[row * s->width + col];
}

/*
int cgol_state_index(const struct cgol_state s, int col, int row) {
   if (col < 0 || col >= s.width || row < 0 || row >= s.height) {
       return 0;
   }
   
   return s.grid[row * s.width + col];
}
*/

void cgol_state_set(struct cgol_state *const s, int col, int row, int value) { 
    if (s == NULL || col < 0 || col >= s->width || row < 0 || row >= s->height) {
       return; 
    }
    s->grid[row * s->width + col];
}

/*
void cgol_state_set(struct cgol_state s, int col, int row, int value) {
    if (col < 0 || col >= s.width || row < 0 || row >= s.height) {
        return;
    }
    s.grid[row * s.width + col] = value == 0 ? 0 : 1; // Normalise all non-zero values to 1 
}
*/

/* Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 * Any live cell with two or three live neighbours lives on to the next generation.
 * Any live cell with more than three live neighbours dies, as if by overpopulation.
 * Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
 */

static int count_live_neighbours(const struct cgol_state *const s, int col, int row) {
   int n = 0;

   for (int i = 0; i < 3; ++i) {    
       for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
           int cell = cgol_state_index(s, col+i-1, row+j-1);    
           n += cell;
       }
   }
   
   return n;
}

/*
struct cgol_state cgol_state_generate_next(const struct cgol_state s) {
    struct cgol_state next = cgol_state_create(s.width, s.height, NOT_INIT);

    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            int curr = cgol_state_index(s, i, j);
            int n = count_live_neighbours(s, i, j);
            
            if (curr) {
                cgol_state_set(next, i, j, (n == 2 || n == 3)); // If alive and has 2 or 3 live neighbours
            } else {
                cgol_state_set(next, i, j, (n == 3)); // If dead and has exactly 3 live neighbours
            }

        }
    }
    
    return next;
}
*/

struct cgol_state *cgol_state_generate_next(const struct cgol_state *const s) {
   struct cgol_state *next = cgol_state_create(s->width, s->height, NOT_INIT);
   
   for (int i = 0; i < s->width; ++i) { 
       for (int j = 0; j < s->width; ++j) {
           int curr = cgol_state_index(s, i, j);
           int n = count_live_neighbours(s, i, j);

           if (curr) {
               cgol_state_set(next, i, j, (n == 2 || n == 3)); // If alive has 2 or 3 live neighbourrs
           } else {
               cgol_state_set(next, i, j, (n==3)); // If dead and has exactly 3 live neighbours
           }
       }
   }
}



