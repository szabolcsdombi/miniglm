#include "common.hpp"

#define N 3

PyObject * GLMVec3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMVec3 * self = (GLMVec3 *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void GLMVec3_tp_dealloc(GLMVec3 * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMVec3_tp_init(GLMVec3 * self, PyObject * args, PyObject * kwargs) {
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

		if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	self->val = vec3_from_iterable(iterable);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMVec3_tp_repr(GLMVec3 * self) {
	PyObject * temp = GLMVec3_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMVec3_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec3_Type && Py_TYPE(rhs) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = ((GLMVec3 *)lhs)->val + ((GLMVec3 *)rhs)->val;
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec3_Type && Py_TYPE(rhs) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = ((GLMVec3 *)lhs)->val - ((GLMVec3 *)rhs)->val;
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec3_Type && Py_TYPE(rhs) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = ((GLMVec3 *)lhs)->val * ((GLMVec3 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec3_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = ((GLMVec3 *)lhs)->val * rhs_float;
			return (PyObject *)res;
		}
	}

	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		glm::mat3 mat3_lhs = mat3_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = mat3_lhs * ((GLMVec3 *)rhs)->val;
			return (PyObject *)res;
		}

		glm::quat quat_lhs = quat_from_iterable(lhs);
		if (!PyErr_Occurred()) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = quat_lhs * ((GLMVec3 *)rhs)->val;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMVec3_Type && Py_TYPE(rhs) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = ((GLMVec3 *)lhs)->val / ((GLMVec3 *)rhs)->val;
		return (PyObject *)res;
	}

	if (Py_TYPE(lhs) == &GLMVec3_Type) {
		float rhs_float = (float)PyFloat_AsDouble(rhs);
		if (!PyErr_Occurred()) {
			GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
			res->val = ((GLMVec3 *)lhs)->val / rhs_float;
			return (PyObject *)res;
		}
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		((GLMVec3 *)lhs)->val += ((GLMVec3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		((GLMVec3 *)lhs)->val -= ((GLMVec3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		((GLMVec3 *)lhs)->val *= ((GLMVec3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMVec3 *)lhs)->val *= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		((GLMVec3 *)lhs)->val /= ((GLMVec3 *)rhs)->val;
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		((GLMVec3 *)lhs)->val /= rhs_float;
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMVec3_nb_negative(GLMVec3 * self) {
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	res->val = -((GLMVec3 *)self)->val;
	return (PyObject *)res;
}

PyObject * GLMVec3_nb_positive(GLMVec3 * self) {
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	res->val = +((GLMVec3 *)self)->val;
	return (PyObject *)res;
}

PyNumberMethods GLMVec3_tp_as_number = {
	(binaryfunc)GLMVec3_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMVec3_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMVec3_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMVec3_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMVec3_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMVec3_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMVec3_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMVec3_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMVec3_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMVec3_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMVec3_sq_length(GLMVec3 * self) {
	return N;
}

PyObject * GLMVec3_sq_item(GLMVec3 * self, Py_ssize_t key) {
	if (key < N) {
		return PyFloat_FromDouble(self->val[key]);
	} else {
		return 0;
	}
}

int GLMVec3_sq_ass_item(GLMVec3 * self, Py_ssize_t key, PyObject * value) {
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

PySequenceMethods GLMVec3_tp_as_sequence = {
	(lenfunc)GLMVec3_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMVec3_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMVec3_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMVec3_bf_getbuffer(GLMVec3 * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMVec3_tp_as_buffer = {
	(getbufferproc)GLMVec3_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMVec3_tp_meth_dot(GLMVec3 * lhs, PyObject * args) {
	PyObject * rhs;
	
	int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	}
	
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		return PyFloat_FromDouble(glm::dot(lhs->val, ((GLMVec3 *)rhs)->val));
	}
	return 0;
}

PyObject * GLMVec3_tp_meth_cross(GLMVec3 * lhs, PyObject * args) {
	PyObject * rhs;
	
	int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	}
	if (Py_TYPE(rhs) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = glm::cross(lhs->val, ((GLMVec3 *)rhs)->val);
		return (PyObject *)res;
	}
	return 0;
}

PyObject * GLMVec3_tp_meth_reflect(GLMVec3 * self, PyObject * args) {
	PyObject * norm;
	
	int arg_ok = PyArg_ParseTuple(args, "O", &norm);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	};
	if (Py_TYPE(norm) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = glm::reflect(self->val, ((GLMVec3 *)norm)->val);
		return (PyObject *)res;
	}
	return 0;
}

PyObject * GLMVec3_tp_meth_refract(GLMVec3 * self, PyObject * args) {
	PyObject * norm;
	
	int arg_ok = PyArg_ParseTuple(args, "O", &norm);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameter!");
		return 0;
	}

	float eta = (float)PyFloat_AsDouble(PyTuple_GetItem(args, 1));
	if (PyErr_Occurred()) {
		return 0;
	}
	if (Py_TYPE(norm) == &GLMVec3_Type) {
		GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
		res->val = glm::refract(self->val, ((GLMVec3 *)norm)->val, eta);
		return (PyObject *)res;
	}
	return 0;
}


PyObject * GLMVec3_tp_meth_out(GLMVec3 * lhs, PyObject * args){
	PyObject * rhs;
	int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

	if(!arg_ok){
		PyErr_Format(PyExc_Exception, "Missing parameters!");
		return 0;
	}

	if(Py_TYPE(rhs) == &GLMVec3_Type){
		
		GLMMat3 * res = (GLMMat3 *)GLMMat2_tp_new(&GLMMat3_Type, 0, 0);

		res->val[0][0] = ((GLMVec3 *)lhs)->val[0] * ((GLMVec3 *)rhs)->val[0];
		res->val[0][1] = ((GLMVec3 *)lhs)->val[0] * ((GLMVec3 *)rhs)->val[1];
		res->val[0][2] = ((GLMVec3 *)lhs)->val[0] * ((GLMVec3 *)rhs)->val[2];
		res->val[1][0] = ((GLMVec3 *)lhs)->val[1] * ((GLMVec3 *)rhs)->val[0];
		res->val[1][1] = ((GLMVec3 *)lhs)->val[1] * ((GLMVec3 *)rhs)->val[1];
		res->val[1][2] = ((GLMVec3 *)lhs)->val[1] * ((GLMVec3 *)rhs)->val[2];
		res->val[2][0] = ((GLMVec3 *)lhs)->val[2] * ((GLMVec3 *)rhs)->val[0];
		res->val[2][1] = ((GLMVec3 *)lhs)->val[2] * ((GLMVec3 *)rhs)->val[1];
		res->val[2][2] = ((GLMVec3 *)lhs)->val[2] * ((GLMVec3 *)rhs)->val[2];
		
		return (PyObject *)res;

	}

	return 0;
}


PyMethodDef GLMVec3_tp_methods[] = {
	{"dot", (PyCFunction)GLMVec3_tp_meth_dot, METH_VARARGS, 0},
	{"out", (PyCFunction)GLMVec3_tp_meth_out, METH_VARARGS, 0},
	{"cross", (PyCFunction)GLMVec3_tp_meth_cross, METH_VARARGS, 0},
	{"reflect", (PyCFunction)GLMVec3_tp_meth_reflect, METH_VARARGS, 0},
	{"refract", (PyCFunction)GLMVec3_tp_meth_refract, METH_VARARGS, 0},
	{0},
};

PyObject * GLMVec3_tp_get_length(GLMVec3 * self, void * closure) {
	return PyFloat_FromDouble(glm::length(self->val));
}

PyObject * GLMVec3_tp_get_normal(GLMVec3 * self, void * closure) {
	GLMVec3 * res = (GLMVec3 *)GLMVec3_tp_new(&GLMVec3_Type, 0, 0);
	res->val = glm::normalize(self->val);
	return (PyObject *)res;
}

PyObject * GLMVec3_tp_get_tup(GLMVec3 * self, void * closure) {
	return GLMVec3_Tuple(self);
}

PyObject * GLMVec3_tp_get_data(GLMVec3 * self, void * closure) {
	PyObject * res = PyBytes_FromStringAndSize(0, sizeof(self->val));
	memcpy(PyBytes_AS_STRING(res), &self->val, sizeof(self->val));
	return res;
}

PyGetSetDef GLMVec3_tp_getseters[] = {
	{(char *)"length", (getter)GLMVec3_tp_get_length, 0, 0, 0},
	{(char *)"normal", (getter)GLMVec3_tp_get_normal, 0, 0, 0},
	{(char *)"tup", (getter)GLMVec3_tp_get_tup, 0, 0, 0},
	{(char *)"data", (getter)GLMVec3_tp_get_data, 0, 0, 0},
	{0},
};

PyTypeObject GLMVec3_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Vec3", // tp_name
	sizeof(GLMVec3), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMVec3_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMVec3_tp_repr, // tp_repr
	&GLMVec3_tp_as_number, // tp_as_number
	&GLMVec3_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMVec3_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMVec3_tp_methods, // tp_methods
	0, // tp_members
	GLMVec3_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMVec3_tp_init, // tp_init
	0, // tp_alloc
	GLMVec3_tp_new, // tp_new
};

PyObject * GLMVec3_Tuple(GLMVec3 * self) {
	PyObject * tuple = PyTuple_New(N);
	PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(self->val[0]));
	PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(self->val[1]));
	PyTuple_SET_ITEM(tuple, 2, PyFloat_FromDouble(self->val[2]));
	return tuple;
}
