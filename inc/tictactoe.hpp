#ifndef _TIC_TAC_TOE_GAME
#define _TIC_TAC_TOE_GAME
namespace TicTacToeGame {
    class TicTacToeGame {
        private:
            static const u_int16_t _BOARD_FFIELD_BIT_MASK;
            static const u_int16_t _OTHER_FIELD_BIT_MASK;
            static const u_int8_t _OTHER_FIELD_SIZE;
            static const u_int16_t _DIAGONAL_MATCH_PATTERN;
            u_int16_t _player_O_status_and_general; // Placed[0-8], General[9-15]
            u_int16_t _player_X_status_and_vmatch; // Placed[0-8], vertical match pattern base[9-15]
            #ifdef _TIC_TAC_TOE_GAME_AUTO
            int8_t _negamax(u_int8_t depth, int8_t alpha, int8_t beta, int8_t player);
            #endif

        public:
            TicTacToeGame(); // Constructor
            void clear(); // Clear
            int8_t place(u_int8_t player, u_int8_t locate); // player do place / player: 0->X, 1->O / locate: 0-8
            int8_t unplace(u_int8_t locate); // player undo place / locate: 0-8
            int8_t check(); // Determining victory, loss or defeat
            std::string get_board_print(char opening = '[', char x_mark = 'X', char o_mark = 'O', char blank = ' ', char closing = ']', char line_end = '\n'); // get board for print
            #ifdef _TIC_TAC_TOE_GAME_AUTO
            int8_t get_next_optimal_place(u_int8_t player, u_int8_t depth_limit = 9); // Calculate the next optimal number / player: 0->X, 1->O
            #endif
    };
}
#endif
