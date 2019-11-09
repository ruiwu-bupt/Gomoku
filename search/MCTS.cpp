#include "MCTS.h"
#include "board.h"
#include <cmath>
#include <random>
#include <stdlib.h>
#include <vector>

MCTS::MCTS(Predictor* _predictor, const Board& bd, int _pov, int _simulate_cnt, int _current_step) :
    predictor(_predictor),
    simulate_cnt(_simulate_cnt) {
    root = new mcts_node(bd, _pov);
    C_puct = 0.001;
}

mcts_node* MCTS::select() {
    auto cur = root;
    while (cur->expanded) {
        int max_index = -1;
        float ucb = 0.0;
        for (int i = 0; i < cur->children.size(); i++) {
            if (max_index == -1 || cur->get_ucb() > ucb) {
                max_index = i;
                ucb = cur->get_ucb;
            }
        }
        cur = cur->children[max_index];
    }
    return cur;
}

// expand 需要提交神经网络进行评估，代价较大
// 尽量提高并行性，所以一次提交多个叶子节点到神经网络，然后按顺序一个一个执行back_up
void MCTS::expand(mcts_node* leaf) {
    // predictor->test();
}

void MCTS::back_up(mcts_node* leaf, float v) {
    int leaf_pov = leaf->pov;
    v = -v;
    while (leaf) {
        leaf->N_sa++;
        leaf->W_sa += -v;
        leaf->Q_sa = leaf->W_sa/leaf->N_sa;
        update_action_value(leaf);
        leaf = leaf->parent;
    }
}


void MCTS::update_action_value(mcts_node* cur) {
    if (!cur->parent)
        return;
    cur->action_value = C_puct * cur->P_sa *
        sqrt(cur->parent->N_sa) / (1 + cur->N_sa);
}

void MCTS::simulate() {
    // 这里会不会引发bug
    int accomplished_cnt = root->N_sa;
    while (accomplished_cnt < simulate_cnt) {
        // 等待进行evalute的棋盘状态队列
        vector<mcts_node*> mcts_node_queue;
        vector<Board*> board_queue;
        bool batch_ready = false;
        while (mcts_node_queue.size() < MINI_BATCHSZ && !batch_ready) {
            // 初始可选择状态很少的时候要进行什么trick 操作
            auto target_leaf = select();
            if (target_leaf->predicting) {
                // virtual loss 还是直接提交mini batch
                batch_ready = true;
                break;
            }
            target_leaf->predicting = true;
            // TODO 考虑根据游戏规则直接可以结束的情况
            mcts_node_queue.push_back(target_leaf);
            board_queue.push_back(&target_leaf->board);
        }
        vector<label> rst = predictor->test(board_queue);
        for (int i = 0; i < rst.size(); i++) {
            mcts_node* parent = mcts_node_queue[i];
            // probs只是神经网络评估出来的概率
            // 需要增加温度系数和狄利克雷噪声的是根节点走下一步的操作
            vector<float> probs;
            float v = rst[i][BOARD_SZ * BOARD_SZ];
            for (int j = 0; j < BOARD_SZ * BOARD_SZ; j++) {
                probs.push_back(rst[i][j]);
            }
            real_softmax(parent->board, probs);
            for (int j = 0 ; j < BOARD_SZ * BOARD_SZ; j++) {
                mcts_node* child =  new mcts_node(parent->board, 1 - parent->pov);
                child_parent = parent;
                child->P_sa = probs[j];
                parent->children.push_back(child);
                child->board.move(mv (j / BOARD_SZ, j % BOARD_SZ), parent->pov);
            }
            back_up(parent, v);
        }
    }
}

int MCTS::_prob_mv(const vector<float>& probs) {
    // TODO: rand algorithm not appropriate
    int len = probs.size();
    float rand_float = (float)rand() / (float)RAND_MAX;
    float sum = 0;
    int i = 0;
    for (; i <= len; i++) {
        if (rand_float >= sum && rand_float < sum + probs[i]) {
            return i;
        }
        else {
            sum += probs[i];
        }
    }
    return i;
}

int MCTS::prob_mv(const vector<float>& probs) {
    int rst = _prob_mv(probs);
    // TODO: 直接判断等于0还是无穷小值
    return probs[rst] == 0.0 ? rst : prob_mv(probs);
}

// 抹去棋盘上非法的落子位置，使用softmax进行平滑
void MCTS::real_softmax(const Board& bd, vector<float>& probs) {
    float sum = 0;
    for (int i = 0; i < probs.size(); i++) {
        if (bd.move_valid(mv (i / BOARD_SZ, i % BOARD_SZ ))) {
            sum += probs[i];
        }
        else {
            probs[i] = 0;
        }
    }
    for (int i = 0; i < probs.size(); i++) {
        probs[i] /= sum;
    }
}

void MCTS::dir_noise(vector<float>& probs, mcts_node* cur) {
    return probs;
}

// 在根节点进行 1/t 平滑
vector<float> MCTS::get_root_move_probs() {
    float temperature = get_temperature();
    float sum = 0;
    for (int i = 0; i < root->children.size(); i++) {
        sum += pow(root->children[i]->N_sa, 1 / temperature);
    }
    vector<float> probs;
    for (int i = 0; i < root->children.size(); i++) {
        float prob = pow(root->children[i]->N_sa, 1 / temperature) / sum;
        probs.push_back(prob);
    }
    return probs;
}

float MCTS::get_temperature() {
    return 1 / (root->current_step / 10);
}

void MCTS::move() {
    vector<float> probs = get_root_move_probs();
    real_softmax(root->board, probs);
    int idx = prob_mv(probs);
    mcts_node* new_root = root->children[idx];
    delete_except(root, choice);
    root = new_root;
}

void MCTS::delete_except(mcts_node* cur, mcts_node* choice) {
    if (cur == choice) return;
    if (!root->children.size()) delete cur;
    for (int i = 0; i < cur->children.size(); i++) {
        delete_except(cur->children[i], choice);
    }
}
// TODO
// 在根局面进行走子时，前n步使用softmax概率扩大搜索范围
// 后面正比于N^(1/t)，t是温度，小于1，然后增加狄利克雷噪声，帮助度过局部最优

