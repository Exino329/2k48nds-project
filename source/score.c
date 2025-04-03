#include <nds.h>
#include <stdio.h>

#include "timer.h"
#include "score.h"

/// Holds the current score and the best saved score 
unsigned int score = 0;
unsigned int best_score = 0; // maximum number of points the player has done during a game


void update_scores(unsigned int new_score) {

    // current score
    score = new_score;

	// keep track of the best score
    if (score > best_score) {
        best_score = score;
    }
	
    display_score();
	display_best_score();
}

void read_best_score(){

	// Open storage file in read mode
    FILE *file = fopen("/storage.txt", "r");

    if(file != NULL){

		// Read the best score stored in storage.txt
		fscanf(file, "%u\n", &best_score);
		fclose(file);
	}
}
void store_best_score(){

	// Open storage file to overwrite
	FILE *file = fopen("/storage.txt", "w+");

    if(file != NULL){
        
		// Write the best score
        fprintf(file, "%u\n", best_score);
        fclose(file);
    }
}
void display_score() {
    int j,i, number;
	//i, digit to display
	for(i = 5; i>0; i--)
	{
		//calculate the power of i-1 in j
		j = i-1; number = 1;
		while(j--)number = number*10;
		//Obtain the number to render
		number = score / number;
		number = number % 10;
		//Render the number
		BG_MAP_RAM(24)[Y_OFFSET_SCORE + X_OFFSET_SCORE + (5-i)] = timerMap[(number * 2)] | TILE_PALETTE(8);
		BG_MAP_RAM(24)[Y_OFFSET_SCORE + X_OFFSET_SCORE + (5-i) + NUM_TILE_W] = timerMap[(number * 2) + 1] | TILE_PALETTE(8);
	}
}

void display_best_score() {
    int j,i, number;
	//i, digit to display
	for(i = 5; i>0; i--)
	{
		//calculate the power of i-1 in j
		j = i-1; number = 1;
		while(j--)number = number*10;
		//Obtain the number to render
		number = best_score / number;
		number = number % 10;
		//Render the number
		BG_MAP_RAM(24)[Y_OFFSET_BEST_SCORE + X_OFFSET_SCORE + (5-i)] = timerMap[(number * 2)] | TILE_PALETTE(8);
		BG_MAP_RAM(24)[Y_OFFSET_BEST_SCORE + X_OFFSET_SCORE + (5-i) + NUM_TILE_W] = timerMap[(number * 2) + 1] | TILE_PALETTE(8);
	}

}
