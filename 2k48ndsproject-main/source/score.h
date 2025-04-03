#ifndef SCORE_H
#define SCORE_H

#define MAX_SCORE 99999

#define NUM_TILE_W 32

#define X_OFFSET_SCORE 24
#define Y_OFFSET_SCORE 4*32

#define Y_OFFSET_BEST_SCORE 9*32

/// Update the score and the best scores and display them
void update_scores(unsigned int new_score);

/// Read the best score from a file on the nds
void read_best_score();

/// Store the best score in a file on the nds
void store_best_score();

/// Display the score on the screen
void display_score();

/// Display the best score on the screen
void display_best_score();


#endif // SCORE_H