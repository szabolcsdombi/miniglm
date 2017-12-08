#include "common.hpp"

#define N 4

PyObject * GLMQuatArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs){
    GLMQuatArray * self = (GLMQuatArray *)type->tp_alloc(type, 0);

    if(self){
        self->val = 0;
    }

    return (PyObject *)self;
}

void GLMQuatArray_tp_dealloc(GLMQuatArray * self){
    Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMQuatArray_tp_init(GLMQuatArray * self, PyObject * args, PyObject * kwargs){
    PyObject * iterable;

    int arg_ok = PyArg_ParseTuple(args, "O", &iterable);

    if(!arg_ok){
        return -1;
    }

    if(Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) % N == 0){
        int size = PyTuple_GET_SIZE(iterable) / N;
        self->val = new glm::quat[size + 1];
        self->size = size;

        for(int i = 0; i < size; i++){
            self->val[i][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 0));
			self->val[i][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 1));
            self->val[i][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 2));
            self->val[i][3] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 3));
        }

        if(PyErr_Occurred()){
            return -1;
        }

        return 0;
    }

    PyObject * iterator = PyObject_GetIter(iterable);
    int size = PyObject_Size(iterable);

    if(!iterator || size < 0 || size % N){
        PyErr_Format(PyExc_Exception, "not iterable or wrong size");
        return 0;
    }

    size = size / N;
    
    self->val = new glm::quat[size + 1];
    for(int k = 0; k < size; ++k){
        for(int i = 0; i < N; i++){
            PyObject * item = PyIter_Next(iterator);
            self->val[k][i] = (float)PyFloat_AsDouble(item);
            Py_DECREF(item);
        }
    }

    Py_DECREF(iterator);

    if(PyErr_Occurred()){
        return -1;
    }

    return 0;
}

PyObject * GLMQuatArray_tp_repr(GLMQuatArray * self) {
	PyObject * temp = GLMQuatArray_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}


