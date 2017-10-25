#include "common.hpp"

glm::vec2 vec2_from_iterable(PyObject * iterable) {
	glm::vec2 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 2; ++i) {
		PyObject * item = PyIter_Next(iterator);
		if (!item) {
			Py_DECREF(iterator);
			PyErr_Format(PyExc_Exception, "not enough values to unpack");
			return result;
		}
		result[i] = (float)PyFloat_AsDouble(item);
		Py_DECREF(item);
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::vec3 vec3_from_iterable(PyObject * iterable) {
	glm::vec3 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 3; ++i) {
		PyObject * item = PyIter_Next(iterator);
		if (!item) {
			Py_DECREF(iterator);
			PyErr_Format(PyExc_Exception, "not enough values to unpack");
			return result;
		}
		result[i] = (float)PyFloat_AsDouble(item);
		Py_DECREF(item);
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::vec4 vec4_from_iterable(PyObject * iterable) {
	glm::vec4 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 4; ++i) {
		PyObject * item = PyIter_Next(iterator);
		if (!item) {
			Py_DECREF(iterator);
			PyErr_Format(PyExc_Exception, "not enough values to unpack");
			return result;
		}
		result[i] = (float)PyFloat_AsDouble(item);
		Py_DECREF(item);
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::mat2 mat2_from_iterable(PyObject * iterable) {
	glm::mat2 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			PyObject * item = PyIter_Next(iterator);
			if (!item) {
				Py_DECREF(iterator);
				PyErr_Format(PyExc_Exception, "not enough values to unpack");
				return result;
			}
			result[i][j] = (float)PyFloat_AsDouble(item);
			Py_DECREF(item);
		}
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::mat3 mat3_from_iterable(PyObject * iterable) {
	glm::mat3 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			PyObject * item = PyIter_Next(iterator);
			if (!item) {
				Py_DECREF(iterator);
				PyErr_Format(PyExc_Exception, "not enough values to unpack");
				return result;
			}
			result[i][j] = (float)PyFloat_AsDouble(item);
			Py_DECREF(item);
		}
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::mat4 mat4_from_iterable(PyObject * iterable) {
	glm::mat4 result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			PyObject * item = PyIter_Next(iterator);
			if (!item) {
				Py_DECREF(iterator);
				PyErr_Format(PyExc_Exception, "not enough values to unpack");
				return result;
			}
			result[i][j] = (float)PyFloat_AsDouble(item);
			Py_DECREF(item);
		}
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}

glm::quat quat_from_iterable(PyObject * iterable) {
	glm::quat result;
	PyObject * iterator = PyObject_GetIter(iterable);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "not iterable");
		return result;
	}

	for (int i = 0; i < 4; ++i) {
		PyObject * item = PyIter_Next(iterator);
		if (!item) {
			Py_DECREF(iterator);
			PyErr_Format(PyExc_Exception, "not enough values to unpack");
			return result;
		}
		result[i] = (float)PyFloat_AsDouble(item);
		Py_DECREF(item);
	}

	if (PyObject * item = PyIter_Next(iterator)) {
		Py_DECREF(item);
		Py_DECREF(iterator);
		PyErr_Format(PyExc_Exception, "too many values to unpack");
		return result;
	}

	Py_DECREF(iterator);
	return result;
}
