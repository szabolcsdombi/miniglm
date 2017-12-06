#include "common.hpp"

#define N 4

PyObject * GLMVec4Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs){
    GLMVec4Array * self = (GLMVec4Array *)type->tp_alloc(type, 0);

    if(self){
        self->val = 0;
    }

    return (PyObject *)self;
}

void GLMVec4Array_tp_dealloc(GLMVec4Array * self){
    Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMVec4Array_tp_init(GLMVec4Array * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable = PyTuple_GetItem(args, 0);

	if (Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) % N == 0) {
		int size = PyTuple_GET_SIZE(iterable) / N;
		self->val = new glm::vec4[size];
		self->size = size;

		for (int i = 0; i < size; ++i) {
			self->val[i][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 0));
			self->val[i][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 1));
            self->val[i][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 2));
            self->val[i][3] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 3));
		}

		if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	PyObject * iterator = PyObject_GetIter(iterable);
	int size = PyObject_Size(iterable);

	if (!iterator || size < 0 || size % N) {
		PyErr_Format(PyExc_Exception, "not iterable or wrong size");
		return 0;
	}

	size = size / N;

	self->val = new glm::vec4[size];
	self->size = size;

	for (int k = 0; k < size; ++k) {
		for (int i = 0; i < N; ++i) {
			PyObject * item = PyIter_Next(iterator);
			self->val[k][i] = (float)PyFloat_AsDouble(item);
			Py_DECREF(item);
		}
	}

	Py_DECREF(iterator);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMVec4Array_tp_repr(GLMVec4Array * self) {
	PyObject * temp = GLMVec4Array_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}


PyObject * GLMVec4Array_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec4Array_Type && Py_TYPE(rhs) == &GLMVec4Array_Type) {
		GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec4[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] + rhs_val[i];
		}
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}


PyObject * GLMVec4Array_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec4Array_Type && Py_TYPE(rhs) == &GLMVec4Array_Type) {
		GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec4[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] - rhs_val[i];
		}
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}


PyObject * GLMVec4Array_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec4Array_Type && Py_TYPE(rhs) == &GLMVec4Array_Type) {
		GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec4[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] * rhs_val[i];
		}
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec4Array_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
			int size = ((GLMVec4Array *)lhs)->size;
			glm::vec4 * val = ((GLMVec4Array *)lhs)->val;
			res->size = size;
			res->val = new glm::vec4[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = val[i] * rhs_float;
			}
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		glm::mat4 mat4_lhs = mat4_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
			int size = ((GLMVec4Array *)rhs)->size;
			glm::vec4 * val = ((GLMVec4Array *)rhs)->val;
			res->size = size;
			res->val = new glm::vec4[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = mat4_lhs * val[i];
			}
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec4Array_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec4Array_Type && Py_TYPE(rhs) == &GLMVec4Array_Type) {
		GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec4[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] / rhs_val[i];
		}
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec4Array_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
			int size = ((GLMVec4Array *)lhs)->size;
			glm::vec4 * val = ((GLMVec4Array *)lhs)->val;
			res->size = size;
			res->val = new glm::vec4[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = val[i] / rhs_float;
			}
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}


