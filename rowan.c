// rowan.c
#include <Python.h>
#include <structmember.h>

// RowanObject yapısı
typedef struct {
    PyObject_HEAD
    char *domain;
    char *ip_address;
    char *data;
} RowanObject;

// RowanObject için __init__ fonksiyonu
static int RowanObject_init(RowanObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"domain", "ip_address", "data", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sss", kwlist,
                                     &self->domain, &self->ip_address, &self->data))
        return -1;

    return 0;
}

// RowanObject'in verilerini yazdırma fonksiyonu
static PyObject *RowanObject_print(RowanObject *self) {
    if (self->data && strlen(self->data) > 0) {
        printf("Domain: %s\n", self->domain);
        printf("IP Address: %s\n", self->ip_address);
        printf("Data: %s\n", self->data);
    } else {
        printf("Kiwi not found\n");
    }
    Py_RETURN_NONE;
}

// RowanObject metotları
static PyMethodDef RowanObject_methods[] = {
    {"print_info", (PyCFunction)RowanObject_print, METH_NOARGS, "Print the Rowan Object's information"},
    {NULL}  /* Sentinel */
};

// RowanObject üyeleri
static PyMemberDef RowanObject_members[] = {
    {"domain", T_STRING, offsetof(RowanObject, domain), 0, "domain name"},
    {"ip_address", T_STRING, offsetof(RowanObject, ip_address), 0, "IP address"},
    {"data", T_STRING, offsetof(RowanObject, data), 0, "associated data"},
    {NULL}  /* Sentinel */
};

// RowanObject tip tanımı
static PyTypeObject RowanObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "megaognezyum.RowanObject",
    .tp_doc = "Rowan Object for data caching and validation",
    .tp_basicsize = sizeof(RowanObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)RowanObject_init,
    .tp_members = RowanObject_members,
    .tp_methods = RowanObject_methods,
};

// Modül tanımı
static PyModuleDef megaognezyummodule = {
    PyModuleDef_HEAD_INIT,
    "megaognezyum",   /* module name */
    "Mega Ognezyum Module", /* module doc */
    -1,       /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    NULL, NULL, NULL, NULL, NULL
};

// Modül başlatma fonksiyonu
PyMODINIT_FUNC PyInit_megaognezyum(void) {
    PyObject *m;
    if (PyType_Ready(&RowanObjectType) < 0)
        return NULL;

    m = PyModule_Create(&megaognezyummodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&RowanObjectType);
    if (PyModule_AddObject(m, "RowanObject", (PyObject *)&RowanObjectType) < 0) {
        Py_DECREF(&RowanObjectType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
