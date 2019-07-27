#ifndef __MCTS_H
#define __MCTS_H
#include "board.h"


class Predictor;

const int MIN_BATCHSZ = 32;
struct mcts_node {
    Board board;
    Board* parent;
    vector<mcts_node*> children;
    bool expanded;
    bool predicting;
    int pov;
    int N_sa;
    float W_sa;
    float Q_sa;
    float P_sa;
    float action_value;
    node(const Board& bd, int _pov) :
        parent(NULL),
        expanded(false),
        predicting(false),
        N_sa(0),
        W_sa(0.0),
        Q_sa(0.0),
        P_sa(1.0),
        action_value(0.0) {
        board = bd;
        pov = _pov;
    }
};

class MCTS {
public:
    MCTS(Predictor* _predictor, const Board& bd, int _pov, int _simulate_cnt);
    mcts_node* select();
    void expand();
    void back_up(mcts_node* leaf);
    void update_action_value(mcts_node* cur);
private:
    Predictor* predictor;
    mcts_node* root;
    int simulate_cnt;
    float C_puct;
}

#endif
