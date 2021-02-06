#include <Python.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

enum OperandType {
    SCALAR,
    VECTOR,
    QUATERNION,
    MATRIX,
};

struct Operand {
    OperandType type;
    union {
        double s;
        glm::dvec3 v;
        glm::dquat q;
        glm::dmat3 m;
    };
};

int converter(PyObject * obj, Operand * operand) {
    if (PyFloat_Check(obj)) {
        operand->type = SCALAR;
        operand->s = PyFloat_AsDouble(obj);
        return 1;
    }
    if (PyLong_Check(obj)) {
        operand->type = SCALAR;
        operand->s = PyLong_AsDouble(obj);
        return 1;
    }
    if (!PyTuple_CheckExact(obj)) {
        PyErr_Format(PyExc_TypeError, "invalid operand");
        return 0;
    }
    if (PyTuple_Size(obj) == 3) {
        operand->type = VECTOR;
        operand->v.x = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 0));
        operand->v.y = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 1));
        operand->v.z = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 2));
        if (PyErr_Occurred()) {
            return NULL;
        }
        return 1;
    }
    if (PyTuple_Size(obj) == 4) {
        operand->type = QUATERNION;
        operand->q.x = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 0));
        operand->q.y = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 1));
        operand->q.z = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 2));
        operand->q.w = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 3));
        if (PyErr_Occurred()) {
            return NULL;
        }
        return 1;
    }
    if (PyTuple_Size(obj) == 9) {
        operand->type = MATRIX;
        operand->m[0].x = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 0));
        operand->m[0].y = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 1));
        operand->m[0].z = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 2));
        operand->m[1].x = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 3));
        operand->m[1].y = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 4));
        operand->m[1].z = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 5));
        operand->m[2].x = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 6));
        operand->m[2].y = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 7));
        operand->m[2].z = PyFloat_AsDouble(PyTuple_GET_ITEM(obj, 8));
        if (PyErr_Occurred()) {
            return NULL;
        }
        return 1;
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return 0;
}

PyObject * tup(const glm::dvec3 & v) {
    PyObject * res = PyTuple_New(3);
    PyTuple_SET_ITEM(res, 0, PyFloat_FromDouble(v.x));
    PyTuple_SET_ITEM(res, 1, PyFloat_FromDouble(v.y));
    PyTuple_SET_ITEM(res, 2, PyFloat_FromDouble(v.z));
    return res;
}

PyObject * tup(const glm::dquat & q) {
    PyObject * res = PyTuple_New(4);
    PyTuple_SET_ITEM(res, 0, PyFloat_FromDouble(q.x));
    PyTuple_SET_ITEM(res, 1, PyFloat_FromDouble(q.y));
    PyTuple_SET_ITEM(res, 2, PyFloat_FromDouble(q.z));
    PyTuple_SET_ITEM(res, 3, PyFloat_FromDouble(q.w));
    return res;
}

PyObject * tup(const glm::dmat3 & m) {
    PyObject * res = PyTuple_New(9);
    PyTuple_SET_ITEM(res, 0, PyFloat_FromDouble(m[0].x));
    PyTuple_SET_ITEM(res, 1, PyFloat_FromDouble(m[0].y));
    PyTuple_SET_ITEM(res, 2, PyFloat_FromDouble(m[0].z));
    PyTuple_SET_ITEM(res, 3, PyFloat_FromDouble(m[1].x));
    PyTuple_SET_ITEM(res, 4, PyFloat_FromDouble(m[1].y));
    PyTuple_SET_ITEM(res, 5, PyFloat_FromDouble(m[1].z));
    PyTuple_SET_ITEM(res, 6, PyFloat_FromDouble(m[2].x));
    PyTuple_SET_ITEM(res, 7, PyFloat_FromDouble(m[2].y));
    PyTuple_SET_ITEM(res, 8, PyFloat_FromDouble(m[2].z));
    return res;
}

PyObject * bytes(double s) {
    float encoded[] = {(float)s};
    return PyBytes_FromStringAndSize((char *)encoded, sizeof(encoded));
}

PyObject * bytes(const glm::dvec3 & v) {
    float encoded[] = {(float)v.x, (float)v.y, (float)v.z};
    return PyBytes_FromStringAndSize((char *)encoded, sizeof(encoded));
}

