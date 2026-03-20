# Tic Tac Toe Game

## summation
This is a simple Tic-Tac-Toe written in C++.

* `clear()` : Reset the game.
* `place(player, locate)` : Place the player's(`0`, `1`) piece on the locate(`0`-`8`). (Returns the position on success, and `-1` on failure.)
* `unplace(locate)` : Removes the player's piece from locate(`0`-`8`). (Returns the position on success, and `-1` on failure.)
* `check()` : Returns the win/loss status. (`0`:X, `1`:O, `-1`:Draw or undecided)
* `*get_board_print(opening, x_mark, o_mark, blank, closing, line_end)` : Returns a string to display the Tic-Tac-Toe situation on the screen. (Some customization is possible)
* `get_next_optimal_place(player, depth_limit)` : The negamax (with alpha-beta pruning) algorithm returns the optimal position for the next move. (Which player will find the optimal position? `0`:X, `1`:O, Depth of exploration: `0`-`9`)

For optimal number calculation, the `_TIC_TAC_TOE_GAME_AUTO` macro is required.

## Compile
$ `g++ src/main.cpp lib/tictactoe.cpp -std=c++23 -I inc -Wall -D _TIC_TAC_TOE_GAME_AUTO`