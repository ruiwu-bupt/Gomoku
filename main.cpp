#include "board.h"
#include "value.h"
#include "tree_search.h"
#include <ncurses.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <iostream>

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
	getch();
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
	bool turn = bd.get_black_moves() == bd.get_white_moves();
	Ab_search ai(0, 0);
	bool rst;
	while (rst = !bd.finish()) {
		string info = "你是白棋" + string(white);
		if (is_black)
			info = "你是黑棋" + string(black);
		const char* str = "请输入落子位置: ";
		mvaddstr(maxlines-2, 0, info.c_str());
		if (turn == is_black) {
			mvaddstr(maxlines-1, 0, str);
			echo();
			move(maxlines-1, 10);
			int x, y;
			std::cin >> x >> y;
			bd.move(mv(x,y), is_black);
		}
		else {
			mv move = ai.search(bd, !is_black);
			bd.move(move, !is_black);
		}
		turn = 1-turn;
		refresh();
	}
	if (rst == is_black)
		mvaddstr(maxlines-1, 0, "你赢了");
	else
		mvaddstr(maxlines-1, 0, "你输了");
}