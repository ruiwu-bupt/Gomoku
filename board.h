#ifndef __BOARD_H
#define __BOARD_H

#include <vector>
#include <ncurses.h>
#include <utility>
using namespace std;
typedef pair<int, int> mv;

const char* black = "＠";
const char* white = "＃";
const char* blank = "十";
// -1 for white, 0 for null, 1 for black
class Board{
public:
	Board(int N);
	Board(int N, const vector<vector<int>>& opening);
	void draw();
	bool black_move(const mv& move);
	bool white_move(const mv& move);
	bool move_valid(const mv& move);
	const vector<vector<int>>& get_board() { return __board;}
	const vector<mv>& get_white_moves() { return __black_moves;}
	const vector<mv>& get_black_moves() { return __white_moves;}
	int finish();
private:
	int __N;
	vector<vector<int>> __board;
	vector<mv> __black_moves;
	vector<mv> __white_moves;
};

#endif