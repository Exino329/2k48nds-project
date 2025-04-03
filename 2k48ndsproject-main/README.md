# 2048 NDS Project 

by Boucheny Rayan (327575) and Lieberherr Lorin (326858).

## Getting started

This readme is done to explain the 2048 rules and how to play the game on the NDS.

## 2048 Game rules

The game is represented by a 4x4 grid of 16 cells also named tiles. The goal is to make the maximum number of points during a game session and also reaching 2048 in the minimum possible time. Here are the rules of the game :

1. Cell neighbors : the neighbors of a cell are the ones directly below, to the left, above, and below the cell.

2. At each turn, the player will move the cells on the grid in one of the 4 directions : up , down, right or left. When doing this, all of the cells will be moved in the given direction. If two neighbors cells moved in the given direction have the same value, they will be merged into a cell representing the addition of the 2 cells and the player will gain points for each merge done. Here are some examples to have a better understanding of whats going on : 

- if a row of the grid has the values 2 - 4 - 4 - 16 and the player moves to the right, the updated row after the move will be : 0 - 2 - 8 - 16 (0 means that the cell is empty). the player gains 4 + 4 = 8 points for this row.

- if a row of the grid has the values 2 - 32 - 4 - 16 and the player moves the left, nothing will change in this row since there are no neighbors that have the same value. Hence the player gains 0 points for this row

- if a row of the grid has the values 8 - 8 - 8 - 8 and the player moves to the left, the resulting row will be : 16 - 16 - 0 - 0 because we are only allowed to merge two cells together. The player gains (8 + 8) + (8 + 8) = 32 points for this row.

(n.b. columns follow the same rules it was just easier to represent rows than columns for the explanantions)

3. After the player has done the move, One of the current empty cell (chosen randomly) will be filled with a value of 2 (with 90 % probability) or a 4 (with 10 % probability). And then the player can restart doing a move.

4. The game is lost when the player can't move anymore which means that the grid has no more empty cells AND that there is no neighboring cells having the same value.

5. The game starts with an initial cell filled exactly like in point 3. 


## Play 2048 On the Nintendo DS

The .nds file for the game is named 2k48ndsproject.nds

When launching the game, The menu screen will appear. You can switch menu option using the keys UP, DOWN, LEFT, RIGHT and select the desired option using key A. Touchscreen can also being used to select one of the menu option. If you are in the rules screen, you cann press B to go back to the menu. The game starts when you select start option and press key A.

When you are playing, you can move the cells of the 2048 up,down,right or left using the directional pad (at the left) of the NDS to move in the wanted direction. You can also use the touchscreen and swipe in the direction you want to move (you will maybe take some tries to habit yourself to the drag)


The score of the current game is showed in SCORE. BEST SCORE keep tracks of the best score of the player and display it. The best score is also stored in the NDS when you lose or restart the game. (N.B.) if you beat the best score and switch off the device, the score won't be remembered because it is only remembered when the games end (i.e. the player lose or the game is restarted).

The time indicates the time that has passed since the game has started. The best time is there to add a "speedrunning" dimension to the game. When the player manages to obtain a cell with a value of 2048 in a time less than the current best time (showed in BEST TIME on screen), it will be stored exactly in the same way as the best score. Note that a best time of 0 means that the player currently never reached 2048.

You can also restart a new game by pressing the key B when you are playing

(Note that we only handle cells values until 4096 included for the project so if you manage to break the game, you can consider yourself as a master of the game).

Finally, When the player loses (i.e. he can't move anymore) The up screen will remain and the down screen will say that the player lost and that he can restart to play by either pressing B