PyObject * GLMVec4Array_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] += rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec4Array_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] -= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec4Array_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] *= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMVec4Array *)lhs)->size;
		glm::vec4 * val = ((GLMVec4Array *)lhs)->val;
		for (int i = 0; i < size; ++i) {
			val[i] *= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec4Array_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] /= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMVec4Array *)lhs)->size;
		glm::vec4 * val = ((GLMVec4Array *)lhs)->val;
		for (int i = 0; i < size; ++i) {
			val[i] /= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec4Array_nb_negative(GLMVec4Array * self) {
	GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
	int size = ((GLMVec4Array *)self)->size;
	glm::vec4 * val = ((GLMVec4Array *)self)->val;
	res->size = size;
	res->val = new glm::vec4[size];
	for (int i = 0; i < size; ++i) {
		res->val[i] = -val[i];
	}
	return (PyObject *)res;
}

PyObject * GLMVec4Array_nb_positive(GLMVec4Array * self) {
	GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
	int size = ((GLMVec4Array *)self)->size;
	glm::vec4 * val = ((GLMVec4Array *)self)->val;
	res->size = size;
	res->val = new glm::vec4[size];
	for (int i = 0; i < size; ++i) {
		res->val[i] = +val[i];
	}
	return (PyObject *)res;
}

PyNumberMethods GLMVec4Array_tp_as_number = {
	(binaryfunc)GLMVec4Array_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMVec4Array_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMVec4Array_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMVec4Array_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMVec4Array_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMVec4Array_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMVec4Array_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMVec4Array_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMVec4Array_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMVec4Array_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMVec4Array_sq_length(GLMVec4Array * self) {
	return N;
}

PyObject * GLMVec4Array_sq_item(GLMVec4Array * self, Py_ssize_t key) {
	if (key < self->size * N) {
		return PyFloat_FromDouble(self->val[key / N][key % N]);
	} else {
		return 0;
	}
}

int GLMVec4Array_sq_ass_item(GLMVec4Array * self, Py_ssize_t key, PyObject * value) {
	if (key < self->size * N) {
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

PySequenceMethods GLMVec4Array_tp_as_sequence = {
	(lenfunc)GLMVec4Array_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMVec4Array_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMVec4Array_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMVec4Array_bf_getbuffer(GLMVec4Array * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMVec4Array_tp_as_buffer = {
    (getbufferproc)GLMVec4Array_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMVec4Array_tp_meth_dot(GLMVec4Array * lhs, PyObject * args) {
	PyObject * rhs;
	int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	}

	if (Py_TYPE(rhs) == &GLMVec4Array_Type) {
		int lhs_size = ((GLMVec4Array *)lhs)->size;
		int rhs_size = ((GLMVec4Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec4 * lhs_val = ((GLMVec4Array *)lhs)->val;
		glm::vec4 * rhs_val = ((GLMVec4Array *)rhs)->val;
		PyObject * res = PyTuple_New(lhs_size);
		for (int i = 0; i < lhs_size; ++i) {
			PyTuple_SET_ITEM(res, i, PyFloat_FromDouble(glm::dot(lhs_val[i], rhs_val[i])));
		}
		return res;
	}
	return 0;
}


PyMethodDef GLMVec4Array_tp_methods[] = {
	{"dot", (PyCFunction)GLMVec4Array_tp_meth_dot, METH_VARARGS, 0},
	{0},
};

PyObject * GLMVec4Array_tp_get_length(GLMVec4Array * self, void * closure) {
	int size = ((GLMVec4Array *)self)->size;
	glm::vec4 * val = ((GLMVec4Array *)self)->val;
	PyObject * res = PyTuple_New(size);
	for (int i = 0; i < size; ++i) {
		PyTuple_SET_ITEM(res, i, PyFloat_FromDouble(glm::length(val[i])));
	}
	return res;
}

PyObject * GLMVec4Array_tp_get_normal(GLMVec4Array * self, void * closure) {
	GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
	int size = ((GLMVec4Array *)self)->size;
	res->size = size;
	res->val = new glm::vec4[res->size + 1];
	glm::vec4 * val = ((GLMVec4Array *)self)->val;
	for (int i = 0; i < size; ++i) {
		res->val[i] = glm::normalize(val[i]);
	}
	return (PyObject *)res;
}

PyObject * GLMVec4Array_tp_get_tup(GLMVec4Array * self, void * closure) {
	return GLMVec4Array_Tuple(self);
}

PyGetSetDef GLMVec4Array_tp_getseters[] = {
	{(char *)"length", (getter)GLMVec4Array_tp_get_length, 0, 0, 0},
	{(char *)"normal", (getter)GLMVec4Array_tp_get_normal, 0, 0, 0},
	{(char *)"tup", (getter)GLMVec4Array_tp_get_tup, 0, 0, 0},
	{0},
};

PyTypeObject GLMVec4Array_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.vec4Array", // tp_name
	sizeof(GLMVec4Array), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMVec4Array_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMVec4Array_tp_repr, // tp_repr
	&GLMVec4Array_tp_as_number, // tp_as_number
	&GLMVec4Array_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMVec4Array_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMVec4Array_tp_methods, // tp_methods
	0, // tp_members
	GLMVec4Array_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMVec4Array_tp_init, // tp_init
	0, // tp_alloc
	GLMVec4Array_tp_new, // tp_new
};

PyObject * GLMVec4Array_Tuple(GLMVec4Array * self) {
	int size = self->size;
	glm::vec4 * val = ((GLMVec4Array *)self)->val;

	PyObject * tuple = PyTuple_New(self->size * N);
	for (int i = 0; i < size; ++i) {
		PyTuple_SET_ITEM(tuple, i * N + 0, PyFloat_FromDouble(val[i][0]));
		PyTuple_SET_ITEM(tuple, i * N + 1, PyFloat_FromDouble(val[i][1]));
        PyTuple_SET_ITEM(tuple, i * N + 2, PyFloat_FromDouble(val[i][2]));
        PyTuple_SET_ITEM(tuple, i * N + 3, PyFloat_FromDouble(val[i][3]));
	}

	return tuple;
}