PyObject * GLMQuatArray_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMQuatArray_Type && Py_TYPE(rhs) == &GLMQuatArray_Type) {
		GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
		int lhs_size = ((GLMQuatArray *)lhs)->size;
		int rhs_size = ((GLMQuatArray *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		glm::quat * lhs_val = ((GLMQuatArray *)lhs)->val;
		glm::quat * rhs_val = ((GLMQuatArray *)rhs)->val;
		res->size = lhs_size;
		res->val = new glm::quat[lhs_size];
		for (int i = 0; i < lhs_size; ++i) {
			res->val[i] = lhs_val[i] + rhs_val[i];
		}
		return (PyObject *)res;
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_nb_multiply(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMQuatArray_Type && Py_TYPE(rhs) == &GLMQuatArray_Type){
        int lhs_size = ((GLMQuatArray *)lhs)->size;
        int rhs_size = ((GLMQuatArray *)rhs)->size;
        
        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }
        
        glm::quat * lhs_val = ((GLMQuatArray *)lhs)->val;
        glm::quat * rhs_val = ((GLMQuatArray *)rhs)->val;

        GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
        res->size = lhs_size;
        res->val = new glm::quat[res->size + 1];
        
        for(int i = 0; i < lhs_size; ++i){
            res->val[i] = lhs_val[i] * rhs_val[i];
        }

        return (PyObject *)res;
    }

    if(Py_TYPE(lhs) == &GLMQuatArray_Type){
        if(Py_TYPE(rhs) == &GLMVec3Array_Type){
            int lhs_size = ((GLMQuatArray *)lhs)->size;
            int rhs_size = ((GLMVec3Array *)rhs)->size;

            if(lhs_size != rhs_size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            glm::quat * lhs_val = ((GLMQuatArray *)lhs)->val;
            glm::vec3 * rhs_val = ((GLMVec3Array *)rhs)->val;

            GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
            res->size = lhs_size;
            res->val = new glm::vec3[res->size + 1];

            for(int i = 0; i < lhs_size; ++i){
                res->val[i] = lhs_val[i] * rhs_val[i];
            }

            return (PyObject *)res;
        }

        if(Py_TYPE(rhs) == &GLMMat3Array_Type){
            if(((GLMQuatArray *)lhs)->size != ((GLMMat3Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }
            int size = ((GLMQuatArray *)lhs)->size;

            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat3[res->size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = glm::mat3_cast(((GLMQuatArray *)lhs)->val[i]) * ((GLMMat3Array *)rhs)->val[i];
            }
            
            return (PyObject *)res;

        }

        float rhs_float = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            int size = ((GLMQuatArray *)lhs)->size;
            GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
            res->size = size;
            res->val = new glm::quat[res->size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMQuatArray *)lhs)->val[i] * rhs_float;
            }

            return (PyObject *)res;
        }
    }
    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_nb_true_divide(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMQuatArray_Type){
        float rhs_float = PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            int size = ((GLMQuatArray *)lhs)->size;
            GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
            res->size = size;
            res->val = new glm::quat[res->size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMQuatArray *)lhs)->val[i] / rhs_float;
            }

            return (PyObject *)res;
        }
    }
    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_nb_inplace_multiply(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(rhs) == &GLMQuatArray_Type){
        int size = ((GLMQuatArray *)lhs)->size;
        
        if(size != ((GLMQuatArray *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        for(int i = 0; i < size; ++i){
            ((GLMQuatArray *)lhs)->val[i] *= ((GLMQuatArray *)rhs)->val[i];
        }

        return lhs;
    }

    float rhs_float = (float)PyFloat_AsDouble(rhs);
    if(!PyErr_Occurred()){
        int size = ((GLMQuatArray *)lhs)->size;
        
        for(int i = 0; i < size; ++i){
            ((GLMQuatArray *)lhs)->val[i] *= rhs_float;
        }

        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs){
    float rhs_float = (float)PyFloat_AsDouble(rhs);
    if(!PyErr_Occurred()){
        int size = ((GLMQuatArray *)lhs)->size;

        for(int i = 0; i < size; ++i){
            ((GLMQuatArray *)lhs)->val[i] /= rhs_float;
        }

        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_nb_negative(GLMQuatArray * self){
    int size = self->size;
    GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
    res->size = size;
    res->val = new glm::quat[res->size + 1];
    for(int i = 0; i < size; ++i){
        res->val[i] = -(self->val[i]);
    }

    return (PyObject *)res;
}

PyObject * GLMQuatArray_nb_positive(GLMQuatArray * self){
    int size = self->size;
    GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
    res->size = size;
    res->val = new glm::quat[res->size + 1];
    for(int i = 0; i < size; ++i){
        res->val[i] = +(self->val[i]);
    }

    return (PyObject *)res;
}

PyNumberMethods GLMQuatArray_tp_as_number = {
	0, // binaryfunc nb_add;
	0, // binaryfunc nb_subtract;
	(binaryfunc)GLMQuatArray_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMQuatArray_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMQuatArray_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMQuatArray_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMQuatArray_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMQuatArray_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMQuatArray_sq_length(GLMQuatArray * self){
    return self->size * N;
}

PyObject * GLMQuatArray_sq_item(GLMQuatArray * self, Py_ssize_t key){
    if(key < N * self->size){
        return PyFloat_FromDouble(self->val[key / N][key % N]);
    }else{
        return 0;
    }
}

PyObject * GLMQuatArray_sq_ass_item(GLMQuatArray * self, Py_ssize_t key, PyObject * val){
    if(key < self->size * N){
        float value = (float)PyFloat_AsDouble(val);
        if(PyErr_Occurred()){
            return (PyObject * )(-1);
        }        
        self->val[key / N][key % N] = value;
        return (PyObject *) 0;
    }else{
        return (PyObject *) -1;
    }
}

PySequenceMethods GLMQuatArray_tp_as_sequence = {
	(lenfunc)GLMQuatArray_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMQuatArray_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMQuatArray_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMQuatArray_bf_getbuffer(GLMQuatArray * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMQuatArray_tp_as_buffer = {
    (getbufferproc)GLMQuatArray_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMQuatArray_tp_meth_dot(GLMQuatArray * lhs, PyObject * args){
    PyObject * rhs;

    int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

    if(!arg_ok){
        return 0;
    }

    if(Py_TYPE(rhs) == &GLMQuatArray_Type){
        if(lhs->size != ((GLMQuatArray *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return (PyObject *)0;
        }
        int size = lhs->size;
        
        GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
		res->size = size;
		res->val = new float[res->size + 1];
		for (int i = 0; i < size; ++i) {
			res->val[i] = glm::dot(((GLMQuatArray *)lhs)->val[i], ((GLMQuatArray *)rhs)->val[i]);
		}

		return (PyObject *)res;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_tp_meth_cross(GLMQuatArray * lhs, PyObject * args){
    PyObject * rhs;

    int arg_ok = PyArg_ParseTuple(args, "O", &rhs);

    if(!arg_ok){
        return 0;
    }

    if(Py_TYPE(rhs) == &GLMQuatArray_Type){
        if(lhs->size != ((GLMQuatArray *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return (PyObject *)0;
        }

        int size = lhs->size;
        GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
        res->size = size;
        res->val = new glm::quat[res->size + 1];

        for(int i = 0; i < size; ++i){
            res->val[i] = glm::cross(lhs->val[i], ((GLMQuatArray *)rhs)->val[i]);
        }
        return (PyObject *)res;
    }
    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMQuatArray_tp_meth_lerp(GLMQuatArray * lhs, PyObject * args){
    PyObject * rhs, * c;

    int arg_ok = PyArg_ParseTuple(args, "OO", &rhs, &c);

    if(!arg_ok){
        return 0;
    }

    float coef = (float)PyFloat_AsDouble(c);
    if(PyErr_Occurred()){
        return (PyObject *)0;
    }
    if(Py_TYPE(rhs) == &GLMQuatArray_Type){
        if(lhs->size != ((GLMQuatArray *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return (PyObject *)0;
        }

        int size = lhs->size;
        GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
        res->size = size;
        res->val = new glm::quat[res->size + 1];

        for(int i = 0; i < size; ++i){
            res->val[i] = glm::lerp(lhs->val[i], ((GLMQuatArray *)rhs)->val[i], coef);
        }

        return (PyObject *)res;
    }
    return 0;
}

PyObject * GLMQuatArray_tp_meth_slerp(GLMQuatArray * lhs, PyObject * args){
    PyObject * rhs, * c;

    int arg_ok = PyArg_ParseTuple(args, "OO", &rhs, &c);

    if(!arg_ok){
        return 0;
    }

    float coef = (float)PyFloat_AsDouble(c);
    if(PyErr_Occurred()){
        return (PyObject *)0;
    }
    if(Py_TYPE(rhs) == &GLMQuatArray_Type){
        if(lhs->size != ((GLMQuatArray *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return (PyObject *)0;
        }

        int size = lhs->size;
        GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
        res->size = size;
        res->val = new glm::quat[res->size + 1];

        for(int i = 0; i < size; ++i){
            res->val[i] = glm::slerp(lhs->val[i], ((GLMQuatArray *)rhs)->val[i], coef);
        }

        return (PyObject *)res;
    }
    return 0;
}

PyMethodDef GLMQuatArray_tp_methods[] = {
	{"dot", (PyCFunction)GLMQuatArray_tp_meth_dot, METH_VARARGS, 0},
	{"cross", (PyCFunction)GLMQuatArray_tp_meth_cross, METH_VARARGS, 0},
	{"slerp", (PyCFunction)GLMQuatArray_tp_meth_slerp, METH_VARARGS, 0},
	{"lerp", (PyCFunction)GLMQuatArray_tp_meth_lerp, METH_VARARGS, 0},
	{0},
};

PyObject * GLMQuatArray_tp_get_conj(GLMQuatArray * self, void * closure){
    int size = self->size;
    GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
    res->size = size;
    res->val = new glm::quat[res->size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::conjugate(self->val[i]);
    }

    return (PyObject *)res;
    
}

PyObject * GLMQuatArray_tp_get_inv(GLMQuatArray * self, void * closure){
    int size = self->size;
    GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
    res->size = size;
    res->val = new glm::quat[res->size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::inverse(self->val[i]);
    }

    return (PyObject *)res;    
}

PyObject * GLMQuatArray_tp_get_length(GLMQuatArray * self, void * closure){   
    GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
	res->size = self->size;
	res->val = new float[res->size + 1];
	for (int i = 0; i < self->size; ++i) {
		res->val[i] = glm::length(self->val[i]);
	}
	return (PyObject *)res;
}

PyObject * GLMQuatArray_tp_get_normal(GLMQuatArray * self, void * closure){
    int size = self->size;
    GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
    res->size = size;
    res->val = new glm::quat[res->size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::normalize(self->val[i]);
    }

    return (PyObject *)res;    
}

PyObject * GLMQuatArray_tp_get_axis(GLMQuatArray * self, void * closure){
    int size = self->size;
    GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
    res->size = size;
    res->val = new glm::vec3[res->size + 1];

    for(int i = 0; i < size; ++i){
        float s = (float)(sqrt(1.0 - self->val[i].w * self->val[i].w));
        res->val[i] = glm::vec3(self->val[i].x / s, self->val[i].y / s, self->val[i].z / s);
    }

    return (PyObject *)res;
}

PyObject * GLMQuatArray_tp_get_angle(GLMQuatArray * self, void * closure){
    int size = self->size;
    GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
    res->size = size;
    res->val = new float[size + 1];
    
    for(int i = 0; i < size; ++i){
        res->val[i] = 2.0 * acos(self->val[i].w);
    }

    return (PyObject *)res;
}

PyObject * GLMQuatArray_tp_get_tup(GLMQuatArray * self, void * closure){
    return GLMQuatArray_Tuple(self);
}

PyGetSetDef GLMQuatArray_tp_getseters[] = {
	{(char *)"length", (getter)GLMQuatArray_tp_get_length, 0, 0, 0},
	{(char *)"normal", (getter)GLMQuatArray_tp_get_normal, 0, 0, 0},
	{(char *)"conj", (getter)GLMQuatArray_tp_get_conj, 0, 0, 0},
	{(char *)"inv", (getter)GLMQuatArray_tp_get_inv, 0, 0, 0},
	{(char *)"axis", (getter)GLMQuatArray_tp_get_axis, 0, 0, 0},
	{(char *)"angle", (getter)GLMQuatArray_tp_get_angle, 0, 0, 0},
	{(char *)"tup", (getter)GLMQuatArray_tp_get_tup, 0, 0, 0},
	{0},
};

PyTypeObject GLMQuatArray_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Quat", // tp_name
	sizeof(GLMQuat), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMQuatArray_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMQuatArray_tp_repr, // tp_repr
	&GLMQuatArray_tp_as_number, // tp_as_number
	&GLMQuatArray_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMQuatArray_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMQuatArray_tp_methods, // tp_methods
	0, // tp_members
	GLMQuatArray_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMQuatArray_tp_init, // tp_init
	0, // tp_alloc
	GLMQuatArray_tp_new, // tp_new
};

PyObject * GLMQuatArray_Tuple(GLMQuatArray * self){
    int size = self->size;
    PyObject * res = PyTuple_New(size * N);

    for(int i = 0; i < size; ++i){
        PyTuple_SET_ITEM(res, i * N + 0, PyFloat_FromDouble(self->val[i][0]));
        PyTuple_SET_ITEM(res, i * N + 1, PyFloat_FromDouble(self->val[i][1]));
        PyTuple_SET_ITEM(res, i * N + 2, PyFloat_FromDouble(self->val[i][2]));
        PyTuple_SET_ITEM(res, i * N + 3, PyFloat_FromDouble(self->val[i][3]));
    }

    return res;
}