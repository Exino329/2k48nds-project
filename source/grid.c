#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint-gcc.h>

#include "grid.h"

#define GRID_DIM 4
#define GRID_SIZE 16

/// Global variable that will represent the grid
Grid g; 

void init_grid(){
    g.index_list.size = GRID_SIZE;
    for(size_t i = 0;i < GRID_SIZE;++i){
        g.content[i/GRID_SIZE][i%GRID_SIZE] = 0;
        g.index_list.content[i] = i;
    }
}

int is_grid_full(){
    return g.index_list.size == 0 ? 1 : 0;
}

void update_grid_state(){
    size_t size = 0;
    for(size_t i = 0;i < GRID_SIZE;++i){
    
        // If the cell at index i is empty, add it to the index_list
        if(g.content[i/GRID_SIZE][i%GRID_SIZE] == 0){
            g.index_list.content[size] = i;
            ++size;
        }
    }
    g.index_list.size = size;
}


unsigned int remove_grid_element(unsigned int elem) {

    // Check correctness of arguments
    if (elem > GRID_SIZE || g.index_list.size == 0) {
        fprintf(stderr, "can't remove element");
        exit(EXIT_FAILURE);
    }

    // Search and "remove" the element in the index list which means to replace it by the element at index size-1 and then decrement the size
    for (size_t i = 0;i < g.index_list.size;++i) {
        if (g.index_list.content[i] == elem) {
            g.index_list.content[i] = g.index_list.content[g.index_list.size -1];
        }
    }
    --(g.index_list.size);
    return elem;
}

unsigned int spawn_tile() {
    if (is_grid_full()) {
        fprintf(stderr, "grid full can't make tile spawn");
        exit(EXIT_FAILURE);
    }

    // Generate a random number r between 0 and the size of the index list (not included)
    int r= rand() % g.index_list.size;

    // Remove the value at index r of the index_list
    unsigned int index = remove_grid_element(g.index_list.content[r]);

    // The cell being filled has 10% probability to being filled with a 4 and 90% probability to being filled with a 2
    int value = rand() % 10 == 0 ? 4 : 2;

    // Update the grid and insert the new value for the empty cell that must be filled
    g.content[index/GRID_DIM][index % GRID_DIM] = value;
    return index;
}

int is_2k48_reached() {

    for (size_t i = 0;i < GRID_SIZE;++i) {
        // Check if a cell is 2048
        if (g.content[i/GRID_SIZE][i%GRID_SIZE] >= 2048) {
            return 1;
        }
    }
    return 0;
}

int can_move() {

    // The player can't move if the grid is full and when there is no neighbours (diagonal not included) with the same value
    if (!is_grid_full()) {
        return 1;
    } else {
        // Check if 2 neighbours (diagonal not included) have the same value
        for (int i = 0; i < GRID_DIM; ++i){
            for (int j = 0; j < GRID_DIM; ++j){
                if(i-1 >= 0 && g.content[i][j] == g.content[i-1][j]){
                    return 1;
                }
                if(i+1 < GRID_DIM && g.content[i][j] == g.content[i+1][j]){
                    return 1;
                }
                if(j-1 >= 0 && g.content[i][j] == g.content[i][j-1]){
                    return 1;
                }
                if(j+1 < GRID_DIM && g.content[i][j] == g.content[i][j+1]){
                    return 1;
                }
            }
    
        }
        return 0;
    }
}


