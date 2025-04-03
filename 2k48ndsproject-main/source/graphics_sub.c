#include <nds.h>
#include <stdio.h>

#include "controls.h"
#include "start_sub.h"
#include "start_sub_click.h"
#include "back_sub.h"
#include "lose_sub.h"
#include "start_sub_1.h"

/// ---- START ---- ///

/// Setup the start menu main engine background
void configure_start_sub_BG2() {
    REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    BGCTRL_SUB[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

    swiCopy(start_sub_1Bitmap, BG_GFX_SUB, start_sub_1BitmapLen/2);
	swiCopy(start_sub_1Pal, BG_PALETTE_SUB, start_sub_1PalLen/2);

    REG_BG2PA_SUB = 1*256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 1*256;
}

/// ---- PLAYING ---- ///

/// Initialise the game sub engine background
void configure_main_sub_BG2() {   
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	BGCTRL_SUB[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

	swiCopy(back_subBitmap, BG_GFX_SUB, back_subBitmapLen/2);
	swiCopy(back_subPal,BG_PALETTE_SUB, back_subPalLen/2);

    REG_BG2PA_SUB = 1*256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 1*256;
}

/// ---- LOSE ---- ///

/// Setup the start menu main engine background
void configure_lose_sub_BG2() {
    REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    BGCTRL_SUB[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

    swiCopy(lose_subBitmap, BG_GFX_SUB, lose_subBitmapLen/2);
	swiCopy(lose_subPal, BG_PALETTE_SUB, lose_subPalLen/2);

    REG_BG2PA_SUB = 1*256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 1*256;
}
