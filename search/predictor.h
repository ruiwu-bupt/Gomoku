#ifndef __PREDICTOR_H
#define __PREDICTOR_H
// #include "Python.h"
#include "board.h"
// extern PyObject* resnet;

const int HISTORY_STEP = 5;

typedef vector<vector<vector<int>>> g_sample;
typedef vector<float> label;
class Predictor {
public:
    vector<vector<float>> test(vector<Board*>& bds);
    int train(vector<Board>& bds, vector<vector<float>>& labels);
};
#endif
