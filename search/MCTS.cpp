#include "MCTS.h"
#include <cmath>

MCTS::MCTS(Predictor* _predictor, const Board& bd, int _pov, int _simulate_cnt) :
    predictor(_predictor),
    simulate_cnt(_simulate_cnt){
    root = new mcts_node(bd, _pov);
    C_puct = 0.001;
}

mcts_node* MCTS::select() {
    auto cur = root;
    while (cur->expanded) {
        int max_index = -1, action_v = -1;
        for (int i = 0; i < cur->children.size(); i++) {
            if (max_index == -1 || cur->action_value > action_v) {
                max_index = i;
                action_v = cur->action_value;
            }
        }
        cur = cur->children[i];
    }
    return cur;
}

void MCTS::expand(mcst_node* leaf) {

}

void MCTS::back_up(mcts_node* leaf, float v) {
    int leaf_pov = leaf->pov;
    while (leaf) {
        leaf->N_sa++;
        leaf->W_sa += v;
        leaf->Q_sa = leaf->W_sa/leaf->N_sa;
        update_action_value(leaf);
    }
}

void MCTS::update_action_value(mcts_node* cur) {
    if (!cur->parent)
        return;
    cur->action_value = C_puct * cur->P_sa *
        sqrt(cur->parent->N_sa) / (1 + cur->N_sa);
}

void MCTS::simulate() {
    int finish_cnt = 0;
    while (finish_cnt < simulate_cnt) {
        bool batch_ready = false;
        for (int i = 0; i < MINI_BATCHSZ && !batch_ready; i++) {
            auto target_leaf = select();
            if (target_leaf->predicting) {
                batch_ready = true;
                break;
            }
            target_leaf->predicting = true;

        }
    }
}
