#include "predictor.h"
// #include "py_init.h"
#include <iostream>
// #include <numpy/arrayobject.h>
using namespace std;

// extern PyObject* resnet;
int Predictor::train(vector<Board>& bds, vector<vector<float>>& labels) {
    return 0;
}

vector<vector<float>> Predictor::test(vector<Board*>& bds) {
    int n = bds.size();
    auto test_sample = vector<g_sample> (n);
    for (int sample_i = 0; sample_i < n; sample_i++) {
        auto bd = bds[sample_i];
        int pov = (bd->get_white_moves().size() + bd->get_black_moves().size()) % 2;
        for (int i = 0; i < BOARD_SZ; i++) {
            for (int j = 0; j < BOARD_SZ; j++) {
                for (int channel = 0; channel < HISTORY_STEP; channel++) {
                    if (channel == HISTORY_STEP - 1) {
                        test_sample[sample_i][HISTORY_STEP-1][i][j] = pov;
                    }
                    else {
                        if (channel % 2 == 0) {
                            test_sample[sample_i][channel][i][j] = pov;
                        }
                        else {
                            test_sample[sample_i][channel][i][j] = 1 - pov;
                        }
                    }
                }
            }
        }
    }
    vector<vector<float>> rst(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < BOARD_SZ * BOARD_SZ; j++) {
            rst[i][j] = 1 / (BOARD_SZ * BOARD_SZ);
        }
        rst[i][BOARD_SZ * BOARD_SZ] = 0.5;
    }
    return rst;
}

