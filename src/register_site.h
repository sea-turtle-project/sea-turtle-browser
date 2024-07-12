#define PY_SSIZE_T_CLEAN
#include <python3.12/Python.h>
#include <string>

int register_site(const char* domain, const char* tld, const char* github) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    Py_Initialize();
    PyRun_SimpleString("import sys\nimport os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");

    pName = PyUnicode_DecodeFSDefault("src.database.database");

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "register_site");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);

            pValue = PyUnicode_FromString(domain);
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyUnicode_FromString(tld);
            PyTuple_SetItem(pArgs, 1, pValue);

            pValue = PyUnicode_FromString(github);
            PyTuple_SetItem(pArgs, 2, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
