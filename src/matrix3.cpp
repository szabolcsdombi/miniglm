#include "common.hpp"

#define N 3

PyObject * GLMMat3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMMat3 * self = (GLMMat3 *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void GLMMat3_tp_dealloc(GLMMat3 * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMMat3_tp_init(GLMMat3 * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable;

	int args_ok = PyArg_ParseTuple(
		args,
		"O",
		&iterable
	);

	if (!args_ok) {
		return -1;
	}

	if (Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) == N * N) {
		self->val[0][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 0));
		self->val[0][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 1));
		self->val[0][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 2));
		self->val[1][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 3));
		self->val[1][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 4));
		self->val[1][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 5));
		self->val[2][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 6));
		self->val[2][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 7));
		self->val[2][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 8));

		if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	if (Py_TYPE(iterable) == &GLMQuat_Type) {
		self->val = glm::mat3_cast(((GLMQuat *)iterable)->val);
		return 0;
	}

	self->val = mat3_from_iterable(iterable);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMMat3_tp_repr(GLMMat3 * self) {
	PyObject * temp = GLMMat3_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMMat3_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat3_Type && Py_TYPE(rhs) == &GLMMat3_Type) {
		GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
		res->val = ((GLMMat3 *)lhs)->val + ((GLMMat3 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat3_Type) {
		glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val + mat3_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		glm::mat3 mat3_lhs = mat3_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = mat3_lhs + ((GLMMat3 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat3_Type && Py_TYPE(rhs) == &GLMMat3_Type) {
		GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
		res->val = ((GLMMat3 *)lhs)->val - ((GLMMat3 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat3_Type) {
		glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val - mat3_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		glm::mat3 mat3_lhs = mat3_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = mat3_lhs - ((GLMMat3 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat3_Type && Py_TYPE(rhs) == &GLMMat3_Type) {
		GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
		res->val = ((GLMMat3 *)lhs)->val * ((GLMMat3 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat3_Type) {
		if (Py_TYPE(rhs) == &GLMVec3_Type) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val * ((GLMVec3 *)rhs)->val;
			return (PyObject *)res;
		}

		if (Py_TYPE(rhs) == &GLMQuat_Type) {
			GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
			res->val = glm::quat_cast(((GLMMat3 *)lhs)->val) * ((GLMQuat *)rhs)->val;
			return (PyObject *)res;
		}

		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val * rhs_float;
			return (PyObject *)res;
		}

		glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val * mat3_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		float lhs_float = (float)PyFloat_AsDouble(lhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = lhs_float * ((GLMMat3 *)lhs)->val;
			return (PyObject *)res;
		}

		glm::mat3 mat3_lhs = mat3_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = mat3_lhs * ((GLMMat3 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat3_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = ((GLMMat3 *)lhs)->val / rhs_float;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		((GLMMat3 *)lhs)->val += ((GLMMat3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat3 *)lhs)->val += mat3_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		((GLMMat3 *)lhs)->val -= ((GLMMat3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat3 *)lhs)->val -= mat3_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat3_Type) {
		((GLMMat3 *)lhs)->val *= ((GLMMat3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat3 *)lhs)->val *= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat3 mat3_rhs = mat3_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat3 *)lhs)->val *= mat3_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat3 *)lhs)->val /= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3_nb_negative(PyObject * self) {
	GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
	res->val = -((GLMMat3 *)self)->val;
	return (PyObject *)res;
}

PyObject * GLMMat3_nb_positive(PyObject * self) {
	GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
	res->val = +((GLMMat3 *)self)->val;
	return (PyObject *)res;
}

PyNumberMethods GLMMat3_tp_as_number = {
	(binaryfunc)GLMMat3_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMMat3_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMMat3_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMMat3_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMMat3_nb_positive, // unaryfunc nb_positive;
	0, // unaryfunc nb_absolute;
	0, // inquiry nb_bool;
	0, // unaryfunc nb_invert;
	0, // binaryfunc nb_lshift;
	0, // binaryfunc nb_rshift;
	0, // binaryfunc nb_and;
	0, // binaryfunc nb_xor;
	0, // binaryfunc nb_or;
	0, // unaryfunc nb_int;
	0, // void *nb_reserved;
	0, // unaryfunc nb_float;
	(binaryfunc)GLMMat3_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMMat3_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMMat3_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMMat3_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMMat3_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMMat3_sq_length(GLMMat3 * self) {
	return N * N;
}

PyObject * GLMMat3_sq_item(GLMMat3 * self, Py_ssize_t key) {
	if (key < N * N) {
		return PyFloat_FromDouble(self->val[key / N][key % N]);
	} else {
		return 0;
	}
}

int GLMMat3_sq_ass_item(GLMMat3 * self, Py_ssize_t key, PyObject * value) {
	if (key < N * N) {
		float x = (float)PyFloat_AsDouble(value);
		if (PyErr_Occurred()) {
			return -1;
		}
		self->val[key / N][key % N] = x;
		return 0;
	} else {
		return -1;
	}
}

PySequenceMethods GLMMat3_tp_as_sequence = {
	(lenfunc)GLMMat3_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMMat3_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMMat3_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMMat3_bf_getbuffer(GLMMat3 * self, Py_buffer * view, int flags) {
	view->buf = (void *)&self->val;
	view->len = sizeof(self->val);
	view->itemsize = 1;

	view->format = 0;
	view->ndim = 0;
	view->shape = 0;
	view->strides = 0;
	view->suboffsets = 0;

	Py_INCREF(self);
	view->obj = (PyObject *)self;
	return 0;
}

PyBufferProcs GLMMat3_tp_as_buffer = {
	(getbufferproc)GLMMat3_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMMat3_tp_meth_row(GLMMat3 * self, PyObject * args) {
	int idx = PyLong_AsLong(PyTuple_GetItem(args, 0));
	if(PyErr_Occurred()){
		PyErr_Format(PyExc_Exception, "Missing parameter or invalid parameter!");
		return 0;
	}
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	res->val = glm::vec3(self->val[0][idx], self->val[1][idx], self->val[2][idx]);
	return (PyObject *)res;
}

PyObject * GLMMat3_tp_meth_col(GLMMat3 * self, PyObject * args) {
	int idx = PyLong_AsLong(PyTuple_GetItem(args, 0));
	if(PyErr_Occurred()){
		PyErr_Format(PyExc_Exception, "Missing parameter or invalid parameter!");
		return 0;
	}
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	res->val = glm::vec3(self->val[idx][0], self->val[idx][1], self->val[idx][2]);
	return (PyObject *)res;
}

PyMethodDef GLMMat3_tp_methods[] = {
	{"row", (PyCFunction)GLMMat3_tp_meth_row, METH_VARARGS, 0},
	{"col", (PyCFunction)GLMMat3_tp_meth_col, METH_VARARGS, 0},
	{0},
};

PyObject * GLMMat3_tp_get_trans(GLMMat3 * self, void * closure) {
	GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
	res->val = glm::transpose(self->val);
	return (PyObject *)res;
}

PyObject * GLMMat3_tp_get_det(GLMMat3 * self, void * closure) {
	return PyFloat_FromDouble(glm::determinant(self->val));
}

PyObject * GLMMat3_tp_get_inv(GLMMat3 * self, void * closure) {
	GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
	res->val = glm::inverse(self->val);
	return (PyObject *)res;
}

PyObject * GLMMat3_tp_get_tup(GLMMat3 * self, void * closure) {
	return GLMMat3_Tuple(self);
}

PyObject * GLMMat3_tp_get_data(GLMMat3 * self, void * closure) {
	PyObject * res = PyBytes_FromStringAndSize(0, sizeof(self->val));
	memcpy(PyBytes_AS_STRING(res), &self->val, sizeof(self->val));
	return res;
}

PyGetSetDef GLMMat3_tp_getseters[] = {
	{(char *)"trans", (getter)GLMMat3_tp_get_trans, 0, 0, 0},
	{(char *)"det", (getter)GLMMat3_tp_get_det, 0, 0, 0},
	{(char *)"inv", (getter)GLMMat3_tp_get_inv, 0, 0, 0},
	{(char *)"tup", (getter)GLMMat3_tp_get_tup, 0, 0, 0},
	{(char *)"data", (getter)GLMMat3_tp_get_data, 0, 0, 0},
	{0},
};

PyTypeObject GLMMat3_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Mat3", // tp_name
	sizeof(GLMMat3), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMMat3_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMMat3_tp_repr, // tp_repr
	&GLMMat3_tp_as_number, // tp_as_number
	&GLMMat3_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMMat3_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMMat3_tp_methods, // tp_methods
	0, // tp_members
	GLMMat3_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMMat3_tp_init, // tp_init
	0, // tp_alloc
	GLMMat3_tp_new, // tp_new
};

PyObject * GLMMat3_Tuple(GLMMat3 * self) {
	PyObject * tuple = PyTuple_New(N * N);
	PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(self->val[0][0]));
	PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(self->val[0][1]));
	PyTuple_SET_ITEM(tuple, 2, PyFloat_FromDouble(self->val[0][2]));
	PyTuple_SET_ITEM(tuple, 3, PyFloat_FromDouble(self->val[1][0]));
	PyTuple_SET_ITEM(tuple, 4, PyFloat_FromDouble(self->val[1][1]));
	PyTuple_SET_ITEM(tuple, 5, PyFloat_FromDouble(self->val[1][2]));
	PyTuple_SET_ITEM(tuple, 6, PyFloat_FromDouble(self->val[2][0]));
	PyTuple_SET_ITEM(tuple, 7, PyFloat_FromDouble(self->val[2][1]));
	PyTuple_SET_ITEM(tuple, 8, PyFloat_FromDouble(self->val[2][2]));
	return tuple;
}
