#ifndef __PREDICTOR_H
#define __PREDICTOR_H
#include "Python.h"
#include "board.h"
extern PyObject* resnet;

const int HISTORY_STEP = 5;

typedef int sample[HSITORY_STEP][BOARD_SZ][BOARD_SZ];
typedef float label[BOARD_SZ*BOARD_SZ+1];

class Predictor {
public:
    void test(vector<Board*>& bds);
    void train(vector<Board*>& bds, vector<label>& labels);
}
#endif
