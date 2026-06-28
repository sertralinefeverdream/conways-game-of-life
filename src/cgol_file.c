#include "../include/cgol_file.h"
#include "../include/cgol.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

#define DELIMITER ','

/*
FILE Format:
100 - Screen Width
100 - Screen Height
50,50 - Live Cell at (50, 50)
1,1 - Live Cell at (50, 50)
{EOF} eof character somewhere
*/

static enum read_state {
    ERR,
    READING_WIDTH,
    READING_HEIGHT,
    READING_DATA,
};

struct cgol_state cgol_state_load_from_file(const char *const file_path) {
    FILE *f = fopen(file_path, "r");
    if (!f) {
        perror("Error trying to open file");
        return cgol_state_create(80, 80, INIT);
    }
    
    int width;
    int height;
    struct cgol_state s;
    
    enum read_state read_state = READING_WIDTH;
    char buf[256];

    while (fgets(f, sizeof(int)*256, buf) && read_state) {
        switch (read_state) {
            case READING_WIDTH:
                
            case READING_HEIGHT:

            case READING_DATA:
                
        }
    }
    
}

