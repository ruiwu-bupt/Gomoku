#include "board.h"
#include "value.h"
#include "tree_search.h"
#include <ncurses.h>
#include <locale.h>
#include <fstream>
#include <string>

void game(const char* opening, bool is_black);
int main(int argc, char* argv[]) {
	int maxlines, maxcols;
	setlocale(LC_ALL,""); 
	initscr();
	cbreak();
	noecho();
	clear();
	bool is_black;
	is_black = argv[2][0] == 'y' ? true : false;
	game(argv[1], is_black);
	refresh();
	endwin();
}

void game(const char* opening_file, bool is_black) {
	int maxlines = LINES - 1;
	int maxcols = COLS - 1;
	int N;
	vector<vector<int>> opening;
	fstream f;
	f.open(opening_file, ios::in);
	string x, y, color;
	f >> x;
	N = stoi(x);
	while (f >> x >> y >> color) {
		opening.push_back(vector<int> {stoi(x), stoi(y), stoi(color)});
	}
	Board bd(N, opening);
	bd.draw();
	const char* str = "请输入落子位置: ";
	mvaddstr(maxlines-1, 0, str);
}