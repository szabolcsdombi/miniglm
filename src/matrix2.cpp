#include "common.hpp"

#define N 2

PyObject * GLMMat2_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMMat2 * self = (GLMMat2 *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void GLMMat2_tp_dealloc(GLMMat2 * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMMat2_tp_init(GLMMat2 * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable = PyTuple_GetItem(args, 0);

	if (Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) == N * N) {
		self->val[0][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 0));
		self->val[0][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 1));
		self->val[1][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 2));
		self->val[1][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 3));

		if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	self->val = mat2_from_iterable(iterable);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMMat2_tp_repr(GLMMat2 * self) {
	PyObject * temp = GLMMat2_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMMat2_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat2_Type && Py_TYPE(rhs) == &GLMMat2_Type) {
		GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
		res->val = ((GLMMat2 *)lhs)->val + ((GLMMat2 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat2_Type) {
		glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val + mat2_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		glm::mat2 mat2_lhs = mat2_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = mat2_lhs + ((GLMMat2 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat2_Type && Py_TYPE(rhs) == &GLMMat2_Type) {
		GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
		res->val = ((GLMMat2 *)lhs)->val - ((GLMMat2 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat2_Type) {
		glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val - mat2_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		glm::mat2 mat2_lhs = mat2_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = mat2_lhs - ((GLMMat2 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat2_Type && Py_TYPE(rhs) == &GLMMat2_Type) {
		GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
		res->val = ((GLMMat2 *)lhs)->val * ((GLMMat2 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMMat2_Type) {
		if (Py_TYPE(rhs) == &GLMVec2_Type) {
			GLMVec2 * res = (GLMVec2 *)GLMVec2_tp_new(&GLMVec2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val * ((GLMVec2 *)rhs)->val;
			return (PyObject *)res;
		}

		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val * rhs_float;
			return (PyObject *)res;
		}

		glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val * mat2_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		float lhs_float = (float)PyFloat_AsDouble(lhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = lhs_float * ((GLMMat2 *)lhs)->val;
			return (PyObject *)res;
		}

		glm::mat2 mat2_lhs = mat2_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = mat2_lhs * ((GLMMat2 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMMat2_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
			res->val = ((GLMMat2 *)lhs)->val / rhs_float;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		((GLMMat2 *)lhs)->val += ((GLMMat2 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat2 *)lhs)->val += mat2_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		((GLMMat2 *)lhs)->val -= ((GLMMat2 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat2 *)lhs)->val -= mat2_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMMat2_Type) {
		((GLMMat2 *)lhs)->val *= ((GLMMat2 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat2 *)lhs)->val *= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::mat2 mat2_rhs = mat2_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat2 *)lhs)->val *= mat2_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMMat2 *)lhs)->val /= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2_nb_negative(PyObject * self) {
	GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
	res->val = -((GLMMat2 *)self)->val;
	return (PyObject *)res;
}

PyObject * GLMMat2_nb_positive(PyObject * self) {
	GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
	res->val = +((GLMMat2 *)self)->val;
	return (PyObject *)res;
}

PyNumberMethods GLMMat2_tp_as_number = {
	(binaryfunc)GLMMat2_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMMat2_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMMat2_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMMat2_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMMat2_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMMat2_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMMat2_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMMat2_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMMat2_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMMat2_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMMat2_sq_length(GLMMat2 * self) {
	return N * N;
}

PyObject * GLMMat2_sq_item(GLMMat2 * self, Py_ssize_t key) {
	if (key < N * N) {
		return PyFloat_FromDouble(self->val[key / N][key % N]);
	} else {
		return 0;
	}
}

int GLMMat2_sq_ass_item(GLMMat2 * self, Py_ssize_t key, PyObject * value) {
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

PySequenceMethods GLMMat2_tp_as_sequence = {
	(lenfunc)GLMMat2_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMMat2_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMMat2_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMMat2_bf_getbuffer(GLMMat2 * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMMat2_tp_as_buffer = {
    (getbufferproc)GLMMat2_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMMat2_tp_meth_row(GLMMat2 * self, PyObject * args) {
	int idx = PyLong_AsLong(PyTuple_GetItem(args, 0));
	GLMVec2 * res = (GLMVec2 *)GLMVec2_tp_new(&GLMVec2_Type, 0, 0);
	res->val = glm::row(self->val, idx);
	return (PyObject *)res;
}

PyObject * GLMMat2_tp_meth_col(GLMMat2 * self, PyObject * args) {
	int idx = PyLong_AsLong(PyTuple_GetItem(args, 0));
	GLMVec2 * res = (GLMVec2 *)GLMVec2_tp_new(&GLMVec2_Type, 0, 0);
	res->val = glm::column(self->val, idx);
	return (PyObject *)res;
}

PyMethodDef GLMMat2_tp_methods[] = {
	{"row", (PyCFunction)GLMMat2_tp_meth_row, METH_VARARGS, 0},
	{"col", (PyCFunction)GLMMat2_tp_meth_col, METH_VARARGS, 0},
	{0},
};

PyObject * GLMMat2_tp_get_trans(GLMMat2 * self, void * closure) {
	GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
	res->val = glm::transpose(self->val);
	return (PyObject *)res;
}

PyObject * GLMMat2_tp_get_det(GLMMat2 * self, void * closure) {
	return PyFloat_FromDouble(glm::determinant(self->val));
}

PyObject * GLMMat2_tp_get_inv(GLMMat2 * self, void * closure) {
	GLMMat2 * res = (GLMMat2 *)GLMMat2_tp_new(&GLMMat2_Type, 0, 0);
	res->val = glm::inverse(self->val);
	return (PyObject *)res;
}

PyObject * GLMMat2_tp_get_tup(GLMMat2 * self, void * closure) {
	return GLMMat2_Tuple(self);
}

PyGetSetDef GLMMat2_tp_getseters[] = {
	{(char *)"trans", (getter)GLMMat2_tp_get_trans, 0, 0, 0},
	{(char *)"det", (getter)GLMMat2_tp_get_det, 0, 0, 0},
	{(char *)"inv", (getter)GLMMat2_tp_get_inv, 0, 0, 0},
	{(char *)"tup", (getter)GLMMat2_tp_get_tup, 0, 0, 0},
	{0},
};

PyTypeObject GLMMat2_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Mat2", // tp_name
	sizeof(GLMMat2), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMMat2_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMMat2_tp_repr, // tp_repr
	&GLMMat2_tp_as_number, // tp_as_number
	&GLMMat2_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMMat2_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMMat2_tp_methods, // tp_methods
	0, // tp_members
	GLMMat2_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMMat2_tp_init, // tp_init
	0, // tp_alloc
	GLMMat2_tp_new, // tp_new
};

PyObject * GLMMat2_Tuple(GLMMat2 * self) {
	PyObject * tuple = PyTuple_New(N * N);
	PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(self->val[0][0]));
	PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(self->val[0][1]));
	PyTuple_SET_ITEM(tuple, 2, PyFloat_FromDouble(self->val[1][0]));
	PyTuple_SET_ITEM(tuple, 3, PyFloat_FromDouble(self->val[1][1]));
	return tuple;
}
