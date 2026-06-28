#ifndef CGOL_H
#define CGOL_H

#include <stdlib.h>

struct cgol_state {
    int width;  
    int height;
    int *grid;
};

struct cgol_state cgol_state_create(int width, int height);
void cgol_state_free(struct cgol_state s);   
int cgol_state_index(const struct cgol_state s, int col, int row); 
void cgol_state_set(struct cgol_state s, int col, int row, int value);
struct cgol_state cgol_state_generate_next(const struct cgol_state s);

#endif