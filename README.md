# conways-game-of-life
A basic implementation of Conway's Game Of Life written in C.
A small pet project that I am working on to get more comfortable with writing in C and using tools like GNU Make.
The code may not be particularly good but it has been a fun learning experience so far with more features to come provided that I'm still motivated.

### Prerequisites:
- This project has not been tested on all platforms. Presumes a UNIX-like/POSIX environment.
- Requires GNU Make
- Requires GCC

### Instructions to Run:
- Open your terminal application.
```bash
$ git clone https://github.com/sertralinefeverdream/conways-game-of-life.git
$ cd conways-game-of-life
$ make 
$ cd build
$ ./conways-game-of-life
```
- `CTRL+C` to exit.

### Changing the hard-coded preset
- Currently, the grid's initial cells are hardcoded until I am able to implement some sort of format to load in a pre-existing grid from a file. (Coming soon)
- `cd` into `src` and open `main.c` in your favourite text editor (Neovim)
- Follow the commented instructions
- Rebuild by running `make` at the project root in your terminal application.

### Possible future improvements
- Loading and saving grid presets in a file format.
- Command line arguments to specify generations per second.
- Keyboard inputs to pause and resume the game.
    - Possibly the ability to edit in-place while paused?
- Make `struct renderer` and `struct cgol_state` opaque types? (Not sure if necessary)
 
## License
- This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

