#include <Python.h>
#include <glm/glm.hpp>

PyObject * mymodule_meth_add(PyObject * self, PyObject * args) {
    glm::vec3 a, b;
    if (!PyArg_ParseTuple(args, "(fff)(fff)", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z)) {
        return NULL;
    }
    glm::vec3 c = a + b;
    return Py_BuildValue("fff", c.x, c.y, c.z);
}

PyMethodDef module_methods[] = {
    {"add", (PyCFunction)mymodule_meth_add, METH_VARARGS, NULL},
    {},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "mymodule", NULL, -1, module_methods};

extern "C" PyObject * PyInit_mymodule() {
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