PyObject * bytes(const glm::dquat & q) {
    float encoded[] = {(float)q.x, (float)q.y, (float)q.z, (float)q.w};
    return PyBytes_FromStringAndSize((char *)encoded, sizeof(encoded));
}

PyObject * bytes(const glm::dmat3 & m) {
    float encoded[] = {
        (float)m[0].x, (float)m[0].y, (float)m[0].z,
        (float)m[1].x, (float)m[1].y, (float)m[1].z,
        (float)m[2].x, (float)m[2].y, (float)m[2].z,
    };
    return PyBytes_FromStringAndSize((char *)encoded, sizeof(encoded));
}

PyObject * meth_add(PyObject * self, PyObject * args) {
    Operand a, b;
    if (!PyArg_ParseTuple(args, "O&O&", converter, &a, converter, &b)) {
        return NULL;
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return tup(a.v + b.v);
    }
    if (a.type == VECTOR && b.type == SCALAR) {
        return tup(a.v + b.s);
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_sub(PyObject * self, PyObject * args) {
    Operand a, b;
    if (!PyArg_ParseTuple(args, "O&O&", converter, &a, converter, &b)) {
        return NULL;
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return tup(a.v - b.v);
    }
    if (a.type == VECTOR && b.type == SCALAR) {
        return tup(a.v - b.s);
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_mul(PyObject * self, PyObject * args) {
    Operand a, b;
    if (!PyArg_ParseTuple(args, "O&O&", converter, &a, converter, &b)) {
        return NULL;
    }
    if (a.type == VECTOR && b.type == SCALAR) {
        return tup(a.v * b.s);
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return tup(a.v * b.v);
    }
    if (a.type == QUATERNION && b.type == VECTOR) {
        return tup(a.q * b.v);
    }
    if (a.type == QUATERNION && b.type == QUATERNION) {
        return tup(a.q * b.q);
    }
    if (a.type == QUATERNION && b.type == MATRIX) {
        return tup(glm::dmat3(a.q) * b.m);
    }
    if (a.type == MATRIX && b.type == VECTOR) {
        return tup(a.m * b.v);
    }
    if (a.type == MATRIX && b.type == QUATERNION) {
        return tup(glm::dquat(a.m) * b.q);
    }
    if (a.type == MATRIX && b.type == MATRIX) {
        return tup(a.m * b.m);
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_mix(PyObject * self, PyObject * args) {
    Operand a, b;
    double s;
    if (!PyArg_ParseTuple(args, "O&O&d", converter, &a, converter, &b, &s)) {
        return NULL;
    }
    if (a.type == SCALAR && b.type == SCALAR) {
        return PyFloat_FromDouble(glm::mix(a.s, b.s, s));
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return tup(glm::mix(a.v, b.v, s));
    }
    if (a.type == QUATERNION && b.type == QUATERNION) {
        return tup(glm::slerp(a.q, b.q, s));
    }
    if (a.type == MATRIX && b.type == MATRIX) {
        return tup(glm::dmat3(glm::slerp(glm::dquat(a.m), glm::dquat(b.m), s)));
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_cross(PyObject * self, PyObject * args) {
    Operand a, b;
    if (!PyArg_ParseTuple(args, "O&O&", converter, &a, converter, &b)) {
        return NULL;
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return tup(glm::cross(a.v, b.v));
    }
    if (a.type == QUATERNION && b.type == QUATERNION) {
        return tup(glm::cross(a.q, b.q));
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_dot(PyObject * self, PyObject * args) {
    Operand a, b;
    if (!PyArg_ParseTuple(args, "O&O&", converter, &a, converter, &b)) {
        return NULL;
    }
    if (a.type == VECTOR && b.type == VECTOR) {
        return PyFloat_FromDouble(glm::dot(a.v, b.v));
    }
    if (a.type == QUATERNION && b.type == QUATERNION) {
        return PyFloat_FromDouble(glm::dot(a.q, b.q));
    }
    PyErr_Format(PyExc_TypeError, "invalid operands");
    return NULL;
}

PyObject * meth_rotate(PyObject * self, PyObject * args) {
    double s;
    glm::dvec3 v;
    if (!PyArg_ParseTuple(args, "d(ddd)", &s, &v.x, &v.y, &v.z)) {
        return NULL;
    }
    return tup(glm::angleAxis(s, v));
}

PyObject * meth_split(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == QUATERNION) {
        PyObject * res = PyTuple_New(2);
        PyTuple_SET_ITEM(res, 0, PyFloat_FromDouble(glm::angle(a.q)));
        PyTuple_SET_ITEM(res, 1, tup(glm::axis(a.q)));
        return res;
    }
    if (a.type == MATRIX) {
        PyObject * res = PyTuple_New(3);
        PyTuple_SET_ITEM(res, 0, tup(a.m[0]));
        PyTuple_SET_ITEM(res, 1, tup(a.m[1]));
        PyTuple_SET_ITEM(res, 2, tup(a.m[2]));
        return res;
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_norm(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == VECTOR) {
        return tup(glm::normalize(a.v));
    }
    if (a.type == QUATERNION) {
        return tup(glm::normalize(a.q));
    }
    if (a.type == MATRIX) {
        return tup(glm::dmat3(glm::normalize(glm::dquat(a.m))));
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_inv(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == QUATERNION) {
        return tup(glm::inverse(a.q));
    }
    if (a.type == MATRIX) {
        return tup(glm::inverse(a.m));
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_det(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == MATRIX) {
        return PyFloat_FromDouble(glm::determinant(a.m));
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_cast(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == QUATERNION) {
        return tup(glm::dmat3(a.q));
    }
    if (a.type == MATRIX) {
        return tup(glm::dquat(a.m));
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_swizzle(PyObject * self, PyObject * args) {
    Operand a;
    const char * swizzle;
    if (!PyArg_ParseTuple(args, "O&s", converter, &a, &swizzle)) {
        return NULL;
    }
    if (a.type == VECTOR) {
        return tup({
            a.v[(swizzle[0] - 'x') & 3],
            a.v[(swizzle[1] - 'x') & 3],
            a.v[(swizzle[2] - 'x') & 3],
        });
    }
    if (a.type == QUATERNION) {
        return tup({
            a.q[(swizzle[3] - 'x') & 3],
            a.q[(swizzle[0] - 'x') & 3],
            a.q[(swizzle[1] - 'x') & 3],
            a.q[(swizzle[2] - 'x') & 3],
        });
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyObject * meth_pack(PyObject * self, PyObject * arg) {
    Operand a;
    if (!converter(arg, &a)) {
        return NULL;
    }
    if (a.type == SCALAR) {
        return bytes(a.s);
    }
    if (a.type == VECTOR) {
        return bytes(a.v);
    }
    if (a.type == QUATERNION) {
        return bytes(a.q);
    }
    if (a.type == MATRIX) {
        return bytes(a.m);
    }
    PyErr_Format(PyExc_TypeError, "invalid operand");
    return NULL;
}

PyMethodDef module_methods[] = {
    {"add", (PyCFunction)meth_add, METH_VARARGS, NULL},
    {"sub", (PyCFunction)meth_sub, METH_VARARGS, NULL},
    {"mul", (PyCFunction)meth_mul, METH_VARARGS, NULL},
    {"mix", (PyCFunction)meth_mix, METH_VARARGS, NULL},
    {"cross", (PyCFunction)meth_cross, METH_VARARGS, NULL},
    {"dot", (PyCFunction)meth_dot, METH_VARARGS, NULL},
    {"rotate", (PyCFunction)meth_rotate, METH_VARARGS, NULL},
    {"split", (PyCFunction)meth_split, METH_O, NULL},
    {"norm", (PyCFunction)meth_norm, METH_O, NULL},
    {"inv", (PyCFunction)meth_inv, METH_O, NULL},
    {"det", (PyCFunction)meth_det, METH_O, NULL},
    {"cast", (PyCFunction)meth_cast, METH_O, NULL},
    {"swizzle", (PyCFunction)meth_swizzle, METH_VARARGS, NULL},
    {"pack", (PyCFunction)meth_pack, METH_O, NULL},
    {},
};

int module_exec(PyObject * self) {
    PyObject * pi = PyFloat_FromDouble(glm::pi<double>());
    PyModule_AddObject(self, "pi", pi);
    return 0;
}

PyModuleDef_Slot module_slots[] = {
    {Py_mod_exec, module_exec},
    {},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "miniglm", NULL, 0, module_methods, module_slots};

extern "C" PyObject * PyInit_miniglm() {
    return PyModuleDef_Init(&module_def);
}
