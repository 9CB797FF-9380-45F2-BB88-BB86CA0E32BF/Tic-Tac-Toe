// include
#include <iostream>
#include <string>
#include <tictactoe.hpp>

// main function(demo)
int main(int argc, char* argv[]) {
    int8_t player;
    int8_t now;

    char one_char;
    int8_t temp_int;

	TicTacToeGame::TicTacToeGame *game_board = new TicTacToeGame::TicTacToeGame();
    
    std::cout << "select O or X :";
    std::cin >> one_char;

    switch (one_char) {
        case 'O': case 'o':
            player = 1;
            break;
        case 'X': case 'x':
            player = -1;
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            return -1;
    }

    now = player;
    std::cout << "Game Start! You start first!" << std::endl;
    std::cout << game_board->get_board_print() << std::endl;

    for (int8_t step = 0; step < 9; step++) {
        if (player == now) {
            while (1) {
                std::cout << "Where will you put it? (0~8): " << std::endl;
                std::cin >> one_char;
                temp_int = one_char - '0';
                if (temp_int < 0 || temp_int > 8)
                    continue;
                temp_int = game_board->place(player < 0 ? 0 : 1, temp_int);
                if (temp_int != -1)
                    break;
            }
        }
        else {
            game_board->place(-player < 0 ? 0 : 1, game_board->get_next_optimal_place(-player < 0 ? 0 : 1));
            std::cout << "The opposing player made a move: " << std::endl;
        }

        std::cout << game_board->get_board_print() << std::endl;

        temp_int = game_board->check();

        if (temp_int == 0) {
            std::cout << "X is Win!" << std::endl;
            break;
        }
        else if (temp_int == 1) {
            std::cout << "O is Win!" << std::endl;
            break;
        }
        else if (temp_int == -1 && step == 8)
            std::cout << "Draw!" << std::endl;

        now = -now;
    }
    std::cout << "Game End!" << std::endl;
    delete game_board;
	return 0;
}
