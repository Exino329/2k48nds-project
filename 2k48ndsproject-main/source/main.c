/*
 * Template Nintendo DS
 * May 2011
 */
#include <nds.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fat.h>

#include "graphics_main.h"
#include "graphics_sub.h"
#include "grid.h"
#include "score.h"
#include "timer_manager.h"
#include "start_menu.h"
#include "controls_manager.h"

#include "back_top.h"
#include "numbers.h"
#include "start_sub_click.h"
#include "start_sub.h"
#include "start_sub_1.h"
#include "start_sub_2.h"
#include "rules.h"

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"



/// The direction done by the player (global for ISR)
Direction direction = NODIR;
/// State of the restart button
unsigned restart_pressed = 0;


/// ISR handling the keys
void keysISR()
{
	// Read the kEYINPUT register
	u16 keys = ~(REG_KEYINPUT);

	// Identify which key triggered the interrupt and print it in the console
	if (keys & KEY_UP) {
        direction = UP;
    }
    if (keys & KEY_DOWN) {
        direction = DOWN;
    }   
    if (keys & KEY_RIGHT) {
        direction = RIGHT;
    }      
    if (keys & KEY_LEFT) {
        direction = LEFT;
    }   
    if (keys & KEY_B) {
        direction = NODIR;
        REG_KEYCNT =  KEY_B | 1<<14;
        restart_pressed = 1;
    }
}

int main(void) {
    consoleDemoInit();

    // Initialise states and menu
    enum GameState requestedState = START;
    enum GameState currentState = NONE;
    enum MenuSelect menuSelect = START_BUTTON;

    // Initialise randomness
    srand(time(NULL));

    // Initialise file system
    fatInitDefault();

    // Load music and sound effects
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mmLoad(MOD_MUSIC);
    mmLoadEffect(SFX_BOOM);
    mmLoadEffect(SFX_LOSE);
    mmStart(MOD_MUSIC, MM_PLAY_LOOP);

    // Main loop
    while (1) {
        
        // Initialisation
        if (requestedState != currentState) {
            switch(requestedState) {
                case START:
                    // Initialise backgrounds
                    configure_start_main_BG0();
                    configure_start_sub_BG2();
                    break;
                case PLAYING:
                    // Initialise backgrounds
                    configure_playing_main_BG0();
                    configure_playing_main_BG2();
                    configure_main_sub_BG2();
                    // Initialise sprites
                    oamInit(&oamMain, SpriteMapping_1D_128, false);
                    configure_number((u8*)numbersTiles);
                    dmaCopy(numbersPal, SPRITE_PALETTE, numbersPalLen);
                    // Instanciate the 16 numbers
                    for (size_t y = 0; y < NUM_TILES / 4; ++y) {
                        int y_pos = y * 36 + TILES_START_Y;
                        for (size_t x = 0; x < NUM_TILES / 4; ++x) {
                            int x_pos = x * 36 + TILES_START_X;
                            numbers[y * 4 + x].y = y_pos;
                            numbers[y * 4 + x].x = x_pos; 
                            numbers[y * 4 + x].frame = (y * 4 + x) % NUM_SPRITE;
                        }
                    }
                    break;
                case LOSE:
                    configure_lose_sub_BG2();
                    break;
            }
            currentState = requestedState;
        }

        // Updating according to the state
        int keys;
        switch (currentState) {
            // START menu
            case START:
                display_start_screen(&menuSelect, &requestedState);
                handle_touchpad_start(&requestedState);
                swiWaitForVBlank();	
                break;
            // Showing the rules
            case RULES:
                handle_return(&menuSelect, &requestedState);
                swiWaitForVBlank();
                break;
            // player Lost
            case LOSE:
                handle_return(&menuSelect, &requestedState);
                swiWaitForVBlank();

                while(!restart_pressed){}
                requestedState = PLAYING;
                break;

            // Actual gameplay
            case PLAYING:
         
                unsigned int points = 0;
                int already_reached_2k48 = 0;
                restart_pressed = 0;
                // Resume music
                mmResume();
                
                // Load text informations
                read_best_score();
                update_scores(points);
                
                init_timer();
                read_best_time();
                display_best_time();

                // Initialise grid
                init_grid();
                spawn_tile();
                
                // Display the number sprites   
                update_sprites_gfx();         
             
                // Enable interrupts
                REG_KEYCNT = KEY_LEFT | KEY_RIGHT | KEY_DOWN | KEY_UP | KEY_B | 1<<14;
                irqSet(IRQ_KEYS, &keysISR);
                irqEnable(IRQ_KEYS);

                // Actual game (out of this loop = end of the game)
                while(can_move() && !restart_pressed) {      
                    handle_touchpad_game(&direction);

                    // Move
                    if(direction != NODIR) {
                        points += grid_move(direction);
                        if(!is_grid_full()){
                            spawn_tile(); 
                        }   

                        update_scores(points);
                        update_sprites_gfx();

                        // Handle best timer when 2048 is reached
                        if(!already_reached_2k48 && is_2k48_reached()){
                            disable_timer();
                            store_best_time();
                            display_best_time();
                            already_reached_2k48 = 1;
                        }

                        direction = NODIR;
                    }
                }

                if (!restart_pressed) {                 
                    // Update last time the graphics showing the grid state when losing
                    update_sprites_gfx();
                    disable_timer();

                    // End of the game effect
                    mmPause();
                    mmEffect(SFX_LOSE);
           
                    requestedState = LOSE;
                }
                // Store the best score when the game ends (i.e. player lost or has restart)
                store_best_score();
                break;
        }
    }
}


