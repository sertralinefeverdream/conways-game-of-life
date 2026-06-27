#include "../include/cgol.h"
#include <stdio.h>
#include <stdlib.h>

struct cgol_state cgol_state_create(int width, int height) {
    if (width <= 0 || height <= 0) {
       perror("cgol_state grid must have non-zero, non-negative dimensions");
       exit(EXIT_FAILURE);
    }

    struct cgol_state s;
    s.width = width;
    s.height = height;
    s.grid = malloc(sizeof(int) * width * height);
    return s;
}

void cgol_state_free(struct cgol_state s) {
    free(s.grid);
}

int cgol_state_index(const struct cgol_state s, int col, int row) {
   if (col < 0 || col >= s.width || row < 0 || row >= s.height) {
       return 0;
   }
   
   return s.grid[row * s.width + col];
}

void cgol_state_set(struct cgol_state s, int col, int row, int value) {
    if (col < 0 || col >= s.width || row < 0 || row >= s.height) {
        return;
    }
    
    s.grid[row * s.width + col] = value;
}

/* Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 * Any live cell with two or three live neighbours lives on to the next generation.
 * Any live cell with more than three live neighbours dies, as if by overpopulation.
 * Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
 */

static int count_live_neighbours(const struct cgol_state s, int col, int row) {
   int n = 0;

   for (int i = 0; i < 3; ++i) {    
       for (int j = 0; j < 3; ++j) {
            if (i == 1 && i == j) {
                continue;
            }

           int cell = cgol_state_index(s, col+i-1, row+j-1);    
           n += cell;
       }
   }
   
   return n;
}

struct cgol_state cgol_state_generate_next(struct cgol_state s) {
    struct cgol_state next = cgol_state_create(s.width, s.height);

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



