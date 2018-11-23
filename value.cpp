#include "value.h"

static int v_matrix[][6] = {
	{10, 40, 300, 500, 1000, 10000},
	{20, 50, 800, 8000, 10000, 10000}
};

int v_func(Board& bd, int next_player) {
	int v = 0;
	v = bd.finish();
	if (v) {
		return v > 0 ? INT_MAX : INT_MIN;
	}
	v = 0;
	auto& board = bd.get_board();
	int m = board.size();
	int n = board[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!board[i][j])
				continue;
			int k = 1, cnt = 0;
			if (j == 0 || board[i][j] != board[i][j-1]) {
				while (j+k < n && board[i][j+k] == board[i][j])
					k++;
				if (j != 0 && !board[i][j-1])
					cnt++;
				if (j+k != n && !board[i][j+k])
					cnt++;
				v += v_assist(k, cnt, board[i][j], next_player);
				k = 1, cnt = 0;
			}
			if (i == 0 || board[i][j] != board[i-1][j]) {
				while (i+k < m && board[i+k][j] == board[i][j])
					k++;
				if (i != 0 && !board[i-1][j])
					cnt++;
				if (i+k != m && !board[i+k][j])
					cnt++;
				v += v_assist(k, cnt, board[i][j], next_player);
				k = 1, cnt = 0;
				
			}
			if ((i == 0 || j == 0) || board[i][j] != board[i-1][j-1]) {
				while ((i+k < m && j+k < n) && board[i+k][j+k] == board[i][j])
					k++; 
				if ((j != 0 && i!= 0) && !board[i-1][j-1])
					cnt++;
				if ((i+k != m && j+k != n) && !board[i+k][j+k])
					cnt++;
				v += v_assist(k, cnt, board[i][j], next_player);
				k = 1, cnt = 0;
			}
			if ((i == 0 || j == n-1) || board[i][j] != board[i-1][j+1]) {
				while ((i+k < m && j-k >= 0) && board[i+k][j-k] == board[i][j])
					k++; 
				if ((j != n-1 && i!= 0) && !board[i-1][j+1])
					cnt++;
				if ((i+k != m && j-k != -1) && !board[i+k][j-k])
					cnt++;
				v += v_assist(k, cnt, board[i][j], next_player);
				k = 1, cnt = 0;
			}
		}
	}
	return v;
}

int v_assist(int lian, int huo, int current_pos_player, int next_player) {
	int large = 10000;
	if (huo == 0)
		return 0;
	return v_matrix[current_pos_player==next_player][(lian-2)*2+(huo-1)]*current_pos_player;
}
