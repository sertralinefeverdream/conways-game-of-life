#ifndef CGOL_FILE_H
#define CGOL_FILE_H

#define CGOL_STATE_NULL (struct cgol_state){.width = 0, .height = 0, .grid = (void*)0,}

struct cgol_state cgol_state_load_from_file(const char* const file_path, int *success);

#endif