//PLEASE COMPILE AS FOLLOWS: clang -lncurses -o conway conway.c


    /***********************************************************************
     * Name(s)   Timur Kasimov and Bryant Nguyen                           *
     * Assignment name (Project 3: Conway's Game of Life)                  *
     *                                                                     *
     * Assignment for November 7th, 2022                                   *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life            *
     *    https://tldp.org/HOWTO/pdf/NCURSES-Programming-HOWTO.pdf         *
     * https://johnsonba.cs.grinnell.edu/CSC161/2022F/struct-2d-arrays/labs*
     *          /conwaygameoflife.html                                     *
     *   Help obtained                                                     *
     *          none                                                       *
     *                                                                     *
     *                                                                     *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: Timur Kasimov and Bryant Nguyen                        *
     ***********************************************************************/
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 20
#define COLS 40


//initial configuration of the well-known oscillator called toad
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: none
void
toad(int gameboard[ROWS][COLS]);

//initial configuration of the well-known oscillator called pulsar
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: none
void
pulsar(int gameboard[ROWS][COLS]);

//initial configuration of the well-known space-ship pattern called glider
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: none
void
glider(int gameboard[ROWS][COLS]);


//initial configuration of a random gameboard
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: none
void
random_board(int gameboard[ROWS][COLS]);


//counts the number of neighbours a cell has
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: returns integer
int
count_adjacent(int gameboard[ROWS][COLS], int i, int j);


//prints gameboard with dots for dead and X for alive
//pre-conditions: takes in a2d array of size 20x40
//post-conditions: none
void
printGameboard(int gameboard[ROWS][COLS]);


//saves the next iteration/round of the game in a temporary 2d array
//pre-conditions: takes in two 2d arrays of size 20x40
//post-conditions: none
void
save_temp_value(int temp_board[ROWS][COLS], int gameboard[ROWS][COLS]);


//copies the next round values from temporary array to the main gameboard
//pre-conditions: takes in two 2d arrays of size 20x40
//post-conditions: none
void
cpy_array(int temp_board[ROWS][COLS], int gameboard[ROWS][COLS]);


//This program presents Conway's game of life.
int main()
{

  //initializing ncurses screen
  initscr();


 
  if (has_colors()) //check whether terminal can handle colors
    {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK); //initialize color pair 1, Cyan on Black
    attron(COLOR_PAIR(1)); //turn on color pair 1
    }

    
  //initializaing variables
  int i = 0, iterations = 0;

  
  int gameboard[ROWS][COLS] = {0}; //main gameboard

  
  int temp_board[ROWS][COLS]= {0}; // temporary gameboard

  
  //Intializes random number generator
  srand((unsigned) time(NULL));


  //introducing the game
  printw("The Game of Life is a simulation devised by the British mathematician\nJohn Horton Conway in 1970.\nYou \"play\" this game by setting an initial input in a grid-like field and\nobserving its evolution over each step in time.\nThe rules are as follows:\n\t1.Any live cell with two or three neighbors survives.\n\t2.Any dead cell with three live neighbors becomes a live cell.\n\t3.All other live cells die in the next generation. Similarly, all other dead\n\tcells stay dead.\n\n");

  
  refresh(); //printing to the ncurses screen
  napms(1000); //sleep for 1 second



  //introducing options for initial configuation of the board
  printw("Choose one of the following options for initial configuration of the board\nby typing in a corresponding letter:\n");
  printw("t: Toad\n");
  printw("g: Glider\n");
  printw("p: Pulsar\n");
  printw("r: Random\n");
  refresh();


  //reading in selected option
  char option = 0;
  scanw("%c", &option);

  switch(option){
  case 't' :
    toad(gameboard); //calling to functions that set initial gameboard configuation
    break;
  case 'g' :
    glider(gameboard);
    break;
  case 'p' :
    pulsar(gameboard);
    break;
  case 'r' :
    random_board(gameboard);
    break;
  default :
    printw("No such option, set to random by default\n"); //set to random by default
    random_board(gameboard);
  }

  //reading in the number of rounds
  printw("Enter the amount of rounds:\n");
  scanw("%d", &iterations);


  // clearing the ncurses screen
  clear();
  

  
  //printing the initial gameboard with X for alive and . for dead
  printw("Initial Configuration:\n");
  printGameboard(gameboard);
  printw("Press any key to start simulation\n"); 
  refresh();
  getchar(); //waiting for the user to start the simulation


  
  //removes cursor
  curs_set(0);

    
  //looping through the selected number of rounds
  for (i = 1; i <= iterations; i++){

    //saving temporary array
    save_temp_value(temp_board, gameboard);

    //copying array from temporary to main gameboard
    cpy_array(temp_board, gameboard);
    
    
    //printing new array
    clear();
    printw("Round %d\n", i); //printing the round number
    printGameboard(gameboard);
    refresh();
    napms(750); //program pauses between rounds so user can see the progress
  
  }


  
  printw("Press any key to finish the program\n");


  //turns off color pair if it was turned on
  if (has_colors()) //
    {
      attroff(COLOR_PAIR(1)); //turns off color pair
      use_default_colors(); //sets to default colors
    }
  
 curs_set(1); //returns cursor
  refresh();
  getch(); //waiting for user to end program
  endwin(); // closes the ncurses window
  return 0;
} // end main

     



