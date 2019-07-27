#include "predictor.h"
#include "py_init.h"
#include <iostream>
#include <numpy/arrayobject.h>
using namespace std;

extern PyObject* resnet;

Predictor::test(vector<Board*>& bds) {
    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pInstance;
    int n = bds.size();
    npy_intp Dims[4] = {n, 5, BOARD_SZ, BOARD_SZ};
    sample* test_sample = new sample[n];
    for (int sample_i = 0; sample_i < n; sample_i++) {
        auto bd = bds[sample_i];
        int pov = (bd.get_white_moves().size() + bd.get_black_moves().size()) % 2;
        for (int i = 0; i < BOARD_SZ; i++) {
            for (int j = 0; j < BOARD_SZ; j++) {
                for (int channel = 0; channel < 5; channel++) {
                    if (channel == 4) {
                        test_sample[sample_i][4][i][j] = pov;
                    }
                    else {
                        if (channel % 2 == 0) {

                        }
                        else {

                        }
                    }
                }
            }
        }
    }
}

Predictor::train(vector<Board*>& bds, vector<label>& labels) {

}
