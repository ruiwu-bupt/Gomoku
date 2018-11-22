#ifndef __TREE_SEARCH_H
#define __TREE_SEARCH_H

#include "board.h"
#include "value.h"
#include <utility>
#include <climits>

// min-max with alpha-beta cut off
class Ab_search{
public:
	int time_limit;
	int thread_num;
	Ab_search(int tl, int tn) : time_limit(tl), thread_num(tn){}
	mv search(Board& board, bool maxmizingPlayer) const;
	vector<mv> generate_children(Board& board) const;
private:
	pair<int, mv> __search(Board& board, int depth, int alpha, int beta, bool maxmizingPlayer) const;
};

#endif