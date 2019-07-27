#include "py_init.h"

PyObject* resnet = NULL;

void init() {
    PyInitialize();
    if (!Py_IsInitialized()) {
        return -1;
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../cnn')")
    import_array();
    PyObject *pModule, pDict, pClass, pInstance;
    pModule = PyImport_ImportModule("resnet")
    pDict = PyModule_GetDict(pModule);
    pClass = PyDict_GetItemString(pDict, "resnet39");
    resnet = PyObject_CallMethod(pClass, NULL);    
}
