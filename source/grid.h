#ifndef GRID_H
#define GRID_H

#include <stdint.h>

#define GRID_DIM 4 /// dimension of the grid
#define GRID_SIZE 16 /// size of the grid

enum GameState { 
    NONE = 0,
    START = 1,
    PLAYING = 2,
    LOSE = 3,
    RULES = 4
};

/// Struct index_list tracks the indexess of the 4x4 grid that are currently free (they are not containing a number which is represented by the value 0 in the grid)
typedef struct {
    /// Keep track of the current size of the index list
    size_t size; 
    /// Content of the index_list represented by a fixed size array of length NB_INDEX. Values in the range [0,size-1] are the current free index, rest of the array is considered as garbage
    unsigned int content[GRID_SIZE]; 
} IndexList;

/// Struct grid represents the grid state of the 2048 games
typedef struct {
    /// Contains the current values of each cell (empty cell is represented by value 0)
    uint32_t content[GRID_DIM][GRID_DIM];
    /// Keep track of all the current empty cells of the grid
    IndexList index_list; 
} Grid;

/// Grid of the game
extern Grid g; 

/// The enum Direction will represents the 4 possible ways to move the cells in the grid
typedef enum {
    NODIR,
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

/// Initialize the grid 
void init_grid(void);

/// Check if the greed is full (i.e. contains no empty cells). Returns 1 in case of success 0 in case of failure
int is_grid_full(void);

/// Insert a 2 or a 4 (with respectively 90% and 10% of probability) in one of the current empty cell and return the index of the new filled cell
unsigned int spawn_tile(void);

/// Update the state of the grid by tracking all empty cell and modify the index_list of the grid accordingly
void update_grid_state(void);

/// Check if a cell has value 2048 
int is_2k48_reached();

/// Check if the player is still able to move in a direction, returns 1 in case of success, 0 in case of failure
int can_move();

/*
 *  Move the cells in the given direction according to the 2048 rules. This method is also responsible to merge non zero neighbours having the same value 
 *  and to update the state of the grid accordingly. Returns the number of points gained by doing the given move (can be 0 if we can't move in the given direction)
 */
unsigned int grid_move(Direction direction);

#endif /* GRID_H */