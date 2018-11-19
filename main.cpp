#include "board.h"
#include "value.h"
#include "tree_search.h"

int main() {
	int maxlines, maxcols;
	initscr();
	cbreak();
	noecho();
	clear();
	maxlines = LINES - 1;
	maxcols = COLS - 1;
	char* str = "input your pick with row index and colomn index: ";
	mvaddstr(maxlines, 0, str);
	
}