# Conways-Game-of-Life
The Game of Life is a simulation devised by the British mathematician John Horton Conway in 1970. You "play" this game by setting an initial input in a grid-like field and observing its evolution over each step in time.

The rules are as follows:
1. Any live cell with two or three neighbors survives.
2. Any dead cell with three live neighbors becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

# Compiling and running
To compile, use the following command in the file's directory
```
clang -lncurses -o conway conway.c
```
To run, simply type 
```
./conway
```
