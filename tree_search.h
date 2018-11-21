#ifndef __TREE_SEARCH_H
#define __TREE_SEARCH_H

#include "board.h"
#include "value.h"
#include <utility>
#include <limits>

// min-max with alpha-beta cut off
class Ab_search{
public:
	int time_limit;
	int thread_num;
	ab_search(int tl, int tn) : time_limit(tl), thread_num(tn){}
	vector<int> search(Board& board) const;
	vector<mv> generate_children(const Board& board) const;
private:
	pair<int, mv> __search(Board& board, mv move, int depth, int alpha, int beta, bool maxmizingPlayer) const;
}

#endif