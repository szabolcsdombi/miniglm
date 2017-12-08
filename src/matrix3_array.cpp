#include "common.hpp"

#define N 3

PyObject * GLMMat3Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs){
    GLMMat3Array * self = (GLMMat3Array *)type->tp_alloc(type, 0);

    if(self){
        self->val = 0;
    }

    return (PyObject *)self;
}

void GLMMat3Array_tp_dealloc(GLMMat3Array * self){
    Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMMat3Array_tp_init(GLMMat3Array * self, PyObject * args, PyObject * kwargs){
    PyObject * iterable;

    int arg_ok = PyArg_ParseTuple(args, "O", &iterable);

    if(!arg_ok){
        return -1;
    }
    
    if(Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) % (N * N) == 0){
        self->size = PyTuple_GET_SIZE(iterable) / (N * N);
        self->val = new glm::mat3[self->size + 1];

        for(int i = 0; i < self->size; ++i){
            self->val[i][0][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 0));
            self->val[i][0][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 1));
            self->val[i][0][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 2));
            self->val[i][1][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 3));
            self->val[i][1][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 4));
            self->val[i][1][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 5));
            self->val[i][2][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 6));
            self->val[i][2][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 7));
            self->val[i][2][2] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N * N + 8));
        }

        if(PyErr_Occurred()){
            return -1;
        }
        return 0;
    }

    PyObject * iterator = PyObject_GetIter(iterable);
    int size = PyObject_Size(iterable);

    if(!iterator || size < 0 || size % (N * N)){
        PyErr_Format(PyExc_Exception, "not iterable or wrong size");
        return 0;
    }

    self->size = size / (N * N);
    self->val = new glm::mat3[self->size + 1];

    for(int k = 0; k < self->size; ++k){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; j++){
                PyObject * item = PyIter_Next(iterator);
                self->val[k][i][j] = (float)PyFloat_AsDouble(item);
                Py_DECREF(item);
            }
        }
    }

    Py_DECREF(iterator);

    if(PyErr_Occurred()){
        return -1;
    }

    return 0;

}

PyObject * GLMMat3Array_tp_repr(GLMMat3Array * self){
    PyObject * temp = GLMMat3Array_Tuple(self);
    PyObject * res = PyObject_Repr(temp);
    Py_DECREF(temp);
    return (PyObject *)res;
}

