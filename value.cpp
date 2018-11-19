#include "value.h"

int v_func(const Board& bd, int next_player) {
	int v = 0;
	auto& board = bd.get_board();
	for (int i = 0; i < __board.size(); i++) {
		for (int j = 0; j < __board[0].size(); j++) {
			if (!__board[i][j])
				continue;
			int k = 1, cnt = 0;
			if (j == 0 || __board[i][j] != board[i][j-1]) {
				while (j+k < board[0].size() && __board[i][j+k] == __board[i][j])
					k++;
				if (j != 0 && !__board[i][j-1])
					cnt++;
				if (j+k != board[0].size() && !__board[i][j+k])
					cnt++;
				v += v_assist(k, cnt, __board[i][j], next_player);
				k = 1, cnt = 0;
			}
			if (i == 0 || __board[i][j] != board[i-1][j]) {
				while (i+k < board.size() && __board[i+k][j] == __board[i][j])
					k++;
				if (i != 0 && !__board[i-1][j])
					cnt++;
				if (i+k != board.size() && !__board[i+k][j])
					cnt++;
				v += v_assist(k, cnt, __board[i][j], next_player);
				k = 1, cnt = 0;
				
			}
			if ((i == 0 && j == 0) || __board[i][j] != board[i-1][j-1]) {
				while ((i+k < board.size() && j+k < board[0].size()) && __board[i+k][j+k] == __board[i][j])
					k++; 
				if ((j != 0 && i!= 0) && !__board[i-1][j-1])
					cnt++;
				if ((i+k != board.size() && j+k != board[0].size()) && !__board[i+k][j+k])
					cnt++;
				v += v_assist(k, cnt, __board[i][j], next_player);
			}
		}
	}
	return v;
}

inline int v_assist(int lian, int huo, int current_pos_player, int next_player) {
	if (huo == 0)
		return 0;
	else if (huo == 1) {
		switch(lian) {
			case 2 : return 1<<((current_pos_player==next_player))*current_pos_player;
			case 3 : return 1<<(2*(current_pos_player==next_player))*current_pos_player;
			case 4 : return 1<<(4*(current_pos_player==next_player))*current_pos_player;
		}
	}
	else {
		case 2 : return 1<<(3*(current_pos_player==next_player)+1)*current_pos_player;
		case 3 : return 1<<(6*(current_pos_player==next_player)+1)*current_pos_player;
		case 4 : return 1<<(12*(current_pos_player==next_player)+1)*current_pos_player;
	}
}
