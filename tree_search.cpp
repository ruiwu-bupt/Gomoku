#include "tree_search.h"
#include "value.h"
#include <algorithm>


mv Ab_search::search(Board& board) const {

}

pair<int, mv> Ab_search::__search(Board& board, mv move, int depth, 
	int alpha, int beta, bool maxmizingPlayer) const {
	board.get_board()[move.first][move.second] = maxmizingPlayer;
	int v = v_func(Board);
	if (!depth || v == INT_MAX || v == INT_MIN)
		return v;
	vector<mv> children = generate_children(Board);
	if (maxmizingPlayer) {
		v = INT_MIN;
		
	}
	else {
		v = INT_MAX;
	}
	board.get_board()[move.first][move.second] = 0;
	return pair<int, mv> ();
}

// max distance 2 for this child piece and any other piece on board
// or use v_func
vector<mv> Ab_search::generate_children(const Board& board) const {
	vector<vector<int>> rst;
	auto bd = board.get_board();
	int N = bd.size();
	if (!board.get_black_moves().size())
		rst.push_back(mv(N/2, N/2));
	else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (bd[i][j])
					continue;
				bool valid = false;
				for (int ii = max(0, ii-2); ii < min(N, ii+2); ii++) {
					for (int jj = max(0, jj-2); jj < min(N, jj+2); jj++) {
						if (!(ii == i && jj == j)) {
							valid = true;
							break;
						}
					}
				}
				if (valid)
					rst.push_back(mv(i, j));
			}
		}
	}
	return rst;
}