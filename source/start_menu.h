#ifndef START_MENU_H
#define START_MENU_H

#include "grid.h"

enum MenuSelect {
    START_BUTTON,
    RULES_BUTTON
};

void display_rules(enum MenuSelect* menuSelect, enum GameState* requestedState);

void display_buttons();

void display_start_screen(enum MenuSelect* menuSelect, enum GameState* requestedState);

#endif // START_MENU_H