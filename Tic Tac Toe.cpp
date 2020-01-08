#include <iostream>
#include <stdlib.h>

int board[3][3];
int player_A;
int player_B;
bool turn;
int count;
int mode;
int move;
bool play;
int winner;
int oned_board;

int reset(bool all) {
	switch (all) {
	case true:
		for (int row = 0; row <= 2; row++) {
			for (int colume = 0; colume <= 2; colume++) {
				board[row][colume] = 0;
			}
		}
		player_A = 0;
		player_B = 0;
		turn = false;
		count = 0;
		mode = 0;
		move = 0;
		play = true;
		winner = 0;
		oned_board = 0;
		break;

	case false:
		for (int row = 0; row <= 2; row++) {
			for (int colume = 0; colume <= 2; colume++) {
				board[row][colume] = 0;
			}
		}
		turn = false;
		move = 0;
		play = true;
		winner = 0;
		oned_board = 0;
		break;

	}
	return 0;
}


int piece_bool_to_int(bool turn) {
	int out = 0;
	switch (turn) {
		case false:
		out = 1;
		break;
	case true:
		out = 2;
		break;

	default:
		out = 0;
		break;
	}
	return out;
}

char piece_int_to_char(int piece) {
	char out;
	switch (piece) {
		case 0:
		out = ' ';
		break;
	case 1:
		out = 'X';
		break;

	case 2:
		out = 'O';
		break;
	}
	return out;
}

int control(int locate) {

	switch (locate) {
	case 1:
		if(board[0][0] == 0){board[0][0] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 2:
		if(board[0][1] == 0){board[0][1] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 3:
		if(board[0][2] == 0){board[0][2] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 4:
		if(board[1][0] == 0){board[1][0] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 5:
		if(board[1][1] == 0){board[1][1] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 6:
		if(board[1][2] == 0){board[1][2] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 7:
		if(board[2][0] == 0){board[2][0] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 8:
		if(board[2][1] == 0){board[2][1] = piece_bool_to_int(turn);turn = !turn;}
		break;

	case 9:
		if(board[2][2] == 0){board[2][2] = piece_bool_to_int(turn);turn = !turn;}
		break;

	default:

		break;
	}
	return 0;	
}

int check_sum_val(int a, int b, int c) {
	int out;
	if (a == b && b == c && a == c) {
		switch(a){
			case 0:
			
			break;

			case 1:
			winner = 1;
			out = true;
			break;

			case 2:
			winner = 2;
			out = true;
			break;
		}
	}else{
		if(oned_board == 0){
			
			}
	}
	return out;
}

int check() {
	int check_sum[3];
	bool checkpass = false;
	//x aixs
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			check_sum[j] = board[i][j];
		}
		if(checkpass == false){
		checkpass = check_sum_val(check_sum[0], check_sum[1], check_sum[2]);
		}
	}

	//y aixs
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			check_sum[j] = board[j][i];
		}
		if(checkpass == false){
		checkpass = check_sum_val(check_sum[0], check_sum[1], check_sum[2]);
		}
	}

	//xy aixis
	for (int i = 0; i <= 2; i++) {
		check_sum[i] = board[i][i];
	}
	if(checkpass == false){
		checkpass = check_sum_val(check_sum[0], check_sum[1], check_sum[2]);
		}
	
	for (int i = 2; i >= 0; i--) {
		check_sum[i] = board[i][2-i];
	}
	if(checkpass == false){
		checkpass = check_sum_val(check_sum[0], check_sum[1], check_sum[2]);
		}

	//all
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			if(board[i][j] == 0){
				oned_board+=1;
			}
		}
	}
	return checkpass;
}

int display() {
	while(true){
	while(play){
	system("Cls");
	std::cout << "Play count: " << count << std::endl;
	std::cout << "Now piece: " << piece_int_to_char(piece_bool_to_int(turn)) << std::endl;
	std::cout << "Player1(X): " << player_A << std::endl;
	std::cout << "Player2(O): " << player_B << std::endl;
	std::cout << std::endl;
	char output = 'E';
	for (int row = 0; row <= 2; row++) {
		for (int colume = 0; colume <= 2; colume++) {
			output = piece_int_to_char(board[row][colume]);
			std::cout << "[" << output << "]";
		}
		std::cout << std::endl;
	}
	if(winner == 1){
		break;
	}else if(winner == 2){
		break;
	}




	std::cout << std::endl;
	std::cout << "Put a Number(1~9): " << std::endl;
	std::cin >> move;
	control(move);
	check();
}
switch(winner){
	case 1:
	std::cout << "Player1 Win!" << std::endl;
	break;

	case 2:
	std::cout << "Player1 Win!" << std::endl;
	break;

}
system("PAUSE");
	}
	return 0;
}

int main(int argc, char* argv[]) {
	system("Title Tic Tac Toe");
	std::cout << "Tic Tac Toe Game" << std::endl;
	std::cout << std::endl;
	std::cout << "1.Single Play With Computer" << std::endl;
	std::cout << "2.Offline Multi Play" << std::endl;
	std::cout << std::endl;
	std::cout << "Select Mode:";
	std::cin >> mode;
	switch (mode) {
	case 1:

		break;

	case 2:
	reset(false);
		display();
		break;

	default:

		break;
	}
	return 0;
}

