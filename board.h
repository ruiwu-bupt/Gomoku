#ifndef __BOARD_H
#define __BOARD_H

#include <vector>

// -1 for white, 0 for null, 1 for black
class Board{
public:
	Board(int N);
	Board(int N, const vector<vector<int>>& opening);
	void draw();
	inline bool black_move(int x, int y);
	inline bool white_move(int x, int y);
	inline bool move_valid(int x, int y);
	inline const vector<vector<int>>& get_board();
	inline const vector<vector<int>>& get_white_moves();
	inline const vector<vector<int>>& get_black_moves();
	int finish();
private:
	int __N;
	vector<vector<int>> __board;
	vector<vector<int>> __black_moves;
	vector<vector<int>> __white_moves;
}

#endif