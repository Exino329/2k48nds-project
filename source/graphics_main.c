#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "graphics_main.h"
#include "grid.h"

#include "numbers.h"
#include "back_top.h"
#include "start_top.h"
#include "timer.h"
#include "lose_top.h"

/// Array of 16 tiles
Number numbers[NUM_TILES]; 

/// Holding the sprites for numbers
u16* sprite_memory[NUM_SPRITE];

/// Update the sprites depending on the grid state
void update_sprites_gfx(){
       for (size_t i = 0; i < NUM_TILES; ++i) {
            numbers[i].frame = g.content[i/GRID_SIZE][i%GRID_SIZE] == 0 ? 0 : log2(g.content[i/GRID_SIZE][i%GRID_SIZE]);
            oamSet(&oamMain, i, numbers[i].x, numbers[i].y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
                    sprite_memory[numbers[i].frame], -1, false, false, false, false, false);
        }
        swiWaitForVBlank();	
        oamUpdate(&oamMain);
}
/// ---- START ---- ///

/// Setup the start menu main engine background
void configure_start_main_BG0() {
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
    BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;

    swiCopy(start_topTiles, BG_TILE_RAM(1), start_topTilesLen/2);
	swiCopy(start_topPal, BG_PALETTE, start_topPalLen/2);
	swiCopy(start_topMap, BG_MAP_RAM(0), start_topMapLen/2);
}

/// ---- PLAYING ---- ///

/// Setup the playing state main engine background
void configure_playing_main_BG2() {
    // Initialise the engine and VRAM
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG2_ACTIVE;
    BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

    REG_BG2PA = 1*256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 1*256;

    // Copy the background to memory
    swiCopy(back_topBitmap, BG_GFX, back_topBitmapLen/2);
	swiCopy(back_topPal, BG_PALETTE, back_topPalLen/2); 
}

/// Setup the playing state second main engine background
void configure_playing_main_BG0() {
    BGCTRL[0] = BG_COLOR_16 | BG_MAP_BASE(24) | BG_TILE_BASE(4) | BG_32x32 | BG_PRIORITY(0);
	dmaCopy(timerTiles, BG_TILE_RAM(4), timerTilesLen);
	dmaCopy(timerPal, &BG_PALETTE[128], timerPalLen);
	dmaCopy(timerPal, &BG_PALETTE[144], timerPalLen);
	BG_PALETTE[129] = ARGB16(1,31,0,0);
	BG_PALETTE[145] = ARGB16(1,0,31,0);

	// Clean the tiles map
	int x = 32*32;
	while(x--)
		BG_MAP_RAM(24)[x] = 0;
    
}

/// Setup the numbers tiles
void configure_number(u8* gfx) {
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

    for (size_t i = 0; i < NUM_SPRITE; ++i) {
        sprite_memory[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
        dmaCopy(gfx, sprite_memory[i], 32*32);
        gfx += 32*32;
    }
}

/// Change a tile value and its sprite accordingly
void change_number(Number* tile, int new_value) {
    tile->frame = new_value % NUM_SPRITE;
}

/// ---- LOSE ---- ///

/// Setup the lose menu main engine background
/// Not used in the final game, but kept
void configure_lose_main_BG0() {
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
    REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
    BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;

    swiCopy(lose_topTiles, BG_TILE_RAM(1), lose_topTilesLen/2);
	swiCopy(lose_topPal, BG_PALETTE, lose_topPalLen/2);
	swiCopy(lose_topMap, BG_MAP_RAM(0), lose_topMapLen/2);
}