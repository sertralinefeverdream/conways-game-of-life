#ifndef CGOL_H
#define CGOL_H

#define INIT 1 
#define NOT_INIT 0
#define CGOL_STATE_NULL ((struct cgol_state){.width = 0, .height = 0, .grid = (void*)0,})

struct cgol_state {
    int width;  
    int height;
    int *grid;
};

struct cgol_state cgol_state_create(int width, int height, int initialised);
struct cgol_state cgol_state_create_randomised(int width, int height, double p);
void cgol_state_free(struct cgol_state s);   
int cgol_state_index(const struct cgol_state s, int col, int row); 
void cgol_state_set(struct cgol_state s, int col, int row, int value);
struct cgol_state cgol_state_generate_next(const struct cgol_state s);

#endif