int count_adjacent(int gameboard[ROWS][COLS], int i, int j)
{
  int num_adjacent = 0;
    //edge cases

    
  if (i != 0 && j!= (COLS-1) && gameboard[i-1][j+1]) //top right corner
    num_adjacent++;
  
  if (j != (COLS-1) && gameboard[i][j+1]) // right 
    num_adjacent++;
  
  if (i != (ROWS -1) && j!= (COLS-1) && gameboard[i+1][j+1]) //bottom right 
    num_adjacent++;
  
  if (i != 0 && gameboard[i-1][j]) // top
    num_adjacent++;
  
  if (i != (ROWS -1) && gameboard[i+1][j]) //bottom
    num_adjacent++;
  
  if (i != 0 && j!= 0  && gameboard[i-1][j-1]) //top left
    num_adjacent++;
  
  if (j!= 0  && gameboard[i][j-1])// left
    num_adjacent++;
  
  if (i != (ROWS -1) && j!= 0 && gameboard[i+1][j-1]) //bottom left
    num_adjacent++;

  return num_adjacent;
}





void
printGameboard(int gameboard[ROWS][COLS]){
  char alive = 'X'; // X for alive
  char dead = '.'; // . for dead
  int i, j;

  //nested loop to print each column within each row
  for (i = 0; i<ROWS; i++)
    {
      for (j = 0; j < COLS; j++)
        {
          if (gameboard[i][j])
            {
              printw("%-2c", alive);              
            }
          else {
            printw("%-2c", dead);            
          }
        }
      printw("\n"); //moving on to new row
    }
  
}




void
save_temp_value(int temp_board[ROWS][COLS], int gameboard[ROWS][COLS]){
   int value = 0;
   int i,   j;
   for (i = 0; i<ROWS; i++)
    {
      for (j = 0; j < COLS; j++)
        {
          // calls to count_adjacent and records the number of neighbors
          value = count_adjacent(gameboard, i, j); 
          if (value == 2)
            temp_board[i][j] = gameboard[i][j]; //remains same
          if (value == 3)
            temp_board[i][j] = 1; //becomes alive 
          if (value < 2 || value > 3)
            temp_board[i][j] = 0; //dies from under-/overpopulation
        }
    } 
}




void
cpy_array(int temp_board[ROWS][COLS], int gameboard[ROWS][COLS]){
  int i, j;
  for (i = 0; i<ROWS; i++)
    {
      for (j = 0; j < COLS; j++)
        {
          gameboard[i][j] = temp_board[i][j]; //copying temporary gameboard into main gameboard
        }
    }
}



void
toad(int gameboard[ROWS][COLS]){
  gameboard[2][2] = gameboard[2][3] = gameboard[2][4] = 1;
  gameboard[3][1] = gameboard[3][2] = gameboard[3][3] = 1;
} //configuration for toad



void
glider(int gameboard[ROWS][COLS]){
  gameboard[0][1] = gameboard[1][2]  = 1;
  gameboard[2][0] = gameboard[2][1] = gameboard[2][2] = 1;
}//configuration for glider



void
pulsar(int gameboard[ROWS][COLS]){
  //horizontal stripes
  gameboard[2][4] = gameboard[2][5] = gameboard[2][6] = gameboard[2][10] = gameboard[2][11] = gameboard[2][12] =  1;
  gameboard[9][4] = gameboard[9][5] = gameboard[9][6] = gameboard[9][10] = gameboard[9][11] = gameboard[9][12] =  1;
  gameboard[7][4] = gameboard[7][5] = gameboard[7][6] = gameboard[7][10] = gameboard[7][11] = gameboard[7][12] =  1;
  gameboard[14][4] = gameboard[14][5] = gameboard[14][6] = gameboard[14][10] = gameboard[14][11] = gameboard[14][12] =  1;

  //vertical stripes
  gameboard[4][2] = gameboard[5][2] = gameboard[6][2] = gameboard[10][2] = gameboard[11][2] = gameboard[12][2] =  1;
  gameboard[4][9] = gameboard[5][9] = gameboard[6][9] = gameboard[10][9] = gameboard[11][9] = gameboard[12][9] =  1;
  gameboard[4][7] = gameboard[5][7] = gameboard[6][7] = gameboard[10][7] = gameboard[11][7] = gameboard[12][7] =  1;
  gameboard[4][14] = gameboard[5][14] = gameboard[6][14] = gameboard[10][14] = gameboard[11][14] = gameboard[12][14] =  1; 
}//configuration for pulsar



void
random_board(int gameboard[ROWS][COLS])
{
  int i = 0, j = 0;
  
  for (i = 0; i<ROWS; i++)
    {
      for (j = 0; j < COLS; j++)
        {
          gameboard[i][j] = (rand() % 2); //randomly assigning each cell's value to alive or dead
        }
    }
}
