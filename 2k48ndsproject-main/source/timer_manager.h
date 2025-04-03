#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

/// Tile map width 
#define NUM_TILE_W 32

/// Tile offset for timers
#define X_OFFSET_TIMER 24
#define Y_OFFSET_TIMER 14*32
#define Y_OFFSET_BEST_TIME 19*32

/// initalize the timer
void init_timer();

/// Stops the timer
void disable_timer();

/// Store the best time in a file in the NDS
void store_best_time();

void display_timer(int min, int sec);

/// Read the in a file from the NDS
void read_best_time();

/// Display the best time
void display_best_time();

#endif