#include "board.h"
#include <assert.h>
#include <string>

const char* black = "＠";
const char* white = "＃";
const char* blank = "十";

Board::Board(int N) {
	__N = N;
	__board = vector<vector<int>> (N, vector<int> (N, 0));
}

Board::Board(int N, const vector<vector<int>>& opening) {
	new(this)Board(N);
	for (int i = 0; i < opening.size(); i++) {
		__board[opening[i][0]][opening[i][1]] = opening[i][2];
		mv move(opening[i][0], opening[i][1]);
		if (opening[i][2] == -1)
			__white_moves.push_back(move);
		if (opening[i][2] == 1)
			__black_moves.push_back(move);
	}
}

bool Board::move_valid(const mv& move) const {
	int x = move.first;
	int y = move.second;
	return !(x < 0 || x >= __N || y < 0 || y >= __N || __board[x][y]);
}

bool Board::move(const mv& move, bool is_black) {
	int x = move.first;
	int y = move.second;
	if (!move_valid(move))
		return false;
	__board[x][y] = is_black ? 1 : -1;
	if (is_black)
		__black_moves.push_back(mv(x, y));
	else
		__white_moves.push_back(mv(x, y));
	return true;
}

int Board::finish() const {
	for (int i = 0; i < __N; i++) {
		for (int j = 0; j < __N; j++) {
			if (!__board[i][j])
				continue;
			int k = 1;
			if (j == 0 || __board[i][j] != __board[i][j-1]) {
				while ((j+k < __N) && __board[i][j+k] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
			k = 1;
			if (i == 0 || __board[i][j] != __board[i-1][j]) {
				while (i+k < __N && __board[i+k][j] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
			k = 1;
			if ((i == 0 || j == 0) || __board[i][j] != __board[i-1][j-1]) {
				while ((i+k < __N && j+k < __N) && __board[i+k][j+k] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
			k = 1;
			if ((i == 0 || j == __N-1) || __board[i][j] != __board[i-1][j+1]) {
				while ((i+k < __N && j-k >= 0) && __board[i+k][j-k] == __board[i][j])
					k++;
				if (k >= 5)
					return __board[i][j];
			}
		}
	}
	return 0;
}

void Board::draw() const {
	for (int i = 0; i < __board.size(); i++) {
		mvaddstr(i+1, 0, to_string(i).c_str());
	}
	for (int j = 0; j < __board[0].size(); j++) {
		mvaddstr(0, (j+1)*2, to_string(j).c_str());
	}
	int x_padding = 1, y_padding = 2;
	for (int i = 0; i < __board.size(); i++) {
		for (int j = 0; j < __board[i].size(); j++) {
			switch(__board[i][j]) {
				case 0:
					mvaddstr(i+x_padding, j+y_padding, blank);
					break;
				case -1:
					mvaddstr(i+x_padding, j+y_padding, white);
					break;
				case 1:
					mvaddstr(i+x_padding, j+y_padding, black);
					break;
				default:
					assert(false);
			}
		}
	}
}