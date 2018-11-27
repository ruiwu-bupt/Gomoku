#include "tree_search.h"
#include "value.h"
#include <algorithm>

// maxmizingPlayer indicate bot AI is black(true) or white(false)
mv Ab_search::search(Board& board, bool maxmizingPlayer) {
	return __search(board, 1, INT_MIN, INT_MAX, maxmizingPlayer).second;
}

pair<int, mv> Ab_search::__search(Board& board, int depth, 
	int alpha, int beta, bool maxmizingPlayer) {
	node_num++;
	mv this_move;
	int v = v_func(board, maxmizingPlayer ? 1 : -1);
	if (!depth || v == INT_MAX || v == INT_MIN)
		return pair<int, mv> (v, pair<int, int> ());
	vector<mv> children = generate_children(board);
	auto& bd = board.get_board();
	if (maxmizingPlayer) {
		v = INT_MIN;
		for (int i = 0; i < children.size(); i++) {
			bd[children[i].first][children[i].second] = 1;
			auto tmp = __search(board, depth-1, alpha, beta, false);
			bd[children[i].first][children[i].second] = 0;
			if (tmp.first > v) {
				v = tmp.first;
				this_move = children[i];
			}
			alpha = max(alpha, v);
			if (beta <= alpha)
				break;
		}
	}
	else {
		v = INT_MAX;
		for (int i = 0; i < children.size(); i++) {
			bd[children[i].first][children[i].second] = -1;
			auto tmp = __search(board, depth-1, alpha, beta, true);
			bd[children[i].first][children[i].second] = 0;
			if (tmp.first < v) {
				v = tmp.first;
				this_move = children[i];
			}
			beta = min(beta, v);
			if (beta <= alpha)
				break;
		}
	}
	return pair<int, mv> (v, this_move);
}

// max distance 2 for this child piece and any other piece on board
// or use v_func
vector<mv> Ab_search::generate_children(Board& board) const {
	vector<mv> rst;
	auto& bd = board.get_board();
	int N = bd.size();
	int l = 1;
	if (!board.get_black_moves().size())
		rst.push_back(mv(N/2, N/2));
	else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (bd[i][j])
					continue;
				bool valid = false;
				for (int ii = max(0, i-l); ii < min(N, i+l); ii++) {
					for (int jj = max(0, j-l); jj < min(N, j+l); jj++) {
						if (bd[ii][jj]) {
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