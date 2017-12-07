#include "common.hpp"

#define N 4

PyObject * GLMQuat_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMQuat * self = (GLMQuat *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void GLMQuat_tp_dealloc(GLMQuat * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMQuat_tp_init(GLMQuat * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable;

	int args_ok = PyArg_ParseTuple(
		args,
		"O",
		&iterable
	);

	if (!args_ok) {
		return -1;
	}

	if (Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) == N) {
		self->val[0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 0));
		self->val[1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 1));
		self->val[2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 2));
		self->val[3] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, 3));

		if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	if (Py_TYPE(iterable) == &GLMMat3_Type) {
		self->val = glm::quat_cast(((GLMMat3 *)iterable)->val);
		return 0;
	}

	self->val = quat_from_iterable(iterable);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMQuat_tp_repr(GLMQuat * self) {
	PyObject * temp = GLMQuat_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMQuat_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMQuat_Type && Py_TYPE(rhs) == &GLMQuat_Type) {
		GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
		res->val = ((GLMQuat *)lhs)->val * ((GLMQuat *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMQuat_Type) {
		if (Py_TYPE(rhs) == &GLMVec3_Type) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = ((GLMQuat *)lhs)->val * ((GLMVec3 *)rhs)->val;
			return (PyObject *)res;
		}

		if (Py_TYPE(rhs) == &GLMMat3_Type) {
			GLMMat3 * res = (GLMMat3 *)GLMMat3_tp_new(&GLMMat3_Type, 0, 0);
			res->val = glm::mat3_cast(((GLMQuat *)lhs)->val) * ((GLMMat3 *)rhs)->val;
			return (PyObject *)res;
		}

		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
			res->val = ((GLMQuat *)lhs)->val * rhs_float;
			return (PyObject *)res;
		}

		glm::quat quat_rhs = quat_from_iterable(rhs);
		if (!PyErr_Occurred()) {
			GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
			res->val = ((GLMQuat *)lhs)->val * quat_rhs;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		glm::quat quat_lhs = quat_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
			res->val = quat_lhs * ((GLMQuat *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuat_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMQuat_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
			res->val = ((GLMQuat *)lhs)->val / rhs_float;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuat_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		((GLMQuat *)lhs)->val *= ((GLMQuat *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMQuat *)lhs)->val *= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	glm::quat quat_rhs = quat_from_iterable(rhs);
	if (!PyErr_Occurred()) {
		((GLMQuat *)lhs)->val *= quat_rhs;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuat_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMQuat *)lhs)->val /= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuat_nb_negative(GLMQuat * self) {
	GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
	res->val = -((GLMQuat *)self)->val;
	return (PyObject *)res;
}

PyObject * GLMQuat_nb_positive(GLMQuat * self) {
	GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
	res->val = +((GLMQuat *)self)->val;
	return (PyObject *)res;
}

PyNumberMethods GLMQuat_tp_as_number = {
	0, // binaryfunc nb_add;
	0, // binaryfunc nb_subtract;
	(binaryfunc)GLMQuat_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMQuat_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMQuat_nb_positive, // unaryfunc nb_positive;
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
	0, // binaryfunc nb_inplace_add;
	0, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMQuat_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMQuat_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMQuat_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMQuat_sq_length(GLMQuat * self) {
	return N;
}

PyObject * GLMQuat_sq_item(GLMQuat * self, Py_ssize_t key) {
	if (key < N) {
		return PyFloat_FromDouble(self->val[key]);
	} else {
		return 0;
	}
}

int GLMQuat_sq_ass_item(GLMQuat * self, Py_ssize_t key, PyObject * value) {
	if (key < N) {
		float x = (float)PyFloat_AsDouble(value);
		if (PyErr_Occurred()) {
			return -1;
		}
		self->val[key] = x;
		return 0;
	} else {
		return -1;
	}
}

PySequenceMethods GLMQuat_tp_as_sequence = {
	(lenfunc)GLMQuat_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMQuat_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMQuat_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMQuat_bf_getbuffer(GLMQuat * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMQuat_tp_as_buffer = {
	(getbufferproc)GLMQuat_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMQuat_tp_meth_dot(GLMQuat * lhs, PyObject * args) {
	PyObject * rhs = PyTuple_GetItem(args, 0);
	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		return PyFloat_FromDouble(glm::dot(lhs->val, ((GLMQuat *)rhs)->val));
	}
	return 0;
}

PyObject * GLMQuat_tp_meth_cross(GLMQuat * lhs, PyObject * args) {
	PyObject * rhs = PyTuple_GetItem(args, 0);
	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
		res->val = glm::cross(lhs->val, ((GLMQuat *)rhs)->val);
		return (PyObject *)res;
	}
	return 0;
}

PyObject * GLMQuat_tp_meth_slerp(GLMQuat * lhs, PyObject * args) {
	PyObject * rhs = PyTuple_GetItem(args, 0);
	float coef = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 1));
	if (PyErr_Occurred()) {
		return 0;
	}
	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
		res->val = glm::slerp(lhs->val, ((GLMQuat *)rhs)->val, coef);
		return (PyObject *)res;
	}
	return 0;
}

PyObject * GLMQuat_tp_meth_lerp(GLMQuat * lhs, PyObject * args) {
	PyObject * rhs = PyTuple_GetItem(args, 0);
	float coef = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 1));
	if (PyErr_Occurred()) {
		return 0;
	}
	if (Py_TYPE(rhs) == &GLMQuat_Type) {
		GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
		res->val = glm::lerp(lhs->val, ((GLMQuat *)rhs)->val, coef);
		return (PyObject *)res;
	}
	return 0;
}