unsigned int grid_move(Direction direction) {
    unsigned int points = 0; 
    unsigned int tmp_row = 0;
    unsigned int tmp_col = 0;
    unsigned int prev_merged = 0; 

    if(direction == UP){

        // Iterates over grid columns
        for(int j = 0;j< GRID_DIM;++j){
            prev_merged = 0;
            
            // Iterates over grid rows in ascending order
            for(int i = 1;i < GRID_DIM;++i){
                tmp_row = i;

                // Move the cell up until it is at the highest row of the grid or its up neighbour is non zero
                while(tmp_row > 0 && g.content[tmp_row-1][j] == 0){
                    g.content[tmp_row-1][j] = g.content[tmp_row][j];
                    g.content[tmp_row][j] = 0;
                    --tmp_row;
                }

                // Merge the current cell with the up neighbours only if they have the same value and that the up neighbour has not already being merged
                if(tmp_row > 0 && g.content[tmp_row-1][j] == g.content[tmp_row][j] && !prev_merged){

                    prev_merged = 1;
                    g.content[tmp_row-1][j]*=2;
                    g.content[tmp_row][j] = 0;
                    points += g.content[tmp_row-1][j]; // Gain the points of the merge
                }else{
                    prev_merged = 0; 
                }
             }
        }
    }

    if(direction == DOWN){
        
        // Iterates over grid columns
        for(int j = 0;j< GRID_DIM;++j){
            prev_merged = 0;

             // Iterates over grid rows in descending order 
            for(int i = GRID_DIM -2;i >= 0;--i){
                tmp_row = i;
                
                // Move the cell down until it is at the lowest row of the grid or its down neighbour is non zero
                while (tmp_row < GRID_DIM - 1 && g.content[tmp_row+1][j] == 0) {
                    g.content[tmp_row+1][j] = g.content[tmp_row][j];
                    g.content[tmp_row][j] = 0;
                    ++tmp_row;
                }

                // Merge the current cell with the down neighbours only if they have the same value and that the down neighbour has not already being merged
                if (tmp_row < GRID_DIM - 1 && g.content[tmp_row+1][j] == g.content[tmp_row][j] && !prev_merged) {
                    prev_merged = 1;
                    g.content[tmp_row+1][j] *= 2;
                    g.content[tmp_row][j] = 0;
                    points += g.content[tmp_row+1][j]; // Gain the points of the merge
                }else{
                    prev_merged = 0;
                }
            }
        }
    }

    if(direction == RIGHT){

        // Iterates over grid rows
        for(int i = 0;i< GRID_DIM;++i){
            prev_merged = 0;

            // Iterates over grid columns in descending order 
            for(int j = GRID_DIM-2;j >= 0;--j){
                tmp_col = j;

                // Move the cell to the right until it is at the right border of the grid or its right neighbour is non zero
                while (tmp_col < GRID_DIM - 1 && g.content[i][tmp_col+1] == 0) {
                    g.content[i][tmp_col+1] = g.content[i][tmp_col];
                    g.content[i][tmp_col] = 0;
                    ++tmp_col;
                }

                // Merge the current cell with the right neighbours only if they have the same value and that the right neighbour has not already being merged
                if (tmp_col < GRID_DIM - 1 && g.content[i][tmp_col+1] == g.content[i][tmp_col] && !prev_merged) {
                    prev_merged = 1;
                    g.content[i][tmp_col+1] *= 2;
                    g.content[i][tmp_col] = 0;
                    points += g.content[i][tmp_col+1]; // Gain the points of the merge
                }else{
                    prev_merged = 0;
                }
            }
        }
    }

    if(direction == LEFT) {
        
        // Iterates over grid rows
        for (int i = 0; i < GRID_DIM; ++i) {
            prev_merged = 0;

            // Iterate over grid columns in ascending order 
            for (int j = 1; j < GRID_DIM; ++j) {
                tmp_col = j;

                // Move the cell to the left until it is at the left border of the grid or its left neighbour is non zero
                while (tmp_col > 0 && g.content[i][tmp_col - 1] == 0) {
                    g.content[i][tmp_col - 1] = g.content[i][tmp_col];
                    g.content[i][tmp_col] = 0;
                    --tmp_col;
                }

                // Merge the current cell with the left neighbours only if they have the same value and that the left neighbour has not already being merged
                if (tmp_col > 0 && g.content[i][tmp_col - 1] == g.content[i][tmp_col] && !prev_merged) {
                    prev_merged = 1;
                    g.content[i][tmp_col - 1] *= 2;
                    g.content[i][tmp_col] = 0;
                    points += g.content[i][tmp_col - 1]; // Gain the points of the merge
                }else{
                    prev_merged = 0;
                }
            }
        }
    }
    update_grid_state(); // Update the state of the grid after the movement has been done
    return points;
}
