#include "common.hpp"

PyObject * mat4_perspective(PyObject * self, PyObject * args) {
	float fovy = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 0));
	float ratio = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 1));
	float znear = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 2));
	float zfar = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 3));
	if (PyErr_Occurred()) {
		return 0;
	}

	GLMMat4 * res = (GLMMat4 *)GLMMat4_tp_new(&GLMMat4_Type, 0, 0);
	res->val = glm::perspective(fovy, ratio, znear, zfar);
	return (PyObject *)res;
}

PyObject * mat4_ortho(PyObject * self, PyObject * args) {
	float left = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 0));
	float right = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 1));
	float bottom = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 2));
	float top = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 3));
	float znear = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 4));
	float zfar = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 5));
	if (PyErr_Occurred()) {
		return 0;
	}

	GLMMat4 * res = (GLMMat4 *)GLMMat4_tp_new(&GLMMat4_Type, 0, 0);
	res->val = glm::ortho(left, right, bottom, top, znear, zfar);
	return (PyObject *)res;
}

PyObject * mat4_look_at(PyObject * self, PyObject * args) {
	PyObject * eye = PyTuple_GetItem(args, 0);
	PyObject * center = PyTuple_GetItem(args, 1);
	PyObject * up = PyTuple_GetItem(args, 2);

	if (Py_TYPE(eye) == &GLMVec3_Type && Py_TYPE(center) == &GLMVec3_Type && Py_TYPE(up) == &GLMVec3_Type) {
		GLMMat4 * res = (GLMMat4 *)GLMMat4_tp_new(&GLMMat4_Type, 0, 0);
		res->val = glm::lookAt(
			((GLMVec3 *)eye)->val,
			((GLMVec3 *)center)->val,
			((GLMVec3 *)up)->val
		);
		return (PyObject *)res;
	}

	glm::vec3 vec3_eye = vec3_from_iterable(eye);
	glm::vec3 vec3_center = vec3_from_iterable(center);
	glm::vec3 vec3_up = vec3_from_iterable(up);

	if (PyErr_Occurred()) {
		return 0;
	}

	GLMMat4 * res = (GLMMat4 *)GLMMat4_tp_new(&GLMMat4_Type, 0, 0);
	res->val = glm::lookAt(vec3_eye, vec3_center, vec3_up);
	return (PyObject *)res;
}
