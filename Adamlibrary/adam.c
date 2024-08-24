#include <Python.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// calloc işlevini Python'a getirme
static PyObject* py_calloc(PyObject* self, PyObject* args) {
    Py_ssize_t count, size;
    if (!PyArg_ParseTuple(args, "nn", &count, &size)) {
        return NULL;
    }
    void* ptr = calloc(count, size);
    if (ptr == NULL) {
        PyErr_NoMemory();
        return NULL;
    }
    PyObject* result = PyLong_FromVoidPtr(ptr);
    return result;
}

// realloc işlevini Python'a getirme
static PyObject* py_realloc(PyObject* self, PyObject* args) {
    PyObject* obj;
    Py_ssize_t new_size;
    if (!PyArg_ParseTuple(args, "On", &obj, &new_size)) {
        return NULL;
    }
    void* ptr = PyLong_AsVoidPtr(obj);
    ptr = realloc(ptr, new_size);
    if (ptr == NULL) {
        PyErr_NoMemory();
        return NULL;
    }
    PyObject* result = PyLong_FromVoidPtr(ptr);
    return result;
}

// bsearch işlevini Python'a getirme
static int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

static PyObject* py_bsearch(PyObject* self, PyObject* args) {
    PyObject* key_obj;
    PyObject* base_list;
    Py_ssize_t nmemb, size;
    if (!PyArg_ParseTuple(args, "OOnn", &key_obj, &base_list, &nmemb, &size)) {
        return NULL;
    }

    int key = (int)PyLong_AsLong(key_obj);
    int* base = (int*)PyMem_Malloc(nmemb * size);
    if (base == NULL) {
        PyErr_NoMemory();
        return NULL;
    }

    PyObject* item;
    for (Py_ssize_t i = 0; i < nmemb; i++) {
        item = PyList_GetItem(base_list, i);
        base[i] = (int)PyLong_AsLong(item);
    }

    int* result = (int*)bsearch(&key, base, nmemb, size, compare);
    PyMem_Free(base);

    if (result == NULL) {
        Py_RETURN_NONE;
    }
    return PyLong_FromLong(*result);
}

// qsort işlevini Python'a getirme
static int compare_qsort(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

static PyObject* py_qsort(PyObject* self, PyObject* args) {
    PyObject* base_list;
    Py_ssize_t nmemb, size;
    if (!PyArg_ParseTuple(args, "Onn", &base_list, &nmemb, &size)) {
        return NULL;
    }

    int* base = (int*)PyMem_Malloc(nmemb * size);
    if (base == NULL) {
        PyErr_NoMemory();
        return NULL;
    }

    PyObject* item;
    for (Py_ssize_t i = 0; i < nmemb; i++) {
        item = PyList_GetItem(base_list, i);
        base[i] = (int)PyLong_AsLong(item);
    }

    qsort(base, nmemb, size, compare_qsort);
    PyObject* result_list = PyList_New(nmemb);
    for (Py_ssize_t i = 0; i < nmemb; i++) {
        PyList_SetItem(result_list, i, PyLong_FromLong(base[i]));
    }
    PyMem_Free(base);
    return result_list;
}

// memcpy işlevini Python'a getirme
static PyObject* py_memcpy(PyObject* self, PyObject* args) {
    PyObject* dest_obj;
    PyObject* src_obj;
    Py_ssize_t n;
    if (!PyArg_ParseTuple(args, "OOn", &dest_obj, &src_obj, &n)) {
        return NULL;
    }
    void* dest = PyBytes_AsString(dest_obj);
    const void* src = PyBytes_AsString(src_obj);
    memcpy(dest, src, n);
    Py_RETURN_NONE;
}

// strtok işlevini Python'a getirme
static PyObject* py_strtok(PyObject* self, PyObject* args) {
    const char* str;
    const char* delimiters;
    char* token;
    static char* saved_ptr = NULL;

    if (!PyArg_ParseTuple(args, "ss", &str, &delimiters)) {
        return NULL;
    }

    if (str != NULL) {
        saved_ptr = (char*)str;
    }

    token = strtok_r(saved_ptr, delimiters, &saved_ptr);
    if (token == NULL) {
        Py_RETURN_NONE;
    }

    return PyUnicode_FromString(token);
}

// asctime işlevini Python'a getirme
static PyObject* py_asctime(PyObject* self, PyObject* args) {
    struct tm tm;
    if (!PyArg_ParseTuple(args, "iiiiii", &tm.tm_sec, &tm.tm_min, &tm.tm_hour,
                          &tm.tm_mday, &tm.tm_mon, &tm.tm_year)) {
        return NULL;
    }
    tm.tm_year += 1900;
    tm.tm_mon += 1;
    char* result = asctime(&tm);
    return PyUnicode_FromString(result);
}

// localtime işlevini Python'a getirme
static PyObject* py_localtime(PyObject* self, PyObject* args) {
    time_t rawtime;
    struct tm* timeinfo;
    if (!PyArg_ParseTuple(args, "l", &rawtime)) {
        return NULL;
    }
    timeinfo = localtime(&rawtime);
    return Py_BuildValue("iiiiii", timeinfo->tm_sec, timeinfo->tm_min, timeinfo->tm_hour,
                         timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year);
}

static PyMethodDef AdamlibraryMethods[] = {
    {"calloc", py_calloc, METH_VARARGS, "Allocate memory with calloc"},
    {"realloc", py_realloc, METH_VARARGS, "Reallocate memory"},
    {"bsearch", py_bsearch, METH_VARARGS, "Binary search"},
    {"qsort", py_qsort, METH_VARARGS, "Quick sort"},
    {"memcpy", py_memcpy, METH_VARARGS, "Memory copy"},
    {"strtok", py_strtok, METH_VARARGS, "String tokenization"},
    {"asctime", py_asctime, METH_VARARGS, "Convert tm structure to string"},
    {"localtime", py_localtime, METH_VARARGS, "Convert time_t to tm structure"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Adamlibrary = {
    PyModuleDef_HEAD_INIT,
    "Adamlibrary",
    NULL,
    -1,
    AdamlibraryMethods
};

PyMODINIT_FUNC PyInit_Adamlibrary(void) {
    return PyModule_Create(&Adamlibrary);
}
