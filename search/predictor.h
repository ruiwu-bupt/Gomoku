#ifndef __PREDICTOR_H
#define __PREDICTOR_H
// #include "Python.h"
#include "board.h"
// extern PyObject* resnet;

const int HISTORY_STEP = 5;

typedef int g_sample[HISTORY_STEP][BOARD_SZ][BOARD_SZ];
typedef 
class Predictor {
public:
    vector<vector<float>> test(vector<Board*>& bds);
    int train(vector<Board>& bds, vector<vector<float>>& labels);
};
#endif
