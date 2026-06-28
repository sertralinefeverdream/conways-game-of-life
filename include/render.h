#ifndef RENDER_H
#define RENDER_H

#include "cgol.h"

#include <stdio.h>
#include <time.h>

struct renderer {
    char cell_char;
    unsigned framerate;
    struct timespec last_update;
};

void render_cgol(struct renderer r, struct cgol_state s);
void render_init(void);
struct renderer renderer_create(char cell_char, unsigned framerate);
void wait_and_render(struct renderer *r, struct cgol_state s);

#endif