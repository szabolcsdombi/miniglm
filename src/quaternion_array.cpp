#include "common.hpp"

#define N 4

PyObject * GLMQuatArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs){
    GLMQuatArray * self = (GLMQuatArray *)type->tp_alloc(type, 0);

    if(self){
        self->val = 0;
    }

    return (PyObject *)self;
}

PyObject * GLMQuatArray_tp_dealloc(GLMQuatArray * self){
    Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMQuatArrat_tp_init(GLMQuatArray * self, PyObject * args, PyObject * kwargs){
    PyObject * iterable = PyTuple_GetItem(args, 0);

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

        GLMQuatArray * res;
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

            GLMVec3Array * res;
            res->size = lhs_size;
            res->val = new glm::vec3[res->size + 1];

            for(int i = 0; i < lhs_size; ++i){
                res->val[i] = lhs_val[i] * rhs_val[i];
            }

            return (PyObject *)res;
        }

        if(Py_TYPE(rhs) == &GLMMat3Array_Type){
            
        }
    }
}