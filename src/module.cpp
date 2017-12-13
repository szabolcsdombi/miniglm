#include "common.hpp"

PyObject * mat4_perspective(PyObject * self, PyObject * args);
PyObject * mat4_ortho(PyObject * self, PyObject * args);
PyObject * mat4_look_at(PyObject * self, PyObject * args);

PyMethodDef methods[] = {
	{"mat4_perspective", mat4_perspective, METH_VARARGS, 0},
	{"mat4_ortho", mat4_ortho, METH_VARARGS, 0},
	{"mat4_look_at", mat4_look_at, METH_VARARGS, 0},
	{0},
};


#if PY_MAJOR_VERSION >= 3

PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"glm",
	0,
	-1,
	methods,
	0,
	0,
	0,
	0,
};

PyObject * Initialize(PyObject * module) {
	{
		if (PyType_Ready(&GLMMat2_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat2 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat2_Type);

		PyModule_AddObject(module, "Mat2", (PyObject *)&GLMMat2_Type);
	}
	{
		if (PyType_Ready(&GLMMat3_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat3 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat3_Type);

		PyModule_AddObject(module, "Mat3", (PyObject *)&GLMMat3_Type);
	}
	{
		if (PyType_Ready(&GLMMat4_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat4 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat4_Type);

		PyModule_AddObject(module, "Mat4", (PyObject *)&GLMMat4_Type);
	}

	{
		if (PyType_Ready(&GLMVec2_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec2 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec2_Type);

		PyModule_AddObject(module, "Vec2", (PyObject *)&GLMVec2_Type);
	}
	{
		if (PyType_Ready(&GLMVec3_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec3 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec3_Type);

		PyModule_AddObject(module, "Vec3", (PyObject *)&GLMVec3_Type);
	}
	{
		if (PyType_Ready(&GLMVec4_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec4 in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec4_Type);

		PyModule_AddObject(module, "Vec4", (PyObject *)&GLMVec4_Type);
	}

	{
		if (PyType_Ready(&GLMQuat_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Quat in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMQuat_Type);

		PyModule_AddObject(module, "Quat", (PyObject *)&GLMQuat_Type);
	}

	{
		if (PyType_Ready(&GLMVec2Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec2Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec2Array_Type);

		PyModule_AddObject(module, "Vec2Array", (PyObject *)&GLMVec2Array_Type);
	}

	{
		if (PyType_Ready(&GLMVec3Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec3Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec3Array_Type);

		PyModule_AddObject(module, "Vec3Array", (PyObject *)&GLMVec3Array_Type);
	}

	{
		if (PyType_Ready(&GLMVec4Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Vec4Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMVec4Array_Type);

		PyModule_AddObject(module, "Vec4Array", (PyObject *)&GLMVec4Array_Type);
	}

	{
		if (PyType_Ready(&GLMMat2Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat2Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat2Array_Type);

		PyModule_AddObject(module, "Mat2Array", (PyObject *)&GLMMat2Array_Type);
	}

	{
		if (PyType_Ready(&GLMMat3Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat3Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat3Array_Type);

		PyModule_AddObject(module, "Mat3Array", (PyObject *)&GLMMat3Array_Type);
	}

	{
		if (PyType_Ready(&GLMMat4Array_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Mat4Array in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMMat4Array_Type);

		PyModule_AddObject(module, "Mat4Array", (PyObject *)&GLMMat4Array_Type);
	}

	{
		if (PyType_Ready(&GLMQuatArray_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register QuatArray in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMQuatArray_Type);

		PyModule_AddObject(module, "QuatArray", (PyObject *)&GLMQuatArray_Type);
	}
	
	{
		if (PyType_Ready(&GLMFloatArray_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register FloatArray in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&GLMFloatArray_Type);

		PyModule_AddObject(module, "FloatArray", (PyObject *)&GLMFloatArray_Type);
	}

	return module;
}

extern "C" PyObject * PyInit_glm() {
	PyObject * module = PyModule_Create(&moduledef);
	return Initialize(module);
}

#else

extern "C" PyObject * initglm() {
	PyObject * module = Py_InitModule("glm", methods);
	return Initialize(module);
}

#endif
