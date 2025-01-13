#include <Python.h>
#include "quicklz.h"  // 引入 QuickLZ 的头文件

// 压缩函数包装
static PyObject* py_quicklz_compress(PyObject* self, PyObject* args) {
    const char* input;
    int input_size;

    // 解析输入参数
    if (!PyArg_ParseTuple(args, "s#", &input, &input_size))
        return NULL;

    char* compressed = (char*)malloc(input_size + 400);
    int compressed_size = qlz_compress(input, compressed, state);

    PyObject* result = Py_BuildValue("y#", compressed, compressed_size);
    free(compressed);
    return result;
}

// 解压缩函数包装
static PyObject* py_quicklz_decompress(PyObject* self, PyObject* args) {
    const char* input;
    int input_size;

    if (!PyArg_ParseTuple(args, "s#", &input, &input_size))
        return NULL;

    char* decompressed = (char*)malloc(4096+400);  // 假设最大解压后大小
    int decompressed_size = qlz_decompress(input, decompressed, state);

    PyObject* result = Py_BuildValue("y#", decompressed, decompressed_size);
    free(decompressed);
    return result;
}

// 方法定义
static PyMethodDef QuicklzMethods[] = {
    {"compress", py_quicklz_compress, METH_VARARGS, "Compress data using QuickLZ."},
    {"decompress", py_quicklz_decompress, METH_VARARGS, "Decompress data using QuickLZ."},
    {NULL, NULL, 0, NULL}
};

// 模块定义
static struct PyModuleDef quicklzmodule = {
    PyModuleDef_HEAD_INIT,
    "quicklz",
    NULL,
    -1,
    QuicklzMethods
};

PyMODINIT_FUNC PyInit_quicklz(void) {
    return PyModule_Create(&quicklzmodule);
}
