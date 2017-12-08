#include "common.hpp"

#define N 2

PyObject * GLMVec2Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMVec2Array * self = (GLMVec2Array *)type->tp_alloc(type, 0);

	if (self) {
		self->val = 0;
	}

	return (PyObject *)self;
}

void GLMVec2Array_tp_dealloc(GLMVec2Array * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMVec2Array_tp_init(GLMVec2Array * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable;

    int arg_ok = PyArg_ParseTuple(args, "O", &iterable);

    if(!arg_ok){
        return -1;
    }

	if (Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) % N == 0) {
		int size = PyTuple_GET_SIZE(iterable) / N;
		self->val = new glm::vec2[size];
		self->size = size;

		for (int i = 0; i < size; ++i) {
			self->val[i][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 0));
			self->val[i][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 1));
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

	self->val = new glm::vec2[size];
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

PyObject * GLMVec2Array_tp_repr(GLMVec2Array * self) {
	PyObject * temp = GLMVec2Array_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMVec2Array_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec2Array_Type && Py_TYPE(rhs) == &GLMVec2Array_Type) {
		GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec2[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] + rhs_val[i];
		}
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec2Array_Type && Py_TYPE(rhs) == &GLMVec2Array_Type) {
		GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec2[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] - rhs_val[i];
		}
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec2Array_Type && Py_TYPE(rhs) == &GLMVec2Array_Type) {
		GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec2[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] * rhs_val[i];
		}
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec2Array_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
			int size = ((GLMVec2Array *)lhs)->size;
			glm::vec2 * val = ((GLMVec2Array *)lhs)->val;
			res->size = size;
			res->val = new glm::vec2[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = val[i] * rhs_float;
			}
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		glm::mat2 mat2_lhs = mat2_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
			int size = ((GLMVec2Array *)rhs)->size;
			glm::vec2 * val = ((GLMVec2Array *)rhs)->val;
			res->size = size;
			res->val = new glm::vec2[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = mat2_lhs * val[i];
			}
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec2Array_Type && Py_TYPE(rhs) == &GLMVec2Array_Type) {
		GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::vec2[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] / rhs_val[i];
		}
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec2Array_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
			int size = ((GLMVec2Array *)lhs)->size;
			glm::vec2 * val = ((GLMVec2Array *)lhs)->val;
			res->size = size;
			res->val = new glm::vec2[size];
			for (int i = 0; i < size; ++i) {
				res->val[i] = val[i] / rhs_float;
			}
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] += rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] -= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] *= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMVec2Array *)lhs)->size;
		glm::vec2 * val = ((GLMVec2Array *)lhs)->val;
		for (int i = 0; i < size; ++i) {
			val[i] *= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		for (int i = 0; i < lhs_size; ++i) {
			lhs_val[i] /= rhs_val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMVec2Array *)lhs)->size;
		glm::vec2 * val = ((GLMVec2Array *)lhs)->val;
		for (int i = 0; i < size; ++i) {
			val[i] /= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec2Array_nb_negative(GLMVec2Array * self) {
	GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
	int size = ((GLMVec2Array *)self)->size;
	glm::vec2 * val = ((GLMVec2Array *)self)->val;
	res->size = size;
	res->val = new glm::vec2[size];
	for (int i = 0; i < size; ++i) {
		res->val[i] = -val[i];
	}
	return (PyObject *)res;
}

PyObject * GLMVec2Array_nb_positive(GLMVec2Array * self) {
	GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
	int size = ((GLMVec2Array *)self)->size;
	glm::vec2 * val = ((GLMVec2Array *)self)->val;
	res->size = size;
	res->val = new glm::vec2[size];
	for (int i = 0; i < size; ++i) {
		res->val[i] = +val[i];
	}
	return (PyObject *)res;
}

PyNumberMethods GLMVec2Array_tp_as_number = {
	(binaryfunc)GLMVec2Array_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMVec2Array_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMVec2Array_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMVec2Array_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMVec2Array_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMVec2Array_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMVec2Array_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMVec2Array_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMVec2Array_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMVec2Array_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMVec2Array_sq_length(GLMVec2Array * self) {
	return N * self->size;
}

PyObject * GLMVec2Array_sq_item(GLMVec2Array * self, Py_ssize_t key) {
	if (key < self->size * N) {
		return PyFloat_FromDouble(self->val[key / N][key % N]);
	} else {
		return 0;
	}
}

int GLMVec2Array_sq_ass_item(GLMVec2Array * self, Py_ssize_t key, PyObject * value) {
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

PySequenceMethods GLMVec2Array_tp_as_sequence = {
	(lenfunc)GLMVec2Array_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMVec2Array_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMVec2Array_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMVec2Array_bf_getbuffer(GLMVec2Array * self, Py_buffer * view, int flags) {
	view->buf = (void *)self->val;
	view->len = sizeof(self->val[0]) * self->size;
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

PyBufferProcs GLMVec2Array_tp_as_buffer = {
	(getbufferproc)GLMVec2Array_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMVec2Array_tp_meth_dot(GLMVec2Array * lhs, PyObject * args) {
	PyObject * rhs;
	int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	}

	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		int lhs_size = ((GLMVec2Array *)lhs)->size;
		int rhs_size = ((GLMVec2Array *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::vec2 * lhs_val = ((GLMVec2Array *)lhs)->val;
		glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;
		
		GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
		res->size = lhs_size;
		res->val = new float[res->size + 1];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = glm::dot(lhs_val[i], rhs_val[i]);
		}
		return (PyObject *)res;
	}
	return 0;
}

PyMethodDef GLMVec2Array_tp_methods[] = {
	{"dot", (PyCFunction)GLMVec2Array_tp_meth_dot, METH_VARARGS, 0},
	{0},
};

PyObject * GLMVec2Array_tp_get_length(GLMVec2Array * self, void * closure) {
	int size = ((GLMVec2Array *)self)->size;
	glm::vec2 * val = ((GLMVec2Array *)self)->val;
	GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
	res->size = self->size;
	res->val = new float[res->size + 1];
	for (int i = 0; i < self->size; ++i) {
		res->val[i] = glm::length(self->val[i]);
	}
	return (PyObject *)res;
}

PyObject * GLMVec2Array_tp_get_normal(GLMVec2Array * self, void * closure) {
	GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
	
	int size = ((GLMVec2Array *)self)->size;
	res->size = size;
	res->val = new glm::vec2[res->size + 1];
	
	glm::vec2 * val = ((GLMVec2Array *)self)->val;
	for (int i = 0; i < size; ++i) {
		res->val[i] = glm::normalize(val[i]);
	}
	return (PyObject *)res;
}

PyObject * GLMVec2Array_tp_get_tup(GLMVec2Array * self, void * closure) {
	return GLMVec2Array_Tuple(self);
}

PyGetSetDef GLMVec2Array_tp_getseters[] = {
	{(char *)"length", (getter)GLMVec2Array_tp_get_length, 0, 0, 0},
	{(char *)"normal", (getter)GLMVec2Array_tp_get_normal, 0, 0, 0},
	{(char *)"tup", (getter)GLMVec2Array_tp_get_tup, 0, 0, 0},
	{0},
};

PyTypeObject GLMVec2Array_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Vec2Array", // tp_name
	sizeof(GLMVec2Array), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMVec2Array_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMVec2Array_tp_repr, // tp_repr
	&GLMVec2Array_tp_as_number, // tp_as_number
	&GLMVec2Array_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMVec2Array_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMVec2Array_tp_methods, // tp_methods
	0, // tp_members
	GLMVec2Array_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMVec2Array_tp_init, // tp_init
	0, // tp_alloc
	GLMVec2Array_tp_new, // tp_new
};

PyObject * GLMVec2Array_Tuple(GLMVec2Array * self) {
	int size = self->size;
	glm::vec2 * val = ((GLMVec2Array *)self)->val;

	PyObject * tuple = PyTuple_New(self->size * N);
	for (int i = 0; i < size; ++i) {
		PyTuple_SET_ITEM(tuple, i * N + 0, PyFloat_FromDouble(val[i][0]));
		PyTuple_SET_ITEM(tuple, i * N + 1, PyFloat_FromDouble(val[i][1]));
	}

	return tuple;
}
