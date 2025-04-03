#include <nds.h>
#include <stdio.h>

#include "timer.h"
#include "timer_manager.h"
unsigned int min, sec;

unsigned int best_time = 0; // best time is the minimum time the player achieved to obtain a cell with 2048 (0 if never reached)

/// ISR to handle the timer recording the time of the game
void ISR_TIMER0() {
    //TODO disable the timer when 2048 is reached
    sec = (sec + 1) % 60;
    if (sec == 0) {
        min++;
        // max time possible (should not be common! 99 minutes..)
        if (min == 99) 
            irqDisable(IRQ_TIMER0);
    }
}

/// ISR to refresh the timer text
void ISR_VBlank()
{
	display_timer(min, sec);
}

/// Initialise the timer IRQ
void init_timer() {
    min = sec = 0;
	TIMER_DATA(0) = TIMER_FREQ_1024(1);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);
    irqSet(IRQ_VBLANK, &ISR_VBlank);
	irqEnable(IRQ_VBLANK);
}

void disable_timer(){
    irqDisable(IRQ_TIMER0);
}

void read_best_time(){

	// Open time.txt file in read mode
    FILE *file = fopen("/time.txt", "r");

    if(file != NULL){

		// Read the best score stored in time.txt
		fscanf(file, "%u\n", &best_time);
		fclose(file);
	}
}

void store_best_time() {

    // Convert the current time in seconds
    unsigned int time = min * 60 + sec;

    // Define the best time
    if (time < best_time || best_time == 0) {
        best_time = time;
    }

	// Open time.txt file in read and write mode
	FILE *file = fopen("/time.txt", "w+");
    
    if (file != NULL) {

        // Store the best time
        fprintf(file, "%u\n", best_time);
        fclose(file);
    }
}

/// Display a time on the screen giving an y offset to display either the timer either the best time
void display_timer_text(int min, int sec, int y_offset) {
    int number, j;

    // Display seconds
    for (int i = 2; i > 0; --i){
        j = i - 1;
        number = 1;
        while(j--) number = number * 10;
        number = sec / number;
        number = number % 10;
        
        BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + (5-i)] = timerMap[(number * 2)] | TILE_PALETTE(8);
		BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + (5-i) + NUM_TILE_W] = timerMap[(number * 2) + 1] | TILE_PALETTE(8);
    }

    // Display the ':'
    BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + 2] = timerMap[20] | TILE_PALETTE(8);
	BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + 2 + NUM_TILE_W] = timerMap[21] | TILE_PALETTE(8);

    // Display minutes
    for (int i = 2; i > 0; --i){
        j = i - 1;
        number = 1;
        while(j--) number = number * 10;
        number = min / number;
        number = number % 10;
        
        BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + (2-i)] = timerMap[(number * 2)] | TILE_PALETTE(8);
		BG_MAP_RAM(24)[y_offset + X_OFFSET_TIMER + (2-i) + NUM_TILE_W] = timerMap[(number * 2) + 1] | TILE_PALETTE(8);
    }
}

/// Display the timer on the main screen
void display_timer(int min, int sec) {
    display_timer_text(min, sec, Y_OFFSET_TIMER);
}

/// Display the best time on the screen (0 if 2048 never reached)
void display_best_time() {
    display_timer_text(best_time / 60, best_time % 60, Y_OFFSET_BEST_TIME);
}

