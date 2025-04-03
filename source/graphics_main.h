#ifndef GRAPHICS_MAIN_H
#define GRAPHICS_MAIN_H

#include <nds.h>
#include <stdio.h>

#include "grid.h"

/// Dimensions of the main screen
#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

/// Dimensions of sprites
#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32

/// Numbers of sprite to allocate and initialize
#define NUM_SPRITE 13 // 12 numbers + empty tile (0)

/// Number of number tiles to be displayed
#define NUM_TILES 16

/// Start of the numbers tiles
#define TILES_START_X 24
#define TILES_START_Y 27

/// Struct holding information for a number tile
typedef struct {
	/// Absolute position of the tile
	int x;
	int y;
    /// GFX frame
    u16* sprite;
    int frame;
} Number;

/// Array of 16 tilesl
extern Number numbers[NUM_TILES]; 

/// Update sprites graphics
void update_sprites_gfx();


/// ----  START  ---- ///
void configure_start_main_BG0();

/// ---- PLAYING ---- ///
void configure_playing_main_BG0();

void configure_playing_main_BG2();

void configure_number(u8* gfx);

void change_number(Number* tile, int new_value);

void configure_tiles();

/// ---- LOSE ---- ///
void configure_lose_main_BG0();

#endif // GRAPHICS_MAIN_H