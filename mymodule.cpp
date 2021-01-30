#include <Python.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

PyObject * mymodule_meth_add(PyObject * self, PyObject * args) {
    glm::dvec3 a, b;
    if (!PyArg_ParseTuple(args, "(ddd)(ddd)", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z)) {
        return NULL;
    }
    glm::dvec3 c = a + b;
    return Py_BuildValue("ddd", c.x, c.y, c.z);
}

PyObject * mymodule_meth_sub(PyObject * self, PyObject * args) {
    glm::dvec3 a, b;
    if (!PyArg_ParseTuple(args, "(ddd)(ddd)", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z)) {
        return NULL;
    }
    glm::dvec3 c = a - b;
    return Py_BuildValue("ddd", c.x, c.y, c.z);
}

PyObject * mymodule_meth_mul(PyObject * self, PyObject * args) {
    glm::dvec3 a;
    double f;
    if (!PyArg_ParseTuple(args, "(ddd)d", &a.x, &a.y, &a.z, &f)) {
        return NULL;
    }
    glm::dvec3 b = a * f;
    return Py_BuildValue("ddd", b.x, b.y, b.z);
}

PyObject * mymodule_meth_normalize(PyObject * self, PyObject * args) {
    glm::dvec3 v;
    if (!PyArg_ParseTuple(args, "(ddd)", &v.x, &v.y, &v.z)) {
        return NULL;
    }
    glm::dvec3 n = glm::normalize(v);
    return Py_BuildValue("ddd", n.x, n.y, n.z);
}

PyObject * mymodule_meth_quat2mat(PyObject * self, PyObject * args) {
    glm::dquat q;
    if (!PyArg_ParseTuple(args, "(dddd)", &q.x, &q.y, &q.z, &q.w)) {
        return NULL;
    }
    glm::dmat3 m = glm::dmat3(q);
    return Py_BuildValue("ddddddddd", m[0].x, m[0].y, m[0].z, m[1].x, m[1].y, m[1].z, m[2].x, m[2].y, m[2].z);
}

PyObject * mymodule_meth_mat2quat(PyObject * self, PyObject * args) {
    glm::dmat3 m;
    if (!PyArg_ParseTuple(args, "(ddddddddd)", &m[0].x, &m[0].y, &m[0].z, &m[1].x, &m[1].y, &m[1].z, &m[2].x, &m[2].y, &m[2].z)) {
        return NULL;
    }
    glm::dquat q = glm::dquat(m);
    return Py_BuildValue("dddd", q.x, q.y, q.z, q.w);
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
