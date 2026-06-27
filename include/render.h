#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include "cgol.h"

struct renderer {
    char cell_char;
};

void render_cgol(struct renderer r, struct cgol_state s);
void render_init(void);

#endif