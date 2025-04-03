#include <nds.h>
#include <stdio.h>

#include "controls_manager.h"
#include "start_menu.h"
#include "grid.h"

#include "rules.h"

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

/// Touchpad polling for the game
void handle_touchpad_game(Direction* direction) {
    // Touchpad reading
    scanKeys();
    unsigned down = keysDown();
    unsigned up = keysUp();
    unsigned held = keysHeld();
    touchPosition touchFirst;
    touchPosition touchSecond;
    if (down & KEY_TOUCH) {
        touchRead(&touchFirst);
    }
    if (held & KEY_TOUCH) {                   
        touchRead(&touchSecond);
    }
    if (up & KEY_TOUCH) {
        int diff_X = touchSecond.px - touchFirst.px;
        int diff_Y = touchSecond.py - touchFirst.py;

        // Move right or left
        if (abs(diff_X) >= abs(diff_Y)) {
            if (diff_X > 0)
                *direction = RIGHT;
            else
                *direction = LEFT;
        } else if (abs(diff_X) < abs(diff_Y)) {
            if (diff_Y > 0)
                *direction = DOWN;
            else
                *direction = UP;
        }
    }
}

/// Touchpad polling for the start menu
void handle_touchpad_start(enum GameState* requestedState) {
    scanKeys();
    touchPosition touch;
    touchRead(&touch);

    if (67 <= touch.px && touch.px <= 239) {
        // START
        if (18 <= touch.py && touch.py <= 56) {
            *requestedState = PLAYING;
        // RULES
        }
        if (65 <= touch.py && touch.py <= 103) {
            *requestedState = RULES;
            swiCopy(rulesBitmap, BG_GFX_SUB, rulesBitmapLen/2);
            swiCopy(rulesPal, BG_PALETTE_SUB, rulesPalLen/2);
        }
    }
}

/// Handle the 'B' return button on menus
void handle_return(enum MenuSelect* menuSelect, enum GameState* requestedState) {
    scanKeys();
    int keys = keysDown();

    if (keys) {
        if (keys & KEY_B) {
            *requestedState = START;
            *menuSelect = START_BUTTON;
        }
    }
}