#ifndef __MCTS_H
#define __MCTS_H
#include "board.h"
#include "predictor.h"


const int MINI_BATCHSZ = 32;
struct mcts_node {
    Board board;
    mcts_node* parent;
    vector<mcts_node*> children;
    bool expanded;
    bool predicting;
    int pov;
    int N_sa;
    float W_sa;
    float Q_sa;
    float P_sa;
    float action_value;
    int current_step;
    mcts_node(const Board& bd, int _pov) :
        parent(NULL),
        expanded(false),
        predicting(false),
        N_sa(0),
        W_sa(0.0),
        Q_sa(0.0),
        P_sa(0.0),
        action_value(0.0),
        board(bd), 
        pov(_pov) {
        int _current_step = bd.get_white_moves().size() + bd.get_black_moves().size();
        current_step = _current_step;
    }
    float get_ucb() {
        return Q_sa + action_value;
    }
};

class MCTS {
public:
    MCTS(Predictor* _predictor, const Board& bd, int _pov, int _simulate_cnt);
    mcts_node* select();
    void expand(mcts_node* leaf);
    void back_up(mcts_node* leaf, float v);
    void update_action_value(mcts_node* cur);
    int prob_mv(const vector<float>& probs);
    int _prob_mv(const vector<float>& probs);
    void real_softmax(const Board& bd, vector<float>& probs);
    void dir_noise(vector<float>& probs, mcts_node* cur);
    void simulate();
    void move();
    float get_temperature();
private:
    Predictor* predictor;
    mcts_node* root;
    int simulate_cnt;
    float C_puct;
};

#endif
