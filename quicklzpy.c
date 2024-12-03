/**
    This is a python module to access to compression and decompression
    in the QuickLZ library. This module only provides a few entry points from
    Python:
    
    The main functions:
        qlz_compress()
        qlz_decompress()
        qlz_size_decompressed()
        qlz_size_compressed()
    
    The state object:
        QLZStateCompress
        

  **/
#include <Python.h>
#define IS_PY3K

#include "quicklz.h"
#if QLZ_STREAMING_BUFFER == 0
    #error Define QLZ_STREAMING_BUFFER to a non-zero value for this module
#endif

struct module_state {
    PyObject *error;
};

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))



static PyTypeObject QLZStateCompressType;
static PyTypeObject QLZStateDecompressType;

typedef struct {
    PyObject_HEAD
    qlz_state_compress* value;
} qlz_state_compress_Type;

typedef struct {
    PyObject_HEAD
    qlz_state_decompress* value;
} qlz_state_decompress_Type;

PyObject *
qlz_state_compress_NEW(PyTypeObject *self)
{
    qlz_state_compress_Type *object = (qlz_state_compress_Type *)self->tp_alloc(self, 0);
    if (object != NULL) {
      object->value = (qlz_state_compress *)malloc(sizeof(qlz_state_compress));
      memset(object->value, 0, sizeof(qlz_state_compress));
    }
    return (PyObject *)object;
}

