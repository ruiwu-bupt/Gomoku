#include "board.h"

Board::board(int N) {
	__N = N;
	__board = vector<vector<int> > (N, vector<int> (N, 0));
}

Board::board(int N, const vector<vector<int>>& opening) {
	board(N);
	for (int i = 0; i < opening.size(); i++) {
		__board[opening[i][0]][opening[i][1]] = opening[i][2];
		vector<int> move{opening[i][0], opening[i][1]};
		if (opening[i][2] == -1)
			__white_moves.push_back(move);
		if (opening[i][2] == 1)
			__black_moves.push_back(move);
	}
}

bool Board::move_valid(int x, int y) const {
	return !(x < 0 || x >= __N || y < 0 || y >= __N || __board[x][y]);
}

bool Board::black_move(int x, int y) {
	if (!move_valid(x, y))
		return false;
	__board[x][y] = 1;
	__black_moves.push_back(vector<int> {x, y});
	return true;
}

bool Board::white_move(int x, int y) {
	if (!move_valid(x, y))
		return false;
	__board[x][y] = -1;
	__white_moves.push_back(vector<int> {x, y});
	return true;
}
inline const vector<vector<int>>& Board::get_board() const {
	return __board;
}

inline const vector<vector<int>>& Board::get_black_moves() const {
	return __black_moves;
}

inline const vector<vector<int>>& Board::get_white_moves() const {
	return __white_moves;
}

int Board::finish() const {
	for (int i = 0; i < __board.size(); i++) {
		for (int j = 0; j < __board[0].size(); j++) {
			if (!__board[i][j])
				continue;
			int k = 1;
			if (j == 0 || __board[i][j] != board[i][j-1]) {
				while (j+k < board[0].size() && __board[i][j+k] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
			k = 1;
			if (i == 0 || __board[i][j] != board[i-1][j]) {
				while (i+k < board.size() && __board[i+k][j] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
			k = 1;
			if ((i == 0 && j == 0) || __board[i][j] != board[i-1][j-1]) {
				while ((i+k < board.size() && j+k < board[0].size()) && __board[i+k][j+k] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
		}
	}
	return 0;
}