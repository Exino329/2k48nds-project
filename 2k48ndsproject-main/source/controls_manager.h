#ifndef CONTROLS_H
#define CONTROLS_H

#include "grid.h"
#include "start_menu.h"

void handle_touchpad_start(enum GameState* requestedState);

void handle_touchpad_game(Direction* direction);

void handle_return(enum MenuSelect* menuSelect, enum GameState* requestedState);

#endif // CONTROLS_H