PyMethodDef GLMQuat_tp_methods[] = {
	{"dot", (PyCFunction)GLMQuat_tp_meth_dot, METH_VARARGS, 0},
	{"cross", (PyCFunction)GLMQuat_tp_meth_cross, METH_VARARGS, 0},
	{"slerp", (PyCFunction)GLMQuat_tp_meth_slerp, METH_VARARGS, 0},
	{"lerp", (PyCFunction)GLMQuat_tp_meth_lerp, METH_VARARGS, 0},
	{0},
};

PyObject * GLMQuat_tp_get_conj(GLMQuat * self, void * closure) {
	GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
	res->val = glm::conjugate(self->val);
	return (PyObject *)res;
}

PyObject * GLMQuat_tp_get_inv(GLMQuat * self, void * closure) {
	GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
	res->val = glm::inverse(self->val);
	return (PyObject *)res;
}

PyObject * GLMQuat_tp_get_length(GLMQuat * self, void * closure) {
	return PyFloat_FromDouble(glm::length(self->val));
}

PyObject * GLMQuat_tp_get_normal(GLMQuat * self, void * closure) {
	GLMQuat * res = (GLMQuat *)GLMQuat_tp_new(&GLMQuat_Type, 0, 0);
	res->val = glm::normalize(self->val);
	return (PyObject *)res;
}

PyObject * GLMQuat_tp_get_axis(GLMQuat * self, void * closure) {
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	float s = (float)sqrt(1.0 - self->val.w * self->val.w);
	res->val = glm::vec3(self->val.x / s, self->val.y / s, self->val.z / s);
	return (PyObject *)res;
}

PyObject * GLMQuat_tp_get_angle(GLMQuat * self, void * closure) {
	return PyFloat_FromDouble(2.0 * acos(self->val.w));
}

PyObject * GLMQuat_tp_get_tup(GLMQuat * self, void * closure) {
	return GLMQuat_Tuple(self);
}

PyObject * GLMQuat_tp_get_data(GLMQuat * self, void * closure) {
	PyObject * res = PyBytes_FromStringAndSize(0, sizeof(self->val));
	memcpy(PyBytes_AS_STRING(res), &self->val, sizeof(self->val));
	return res;
}

PyGetSetDef GLMQuat_tp_getseters[] = {
	{(char *)"length", (getter)GLMQuat_tp_get_length, 0, 0, 0},
	{(char *)"normal", (getter)GLMQuat_tp_get_normal, 0, 0, 0},
	{(char *)"conj", (getter)GLMQuat_tp_get_conj, 0, 0, 0},
	{(char *)"inv", (getter)GLMQuat_tp_get_inv, 0, 0, 0},
	{(char *)"axis", (getter)GLMQuat_tp_get_axis, 0, 0, 0},
	{(char *)"angle", (getter)GLMQuat_tp_get_angle, 0, 0, 0},
	{(char *)"tup", (getter)GLMQuat_tp_get_tup, 0, 0, 0},
	{(char *)"data", (getter)GLMQuat_tp_get_data, 0, 0, 0},
	{0},
};

PyTypeObject GLMQuat_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Quat", // tp_name
	sizeof(GLMQuat), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMQuat_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMQuat_tp_repr, // tp_repr
	&GLMQuat_tp_as_number, // tp_as_number
	&GLMQuat_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMQuat_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMQuat_tp_methods, // tp_methods
	0, // tp_members
	GLMQuat_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMQuat_tp_init, // tp_init
	0, // tp_alloc
	GLMQuat_tp_new, // tp_new
};

PyObject * GLMQuat_Tuple(GLMQuat * self) {
	PyObject * tuple = PyTuple_New(N);
	PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(self->val[0]));
	PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(self->val[1]));
	PyTuple_SET_ITEM(tuple, 2, PyFloat_FromDouble(self->val[2]));
	PyTuple_SET_ITEM(tuple, 3, PyFloat_FromDouble(self->val[3]));
	return tuple;
}
