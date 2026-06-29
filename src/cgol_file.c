#include "../include/cgol_file.h"
#include "../include/cgol.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define DELIMITER ','
#define INVALID_CGOL_RETURN ((struct cgol_state){0, 0, (void*)0}) 

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
        return CGOL_STATE_NULL;
    }
   
    char first_char = fgetc(f);
    if (first_char == EOF) {
        return CGOL_STATE_NULL;
    }
    ungetc(first_char, f);

    int grid_width;
    int grid_height;
    struct cgol_state s; 
    
    enum read_state state = READING_WIDTH;
    char buf[256];

    while (fgets(buf, sizeof(char)*256, f) && state) {
        if (buf[0] == '\n') {
            continue;
        }

        switch (state) {
            case READING_WIDTH:
                errno = 0;
                long w_long = strtol(buf, NULL, 10);
                int is_w_invalid = w_long <= 0 || w_long > INT_MAX;
                if (errno == ERANGE || errno == EINVAL || is_w_invalid) {
                    state = ERR;
                    printf("Invalid w");
                    break;
                }
                
                grid_width = (int)w_long;
                state = READING_HEIGHT;
                break;
                
            case READING_HEIGHT:
                errno = 0;
                long h_long = strtol(buf, NULL, 10);
                int is_h_invalid = h_long <= 0 || h_long > INT_MAX;
                if (errno == ERANGE || errno == EINVAL || is_h_invalid) {
                    state = ERR;
                    break;
                }
                
                grid_height = (int)h_long;
                s = cgol_state_create(grid_width, grid_height, 1);
                state = READING_DATA;
                break;

            case READING_DATA:
                errno = 0;
                const char *const c = strtok(buf, ",");
                const char *const r = strtok(NULL, ",");
                if (!c || !r) {
                    state = ERR;
                    cgol_state_free(s);
                    break;
                }
                
                long c_long = strtol(c, NULL, 10);
                long r_long = strtol(r, NULL, 10);
                int is_c_invalid = c_long < 0 || c_long > grid_width - 1 || c_long > INT_MAX;
                int is_r_invalid = r_long < 0  || r_long > grid_height - 1 || r_long > INT_MAX;
                if (errno == ERANGE || errno == EINVAL || is_c_invalid || is_r_invalid) {
                   state = ERR;
                   cgol_state_free(s);
                   break;
                }
                
                cgol_state_set(s, (int)c_long, (int)r_long, 1);
                break;
        }
    }
    
    fclose(f);

    if (state == ERR) {
        return CGOL_STATE_NULL; 
    }
    
    return s;
}

