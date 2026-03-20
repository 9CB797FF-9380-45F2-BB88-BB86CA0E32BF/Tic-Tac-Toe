#include <iostream>
#include <tictactoe.hpp>

const u_int16_t TicTacToeGame::TicTacToeGame::_BOARD_FFIELD_BIT_MASK = 0xFF80;
const u_int16_t TicTacToeGame::TicTacToeGame::_OTHER_FIELD_BIT_MASK = 0x7F;
const u_int8_t TicTacToeGame::TicTacToeGame::_OTHER_FIELD_SIZE = 7;
const u_int16_t TicTacToeGame::TicTacToeGame::_DIAGONAL_MATCH_PATTERN = 0x1511;

TicTacToeGame::TicTacToeGame::TicTacToeGame() {
	this->clear();
}

void TicTacToeGame::TicTacToeGame::clear() {
	this->_player_O_status_and_general = 0;
	this->_player_X_status_and_vmatch = 0x49;
}

int8_t TicTacToeGame::TicTacToeGame::place(u_int8_t player, u_int8_t locate) {
	u_int16_t index_bitmask;
	if (player > 1 || locate > 8)
		return -1;
	index_bitmask = 1 << (8 - locate + this->_OTHER_FIELD_SIZE);
	if (player) {
		if(!(this->_player_X_status_and_vmatch & index_bitmask || this->_player_O_status_and_general & index_bitmask))
			this->_player_O_status_and_general = this->_player_O_status_and_general | index_bitmask;
		else
			return -1;
	}
	else {
		if(!(this->_player_O_status_and_general & index_bitmask || this->_player_X_status_and_vmatch & index_bitmask))
			this->_player_X_status_and_vmatch = this->_player_X_status_and_vmatch | index_bitmask;
		else
			return -1;
	}
	return locate;	
}

int8_t TicTacToeGame::TicTacToeGame::unplace(u_int8_t locate) {
	u_int16_t index_bitmask;
	if (locate > 8)
		return -1;
	index_bitmask = 1 << (8 - locate + this->_OTHER_FIELD_SIZE);
	this->_player_X_status_and_vmatch = this->_player_X_status_and_vmatch & ~index_bitmask;
	this->_player_O_status_and_general = this->_player_O_status_and_general & ~index_bitmask;
	return locate;
}

int8_t TicTacToeGame::TicTacToeGame::check() {
	for (this->_player_O_status_and_general = this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK; (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) < 3; this->_player_O_status_and_general = (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) | (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1) {
		if ((((this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 0b111 << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) * 3) == 0b111 << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) * 3) || (((this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & (this->_player_X_status_and_vmatch & this->_OTHER_FIELD_BIT_MASK) << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK)) == (this->_player_X_status_and_vmatch & this->_OTHER_FIELD_BIT_MASK) << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK)))
			return 0;
		if ((((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 0b111 << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) * 3) == 0b111 << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) * 3) || (((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & (this->_player_X_status_and_vmatch & this->_OTHER_FIELD_BIT_MASK) << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK)) == (this->_player_X_status_and_vmatch & this->_OTHER_FIELD_BIT_MASK) << (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK)))
			return 1;
	}
	if ((((this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & (this->_DIAGONAL_MATCH_PATTERN & 0x1FF)) == (this->_DIAGONAL_MATCH_PATTERN & 0x1FF)) || (((this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & this->_DIAGONAL_MATCH_PATTERN >> 6) == this->_DIAGONAL_MATCH_PATTERN >> 6))
		return 0;
	if ((((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & (this->_DIAGONAL_MATCH_PATTERN & 0x1FF)) == (this->_DIAGONAL_MATCH_PATTERN & 0x1FF)) || (((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & this->_DIAGONAL_MATCH_PATTERN >> 6) == this->_DIAGONAL_MATCH_PATTERN >> 6))
		return 1;
	return -1;
}

std::string TicTacToeGame::TicTacToeGame::get_board_print(char opening, char x_mark, char o_mark, char blank, char closing, char line_end) {
	std::string board;
	board.resize(30);
	this->_player_O_status_and_general = this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK;
	while((this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) < 30) {
		board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK)] = opening;
		switch (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) {
			case 0:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 8 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 8 ? o_mark : blank;
				break;
			case 3:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 7 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 7 ? o_mark : blank;
				break;
			case 6:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 6 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 6 ? o_mark : blank;
				break;
			case 10:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 5 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 5 ? o_mark : blank;
				break;
			case 13:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 4 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 4 ? o_mark : blank;
				break;
			case 16:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 3 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 3 ? o_mark : blank;
				break;
			case 20:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 2 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 2 ? o_mark : blank;
				break;
			case 23:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 1 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 << 1 ? o_mark : blank;
				break;
			case 26:
				board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1] = (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 ? x_mark : (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE & 1 ? o_mark : blank;
				break;
		}
		board[(this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 2] = closing;
		this->_player_O_status_and_general = (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) | (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 3;
		if ((this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) % 10 == 9) {
			board[this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK] = line_end;
			this->_player_O_status_and_general = (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) | (this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK) + 1;
		}
	}
	return board;
}

int8_t TicTacToeGame::TicTacToeGame::_negamax(u_int8_t depth, int8_t alpha, int8_t beta, int8_t player) {
	int8_t value = INT8_MIN;
	int8_t sub_returned;
	u_int8_t best_postion;
	int8_t game_check = this->check();
	if (depth == 0 || ((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE | (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE) == 0x1FF || game_check != -1) {
		if (game_check == -1)
			return 0;
		else if(game_check == 0)
			game_check = -1;
		else if (game_check == 1)
			game_check = 1;
		if (player == game_check)
			return 1;
		else
			return -1;
	}
    for (u_int8_t shift = 0; shift < 9; shift++) {
		if (!(((this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE | (this->_player_X_status_and_vmatch & this->_BOARD_FFIELD_BIT_MASK) >> this->_OTHER_FIELD_SIZE) & 1 << shift)) {
			this->place(player < 0 ? 0 : 1, 8 - shift);
			sub_returned = -this->_negamax(depth - 1, -beta, -alpha, -player);
			this->unplace(8 - shift);
			if (value < sub_returned) {
				value = sub_returned;
				best_postion = 8 - shift;
			}
			if (alpha < value)
				alpha = value;
			if (alpha >= beta)
				break;
		}
	}
	if (beta > 1)
		this->_player_O_status_and_general = (this->_player_O_status_and_general & this->_BOARD_FFIELD_BIT_MASK) | best_postion;
    return value;
}

int8_t TicTacToeGame::TicTacToeGame::get_next_optimal_place(u_int8_t player, u_int8_t depth_limit) {
	if (depth_limit > 9)
		return -1;
	switch (player) {
		case 0:
			this->_negamax(depth_limit, INT8_MIN+1, INT8_MAX, -1);
			break;
		case 1:
			this->_negamax(depth_limit, INT8_MIN+1, INT8_MAX, 1);
			break;
		default:
			return -1;
			break;
	}
	return this->_player_O_status_and_general & this->_OTHER_FIELD_BIT_MASK;
}