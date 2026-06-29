#include "../include/cgol.h"
#include "../include/render.h"
#include "../include/cgol_file.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define DEFAULT_GPS 20
#define DEFAULT_WIDTH 80 
#define DEFAULT_HEIGHT 80
#define DEFAULT_PROBABILITY 0.09

static volatile sig_atomic_t running = 1;

static void signal_handler(int sig) {
    running = 0;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "No arguments supplied.\n");
        exit(EXIT_SUCCESS);
    }

    // render_init();
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGINT, signal_handler);
    
    unsigned generations_per_second = DEFAULT_GPS;
    int grid_width = DEFAULT_WIDTH; 
    int grid_height = DEFAULT_HEIGHT;
    double p = DEFAULT_PROBABILITY;
    
    struct cgol_state s;
    
    int loading_from_file = 0;
    for (int i = 1; i < argc; ++i) {
        fprintf(stderr, argv[i]);
        if (!strcmp(argv[i], "-f")) {
            const char *const file_path = argv[i+1];
            if (file_path == NULL) {
                fprintf(stdout, "No filepath supplied\n");
                exit(EXIT_FAILURE);
            }

            loading_from_file = 1;
            break;
        } else if (!strcmp(argv[i], "-h")) {  
            errno = 0; 
            const char* const h = argv[i+1];
            if (h == NULL) {
                fprintf(stderr, "No grid height supplied\n");
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
            
            long h_long = strtol(h, NULL, 10);
            int is_h_invalid = h_long <= 0 || h_long > INT_MAX;
            if (errno == ERANGE || errno == EINVAL || is_h_invalid) {
                fprintf(stderr, "Invalid height specified.\n");
                exit(EXIT_FAILURE);
            }

            grid_height = (int)h_long;
            ++i;
        } else if (!strcmp(argv[i], "-w")) {
            errno = 0;
            const char* const w = argv[i+1];
            if (w == NULL) {
                fprintf(stderr, "No grid width supplied\n");
                exit(EXIT_FAILURE);
            }
            
            long w_long = strtol(w, NULL, 10);
            int is_w_invalid = w_long <= 0 || w_long > INT_MAX;
            if (errno == ERANGE || errno == EINVAL || is_w_invalid) {
                fprintf(stderr, "Invalid width specified.\n");
                exit(EXIT_FAILURE);
            }
            
            grid_width = (int)w_long;
            ++i;
        } else if (!strcmp(argv[i], "-g")) {
           errno = 0; 
           const char *const g = argv[i+1];
           if (g == NULL) {
               fprintf(stderr, "No generation rate supplied\n");
               exit(EXIT_FAILURE);
           }
           
           long g_long = strtod(g, NULL);
           int is_g_invalid = g_long <= 0 || g_long > INT_MAX;
           if (errno == ERANGE || is_g_invalid) { 
               fprintf(stderr, "Invalid generation rate specified.\n");
               exit(EXIT_FAILURE);
           }
           
           generations_per_second = (unsigned)g_long;
           ++i;
        } else {
            fprintf(stderr, "Invalid flag supplied\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if (!loading_from_file) {
        s = cgol_state_create_randomised(grid_width, grid_height, p);
    }

    render_init();
    struct renderer r = renderer_create('O', generations_per_second);
    while (running) {
       wait_and_render(&r, s);
       struct cgol_state next_s = cgol_state_generate_next(s);
       cgol_state_free(s);
       s = next_s;
    }
    
    exit(EXIT_SUCCESS);
}