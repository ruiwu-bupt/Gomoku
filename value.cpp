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

				k = 1, cnt = 0;
			}
			if (i == 0 || __board[i][j] != board[i-1][j]) {
				while (i+k < board.size() && __board[i+k][j] == __board[i][j])
					k++;
				if (i != 0 && !__board[i-1][j])
					cnt++;
				if (i+k != board.size() && !__board[i+k][j])
					cnt++;
				k = 1, cnt = 0;
				
			}
			if ((i == 0 && j == 0) || __board[i][j] != board[i-1][j-1]) {
				while ((i+k < board.size() && j+k < board[0].size()) && __board[i+k][j+k] == __board[i][j])
					k++;
				if ((j != 0 && i!= 0) && !__board[i-1][j-1])
					cnt++;
				if ((i+k != board.size() && j+k != board[0].size()) && !__board[i+k][j+k])
					cnt++;
			}
		}
	}
	return v;
}

int v_assist(int lian, int huo, int next_player) {
	
}