void
qlz_state_compress_dealloc(PyObject *self)
{
    free(((qlz_state_compress_Type*)self)->value);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/* This is the Python constructor */
PyObject *
qlz_state_compress_new(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
    return qlz_state_compress_NEW(self);
}

PyObject *qlz_py_getattr(PyObject *self, char * attrname)
{
    PyErr_SetString(PyExc_AttributeError, attrname);
    return NULL;
}

PyObject *
qlz_state_decompress_NEW(PyTypeObject *self)
{
    qlz_state_decompress_Type *object = (qlz_state_decompress_Type *)self->tp_alloc(self, 0);
    if (object != NULL) {
      object->value = (qlz_state_decompress *)malloc(sizeof(qlz_state_decompress));
      memset(object->value, 0, sizeof(qlz_state_decompress));
    }
    return (PyObject *)object;
}

void
qlz_state_decompress_dealloc(PyObject *self)
{
    free(((qlz_state_decompress_Type*)self)->value);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

/* This is the Python constructor */
PyObject *
qlz_state_decompress_new(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
    return qlz_state_decompress_NEW(self);
}

PyObject *qlz_getattr(PyObject *self, char * attrname)
{
    PyErr_SetString(PyExc_AttributeError, attrname);
    return NULL;
}

int qlz_py_setattr(PyObject *self,  char *attrname, PyObject *value)
{
    PyErr_SetString(PyExc_AttributeError, attrname);
    return -1;
}

int qlz_compare(PyObject *self, PyObject *other)
{
    // 'is a' comparison
    return self == other;
}

int qlz_c_print(PyObject *self, FILE *fp, int flags)
{
    fprintf(fp, "QLZStateCompress(%ld)", (long)self);
    return 0;
}

PyObject *qlz_c_str(PyObject *self)
{
    char buf[100];
    sprintf(buf, "QLZStateCompress(%ld)", (long)self);
    return PyBytes_FromString(buf);
}

int qlz_d_print(PyObject *self, FILE *fp, int flags)
{
    fprintf(fp, "QLZStateDecompress(%ld)", (long)self);
    return 0;
}

PyObject *qlz_d_str(PyObject *self)
{
    char buf[100];
    sprintf(buf, "QLZStateDecompress(%ld)", (long)self);
    return PyBytes_FromString(buf);
}

long
qlz_hash(PyObject *self)
{
    return (long)self;
}

/**
  * The qlz_state_compress python object
  */
static PyTypeObject QLZStateCompressType = {
    PyVarObject_HEAD_INIT(NULL, 0)
  "QLZStateCompress",         /* char *tp_name; */
  sizeof(qlz_state_compress_Type),/* int tp_basicsize; */
  0,                          /* int tp_itemsize;       /* not used much */
  (destructor)qlz_state_compress_dealloc, /* destructor tp_dealloc; */
  0,                /* printfunc  tp_print;   */
  qlz_py_getattr,             /* getattrfunc  tp_getattr; /* __getattr__ */
  qlz_py_setattr,             /* setattrfunc  tp_setattr;  /* __setattr__ */
  0,                          /* cmpfunc  tp_compare;  /* __cmp__ */
  qlz_c_str,                  /* reprfunc  tp_repr;    /* __repr__ */
  0,                          /* PyNumberMethods *tp_as_number; */
  0,                          /* PySequenceMethods *tp_as_sequence; */
  0,                          /* PyMappingMethods *tp_as_mapping; */
  qlz_hash,                   /* hashfunc tp_hash;     /* __hash__ */
  0,                          /* ternaryfunc tp_call;  /* __call__ */
  qlz_c_str,                  /* reprfunc tp_str;      /* __str__ */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,   /* tp_flags */
    "quicklz objects",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,      /* tp_init */
    0,                         /* tp_alloc */
    qlz_state_compress_new,                 /* tp_new */
};

/**
  * The qlz_state_compress python object
  */
static PyTypeObject QLZStateDecompressType = {
    PyVarObject_HEAD_INIT(NULL, 0)
  "QLZStateDecompress",       /* char *tp_name; */
  sizeof(qlz_state_decompress_Type),/* int tp_basicsize; */
  0,                          /* int tp_itemsize;       /* not used much */
  (destructor)qlz_state_decompress_dealloc,/* destructor tp_dealloc; */
  0,                /* printfunc  tp_print;   */
  qlz_py_getattr,             /* getattrfunc  tp_getattr; /* __getattr__ */
  qlz_py_setattr,             /* setattrfunc  tp_setattr;  /* __setattr__ */
  0,                          /* cmpfunc  tp_compare;  /* __cmp__ */
  qlz_d_str,                  /* reprfunc  tp_repr;    /* __repr__ */
  0,                          /* PyNumberMethods *tp_as_number; */
  0,                          /* PySequenceMethods *tp_as_sequence; */
  0,                          /* PyMappingMethods *tp_as_mapping; */
  qlz_hash,                   /* hashfunc tp_hash;     /* __hash__ */
  0,                          /* ternaryfunc tp_call;  /* __call__ */
  qlz_d_str,                  /* reprfunc tp_str;      /* __str__ */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,   /* tp_flags */
    "quicklz objects",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,      /* tp_init */
    0,                         /* tp_alloc */
    qlz_state_decompress_new,                 /* tp_new */
};


PyObject *qlz_size_decompressed_py(PyObject *self, PyObject *args)
{ 
    PyObject *result = NULL;
    char* buffer;
    int buffer_length;

    if (PyArg_ParseTuple(args, "y#", &buffer, &buffer_length)) {
        result = Py_BuildValue("i", qlz_size_decompressed(buffer));
    } /* otherwise there is an error,
       * the exception already raised by PyArg_ParseTuple, and NULL is
       * returned.
       */
    return result;
}

PyObject *qlz_size_compressed_py(PyObject *self, PyObject *args)
{ 
    PyObject *result = NULL;
    char* buffer;
    int buffer_length;
    
    if (PyArg_ParseTuple(args, "y#", &buffer, &buffer_length)) {
        result = Py_BuildValue("i", qlz_size_compressed(buffer));
    } /* otherwise there is an error,
       * the exception already raised by PyArg_ParseTuple, and NULL is
       * returned.
       */
    return result;
}

PyObject *qlz_compress_py(PyObject *self, PyObject *args)
{ 
    PyObject *result = NULL;
    PyObject *state = NULL;
    char* buffer;
    char* compressed_buffer;
    int buffer_length;
    int size_compressed;

    if (PyArg_ParseTuple(args, "y#O!",
                         &buffer, &buffer_length,
                         &QLZStateCompressType, &state))
    {
        compressed_buffer = (char*)malloc(buffer_length+400);
        size_compressed = qlz_compress(buffer, compressed_buffer,
                                       buffer_length,
                                       ((qlz_state_compress_Type*)state)->value);
        result = Py_BuildValue("y#", compressed_buffer, size_compressed);
        free(compressed_buffer);
    } /* otherwise there is an error,
       * the exception already raised by PyArg_ParseTuple, and NULL is
       * returned.
       */
    return result;
}

PyObject *qlz_decompress_py(PyObject *self, PyObject *args)
{ 
    PyObject *result = NULL;
    PyObject *state = NULL;
    char* buffer;
    char* decompressed_buffer;
    int buffer_length;
    int size_decompressed;

    if (PyArg_ParseTuple(args, "y#O!",
                        &buffer, &buffer_length,
                        &QLZStateDecompressType, &state))
    {
        size_decompressed = qlz_size_decompressed(buffer);
        decompressed_buffer = (char*)malloc(size_decompressed);

        qlz_decompress(buffer, decompressed_buffer,
                       ((qlz_state_decompress_Type*)state)->value);
        
        result = Py_BuildValue("y#", decompressed_buffer, size_decompressed);
        free(decompressed_buffer);
    } /* otherwise there is an error,
       * the exception already raised by PyArg_ParseTuple, and NULL is
       * returned.
       */
    return result;
}


PyMethodDef QuicklzMethods[] = {
/*  {"QLZStateCompress", qlz_state_compress_new, METH_VARARGS,
    "An internal object for tracking streaming compression.\n"},

  {"QLZStateDecompress", qlz_state_decompress_new, METH_VARARGS,
    "An internal object for tracking streaming decompression.\n"},
*/
  {"qlz_size_decompressed", qlz_size_decompressed_py, METH_VARARGS,
    "qlz_size_decompressed(compressed_data)\n"
    "\n"
    "How many bytes would the uncompressed data in this chunk be?\n"},
  {"qlz_size_compressed", qlz_size_compressed_py, METH_VARARGS,
    "qlz_size_compressed(compressed_data)\n"
    "\n"
    "How many bytes is the compressed data in this chunk?\n"},

  {"qlz_compress", qlz_compress_py, METH_VARARGS,
    "qlz_compress(raw_data, state)\n"
    "Compress a chunk of data using QuickLZ.\n"
    "\n"
    "If the same state object is used to compress data sequentially,\n"
    "then chunks must also be decompressed using a state object in the same\n"
    "sequence.\n"
    "\n"
    "@param raw_data: string-like\n"
    "@param state: a QLZStateCompress object.\n"},

  {"qlz_decompress", qlz_decompress_py, METH_VARARGS,
    "qlz_decompress(compressed_chunk, state)\n"
    "Decompress a chunk of data using QuickLZ."
    "\n"
    "If the same state object is used to compress data sequentially,\n"
    "then chunks must also be decompressed using a state object in the same\n"
    "sequence.\n"
    "\n"
    "@param compressed_chunk: string-like\n"
    "@param state: a QLZStateDecompress object.\n"},

  {NULL, NULL},
};



static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "quicklz",
        "QuickLZ module",
        sizeof(struct module_state),
        QuicklzMethods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

PyObject *
PyInit_quicklz(void)
{

    PyObject *module = PyModule_Create(&moduledef);

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("quicklz.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

    Py_INCREF(&QLZStateCompressType);
    PyModule_AddObject(module, "QLZStateCompress", (PyObject *)&QLZStateCompressType);

    Py_INCREF(&QLZStateDecompressType);
    PyModule_AddObject(module, "QLZStateDecompress", (PyObject *)&QLZStateDecompressType);

    return module;
}