PyObject * GLMMat3Array_nb_add(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMMat3Array_Type && Py_TYPE(rhs) == &GLMMat3Array_Type){
        int lhs_size = ((GLMMat3Array *)lhs)->size;
        int rhs_size = ((GLMMat3Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
        res->size = lhs_size;
        res->val = new glm::mat3[res->size + 1];

        glm::mat3 * lhs_val = ((GLMMat3Array *)lhs)->val;
        glm::mat3 * rhs_val = ((GLMMat3Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] + rhs_val[i];
        }
        
        return (PyObject *)res;
    }
    
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_subtract(PyObject * lhs, PyObject * rhs){
     if(Py_TYPE(lhs) == &GLMMat3Array_Type && Py_TYPE(rhs) == &GLMMat3Array_Type){
        int lhs_size = ((GLMMat3Array *)lhs)->size;
        int rhs_size = ((GLMMat3Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
        res->size = lhs_size;
        res->val = new glm::mat3[res->size + 1];

        glm::mat3 * lhs_val = ((GLMMat3Array *)lhs)->val;
        glm::mat3 * rhs_val = ((GLMMat3Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] - rhs_val[i];
        }
        
        return (PyObject *)res;
    }
    
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_multiply(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMMat3Array_Type && Py_TYPE(rhs) == &GLMMat3Array_Type){
        int lhs_size = ((GLMMat3Array *)lhs)->size;
        int rhs_size = ((GLMMat3Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
        res->size = lhs_size;
        res->val = new glm::mat3[res->size + 1];

        glm::mat3 * lhs_val = ((GLMMat3Array *)lhs)->val;
        glm::mat3 * rhs_val = ((GLMMat3Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] * rhs_val[i];
        }
        
        return (PyObject *)res;
    }

    if(Py_TYPE(lhs) == &GLMMat3Array_Type){
        if(Py_TYPE(rhs) == &GLMVec3Array_Type){
            int lhs_size = ((GLMMat3Array *)lhs)->size;
            int rhs_size = ((GLMVec3Array *)rhs)->size;

            if(lhs_size != rhs_size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);;
            res->size = lhs_size;
            res->val = new glm::vec3[res->size + 1];

            glm::mat3 * lhs_val = ((GLMMat3Array *)lhs)->val;
            glm::vec3 * rhs_val = ((GLMVec3Array *)rhs)->val;

            for(int i = 0; i < res->size; ++i){
                res->val[i] = lhs_val[i] * rhs_val[i];
            }

            return (PyObject *)res;
   
        }
        
        float scalar = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            int lhs_size = ((GLMMat3Array*)lhs)->size;
            res->size = lhs_size;
            res->val = new glm::mat3[lhs_size + 1];
            
            for(int i = 0; i < lhs_size; ++i){
                res->val[i] = ((GLMMat3Array *)lhs)->val[i] * scalar;
            }

            return (PyObject *)res;

        }
    }

    if(Py_TYPE(rhs) == &GLMMat3Array_Type){
        float lhs_float = (float)PyFloat_AsDouble(lhs);
        if(!PyErr_Occurred()){            
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            int rhs_size = ((GLMMat3Array *)rhs)->size;
            res->size = rhs_size;
            res->val = new glm::mat3[rhs_size + 1];
            
            for(int i = 0; i < rhs_size; ++i){
                res->val[i] = lhs_float * ((GLMMat3Array *)rhs)->val[i];
            }

            return (PyObject *)res;
        }
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}


PyObject * GLMMat3Array_nb_true_divide(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMMat3Array_Type){
        float rhs_float = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            int lhs_size = ((GLMMat3Array *)lhs)->size;
            res->size = lhs_size;
            res->val = new glm::mat3[lhs_size + 1];

            for(int i = 0; i < lhs_size; ++i){
                res->val[i] = ((GLMMat3Array *)lhs)->val[i] / rhs_float;
            }

            return (PyObject *)res;
        }
    }
    
    if(Py_TYPE(rhs) == &GLMMat3Array_Type){
        float lhs_float = (float)PyFloat_AsDouble(lhs);
        if(!PyErr_Occurred()){
            
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            int rhs_size = ((GLMMat3Array *)rhs)->size;
            res->size = rhs_size;
            res->val = new glm::mat3[rhs_size + 1];

            for(int i = 0; i < rhs_size; ++i){
                res->val[i] = ((GLMMat3Array *)rhs)->val[i] / lhs_float;
            }

            return (PyObject *)res;
        }
    }
    
    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;    
}


PyObject * GLMMat3Array_nb_inplace_add(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(rhs) == &GLMMat3Array_Type){
        if(((GLMMat3Array *)lhs)->size != ((GLMMat3Array *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        for(int i = 0; i < ((GLMMat3Array *)lhs)->size; ++i){
            ((GLMMat3Array *)lhs)->val[i] += ((GLMMat3Array *)rhs)->val[i];
        }

        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_inplace_subtract(PyObject * lhs, PyObject * rhs){
    if (Py_TYPE(rhs) == &GLMMat3Array_Type) {
        if(((GLMMat3Array *)lhs)->size != ((GLMMat3Array *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        int lhs_size = ((GLMMat3Array *)lhs)->size;
        
        for (int i = 0; i < lhs_size; ++i) {
            ((GLMMat3Array *)lhs)->val[i] -= ((GLMMat3Array *)rhs)->val[i];
        }

        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_inplace_multiply(PyObject * lhs, PyObject * rhs){
    if (Py_TYPE(rhs) == &GLMMat3Array_Type){
        if(((GLMMat3Array *)lhs)->size != ((GLMMat3Array *)rhs)->size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        int lhs_size = ((GLMMat3Array *)lhs)->size;
        
        for (int i = 0; i < lhs_size; ++i) {
            ((GLMMat3Array *)lhs)->val[i] *= ((GLMMat3Array *)rhs)->val[i];
        }

        return lhs;
    }

    float rhs_float = (float)PyFloat_AsDouble(rhs);
    if(!PyErr_Occurred()){
        int lhs_size = ((GLMMat3Array *)lhs)->size;
        for(int i = 0; i < lhs_size; ++i){
            ((GLMMat3Array *)lhs)->val[i] *= rhs_float;
        }
        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs){
    float rhs_float = (float)PyFloat_AsDouble(rhs);
    if(!PyErr_Occurred()){
        int lhs_size = ((GLMMat3Array *)lhs)->size;
        for(int i = 0; i < lhs_size; ++i){
            ((GLMMat3Array *)lhs)->val[i] /= rhs_float;
        }

        return lhs;
    }

    PyErr_Clear();
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat3Array_nb_negative(PyObject * self){
    GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
    res->size = ((GLMMat3Array *)self)->size;
    res->val = new glm::mat3[res->size + 1];
    int self_size = res->size;

    for(int i = 0; i < self_size; ++i){
        res->val[i] = -((GLMMat3Array *)self)->val[i];
    }

    return (PyObject *)res;
}

PyObject * GLMMat3Array_nb_positive(PyObject * self){
    GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
    res->size = ((GLMMat3Array *)self)->size;
    res->val = new glm::mat3[res->size + 1];
    int self_size = res->size;

    for(int i = 0; i < self_size; ++i){
        res->val[i] = +((GLMMat3Array *)self)->val[i];
    }

    return (PyObject *)res;
}

PyNumberMethods GLMMat3Array_tp_as_number = {
	(binaryfunc)GLMMat3Array_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMMat3Array_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMMat3Array_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMMat3Array_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMMat3Array_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMMat3Array_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMMat3Array_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMMat3Array_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMMat3Array_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMMat3Array_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMMat3Array_sq_length(GLMMat3Array * self){
    return self->size * N * N;
}

PyObject * GLMMat3Array_sq_item(GLMMat3Array * self, Py_ssize_t key){
    if(key < self->size * N * N){
        int i = key / (N * N);
        int k = key % (N * N);
        return PyFloat_FromDouble(self->val[i][k / N][k % N]);
    }
    return 0;
}

PyObject * GLMMat3Array_sq_ass_item(GLMMat3Array * self, Py_ssize_t key, PyObject * value){
    if(key < self->size * N * N){
        int i = key / (N * N);
        int k = key % (N * N);
        float val = PyFloat_AsDouble(value);
        if(PyErr_Occurred()){
            return (PyObject *) -1;
        }
        self->val[i][k / N][k % N] = val;
        return 0;
    }
    return (PyObject *) -1;
}

PySequenceMethods GLMMat3Array_tp_as_sequence = {
	(lenfunc)GLMMat3Array_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMMat3Array_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMMat3Array_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMMat3Array_bf_getbuffer(GLMMat3Array * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMMat3Array_tp_as_buffer = {
    (getbufferproc)GLMMat3Array_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};

PyObject * GLMMat3Array_tp_meth_row(GLMMat2 * self, PyObject * args){
    int id = PyLong_AsLong(PyTuple_GetItem(args, 0));
    GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
    res->size = ((GLMMat3Array *)self)->size;
    res->val = new glm::vec3[res->size + 1];
    int size = res->size;

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::row(((GLMMat3Array *)self)->val[i], id);
    }

    return (PyObject *)res;
}

PyObject * GLMMat3Array_tp_meth_col(GLMMat2 * self, PyObject * args){
    int id = PyLong_AsLong(PyTuple_GetItem(args, 0));
    GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
    res->size = ((GLMMat3Array *)self)->size;
    res->val = new glm::vec3[res->size + 1];
    int size = res->size;

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::column(((GLMMat3Array *)self)->val[i], id);
    }

    return (PyObject *)res;
}

PyMethodDef GLMMat3Array_tp_methods[] = {
	{"row", (PyCFunction)GLMMat3Array_tp_meth_row, METH_VARARGS, 0},
	{"col", (PyCFunction)GLMMat3Array_tp_meth_col, METH_VARARGS, 0},
	{0},
};

PyObject * GLMMat3Array_tp_get_trans(GLMMat3Array * self, void * closure){
    GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
    int size = self->size;
    res->size = size;
    res->val = new glm::mat3[size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::transpose(self->val[i]);
    }

    return (PyObject *)res;
}

PyObject * GLMMat3Array_tp_get_det(GLMMat3Array * self, void * closure){
    int size = self->size;
    GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
    res->size = size;
    res->val = new float[size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::determinant(self->val[i]);
    }
    return (PyObject *)res;
}

PyObject * GLMMat3Array_tp_get_inv(GLMMat3Array * self, void * closure){
    GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
    int size = self->size;
    res->size = size;
    res->val = new glm::mat3[size + 1];

    for(int i = 0; i < size; ++i){
        res->val[i] = glm::inverse(self->val[i]);
    }
    return (PyObject *)res;
}

PyObject * GLMMat3Array_tp_get_tup(GLMMat3Array * self, void * closure){
    return (PyObject *) GLMMat3Array_Tuple(self);
}

PyGetSetDef GLMMat3Array_tp_getseters[] = {
	{(char *)"trans", (getter)GLMMat3Array_tp_get_trans, 0, 0, 0},
	{(char *)"det", (getter)GLMMat3Array_tp_get_det, 0, 0, 0},
	{(char *)"inv", (getter)GLMMat3Array_tp_get_inv, 0, 0, 0},
	{(char *)"tup", (getter)GLMMat3Array_tp_get_tup, 0, 0, 0},
	{0},
};

PyTypeObject GLMMat3Array_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.Mat2", // tp_name
	sizeof(GLMMat2), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMMat3Array_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMMat3Array_tp_repr, // tp_repr
	&GLMMat3Array_tp_as_number, // tp_as_number
	&GLMMat3Array_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMMat3Array_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	GLMMat3Array_tp_methods, // tp_methods
	0, // tp_members
	GLMMat3Array_tp_getseters, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMMat3Array_tp_init, // tp_init
	0, // tp_alloc
	GLMMat3Array_tp_new, // tp_new
};

PyObject * GLMMat3Array_Tuple(GLMMat3Array * self){
    int size = self->size;
    PyObject * tuple = PyTuple_New(size * N * N);

    for(int i = 0; i < size; ++i){
        PyTuple_SET_ITEM(tuple, i * N * N + 0, PyFloat_FromDouble(self->val[i][0][0]));
        PyTuple_SET_ITEM(tuple, i * N * N + 1, PyFloat_FromDouble(self->val[i][0][1]));
        PyTuple_SET_ITEM(tuple, i * N * N + 2, PyFloat_FromDouble(self->val[i][0][2]));
        PyTuple_SET_ITEM(tuple, i * N * N + 3, PyFloat_FromDouble(self->val[i][1][0]));
        PyTuple_SET_ITEM(tuple, i * N * N + 4, PyFloat_FromDouble(self->val[i][1][1]));
        PyTuple_SET_ITEM(tuple, i * N * N + 5, PyFloat_FromDouble(self->val[i][1][2]));
        PyTuple_SET_ITEM(tuple, i * N * N + 6, PyFloat_FromDouble(self->val[i][2][0]));
        PyTuple_SET_ITEM(tuple, i * N * N + 7, PyFloat_FromDouble(self->val[i][2][1]));
        PyTuple_SET_ITEM(tuple, i * N * N + 8, PyFloat_FromDouble(self->val[i][2][2]));
    }

    return tuple;
}