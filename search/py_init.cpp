#include "py_init.h"

PyObject* resnet = NULL;

int init() {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        return -1;
    }
    // PySys_SetArgv(1, argv);
    PyRun_SimpleString("print('hello world')");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../cnn')");
    import_array();
    PyRun_SimpleString("print('hello world2')");
    PyObject *pModule, *pDict, *pClass, pInstance;
    pModule = PyImport_ImportModule("resnet");
    PyRun_SimpleString("print('hello world3')");
    pDict = PyModule_GetDict(pModule);
    PyRun_SimpleString("print('hello world4')");
    pClass = PyDict_GetItemString(pDict, "resnet39");
    
    return 0;
}
