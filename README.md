# conways-game-of-life
A basic implementation of Conway's Game Of Life written in C.
A small pet project that I am working on to get more comfortable with writing in C and using tools like GNU Make.
The code may not be particularly good but it has been a fun learning experience so far with more features to come provided that I'm still motivated.

![Video](/assets/imgs/random_grid.webp)

### Prerequisites:
- This project has not been tested on all platforms. Presumes a UNIX-like environment.
- Requires GNU Make
- Requires GCC

### Instructions to Build:
- Open your terminal application.
```bash
$ git clone https://github.com/sertralinefeverdream/conways-game-of-life.git
$ cd conways-game-of-life
$ make 
$ cd build
$ ./conways-game-of-life # Runs with the default flags
```
- `CTRL+C` to exit.

### Optional Command Line Flags
- When executed without the `-f` flag, a randomly generated grid with default game parameters is assumed.
- These default game parameters can be changed  
```bash
$ ./conways-game-of-life -g 10 -h 80 -w 100 -p 100
```
- `-g` : Generations per second. (Must be +ve non-zero positive integer) 
- `-h` : Grid height. (Must be +ve non-zero positive integer)
- `w` : Grid width. (Must be +ve non-zero positive integer)
- `-p` : Probability of a cell being generated alive in a randomly-generated grid. (Decimal value between 0 and 1)

## Loading From A File 
- When executed with the `-f` flag and provided with a valid file path to a file, we can load a preset grid.
```bash
$ ./conways-game-of-life -f <FILE PATH HERE>
```
- When executed, the `-h`, `-w`, and `-p` flags are ignored. We can still adjust the generations per second with `-g`.
```bash
$ ./conways-game-of-life -f <FILE PATH HERE> -g 20
```
- The format of any valid input file may look like this:
```
80
80
1,1
3,3
21,5
67,42
```

- Each line must be separated strictly with a new line character.
- The first line denotes the grid width and the second line denotes the grid height.
- Every subsequent line must be a comma-separated pair denoting the position of a single live cell in your preset grid and must fit within your defined grid dimensions. 
- Shown below is a valid file format that creates a small glider:
```
80
80
1,0
2,1
2,2
1,2
0,2
```
![Glider Video](/assets/imgs/glider.webp)

### Possible future improvements
- [X] Loading and saving grid presets in a file format.
- [X] Command line arguments to specify generations per second.
- [ ] Keyboard inputs to pause and resume the game.
    - [ ] Possibly the ability to edit in-place while paused?
 
## License
- This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

