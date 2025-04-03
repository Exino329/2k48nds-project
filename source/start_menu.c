#include <nds.h>
#include <stdio.h>

#include "start_menu.h"

#include "start_sub_1.h"
#include "start_sub_2.h"
#include "rules.h"
#include "grid.h"

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

/// Animate the buttons of the start menu
void switch_button(enum MenuSelect* menuSelect) {
    if (*menuSelect == START_BUTTON) {
        swiCopy(start_sub_2Bitmap, BG_GFX_SUB, start_sub_2BitmapLen/2);
        swiCopy(start_sub_2Pal, BG_PALETTE_SUB, start_sub_2PalLen/2);
        *menuSelect = RULES_BUTTON;
    } else if (*menuSelect == RULES_BUTTON) {
        swiCopy(start_sub_1Bitmap, BG_GFX_SUB, start_sub_1BitmapLen/2);
        swiCopy(start_sub_1Pal, BG_PALETTE_SUB, start_sub_1PalLen/2);
        *menuSelect = START_BUTTON;
    }
}

/// Display the rules menu
void display_rules(enum MenuSelect* menuSelect, enum GameState* requestedState) {
    scanKeys();
    int keys = keysDown();

    if (keys) {
        if (keys & KEY_B) {
            *requestedState = START;
            *menuSelect = START_BUTTON;
        }
    }
}

/// Display the start screen menu
void display_start_screen(enum MenuSelect* menuSelect, enum GameState* requestedState) {
    scanKeys();
    int keys = keysUp();

    if (keys) {
        // A 
        if (keys & KEY_A) {
            // Start the game
            if (*menuSelect == START_BUTTON) {
                *requestedState = PLAYING;
            } else if (*menuSelect == RULES_BUTTON) {
                *requestedState = RULES;
                swiCopy(rulesBitmap, BG_GFX_SUB, rulesBitmapLen/2);
                swiCopy(rulesPal, BG_PALETTE_SUB, rulesPalLen/2);
            }
        }
        // UP, DOWN, RIGHT, LEFT
        else if (keys & KEY_UP || keys & KEY_DOWN || keys & KEY_RIGHT || keys & KEY_LEFT) {
            mmEffect(SFX_BOOM);
            switch_button(menuSelect);
        }
    }
}