#include "common.hpp"

#define N 2

PyObject * GLMMat2Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs){
    GLMMat2Array * self = (GLMMat2Array *)type->tp_alloc(type, 0);

    if(self){
        self->val = 0;
    }

    return (PyObject *)self;
}

PyObject * GLMMat2Array_tp_dealloc(GLMMat2Array * self){
    Py_TYPE(self)->tp_dealloc((PyObject *)self);
}

int GLMMat2Array_tp_init(GLMMat2Array * self, PyObject * args, PyObject * kwargs){
    PyObject * iterable = PyTuple_GET_ITEM(args, 0);
    
    if(Py_TYPE(iterable) == &PyTuple_Type && PyTuple_GET_SIZE(iterable) % (N * N) == 0){
        self->size = PyTuple_GET_SIZE(iterable) / (N * N);
        self->val = new glm::mat2[self->size + 1];

        for(int i = 0; i < self->size; ++i){
            self->val[i][0][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 0));
            self->val[i][0][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 1));
            self->val[i][1][0] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 2));
            self->val[i][1][1] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i * N + 3));
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
    self->val = new glm::mat2[self->size + 1];

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

PyObject * GLMMat2Array_tp_repr(GLMMat2Array * self){
    PyObject * temp = GLMMat2Array_Tuple(self);
    PyObject * res = PyObject_Repr(temp);
    Py_DECREF(temp);
    return (PyObject *)res;
}

PyObject * GLMMat2Array_nb_add(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMMat2Array_Type && Py_TYPE(rhs) == &GLMMat2Array_Type){
        int lhs_size = ((GLMMat2Array *)lhs)->size;
        int rhs_size = ((GLMMat2Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat2Array * res;
        res->size = lhs_size;
        res->val = new glm::mat2[res->size + 1];

        glm::mat2 * lhs_val = ((GLMMat2Array *)lhs)->val;
        glm::mat2 * rhs_val = ((GLMMat2Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] + rhs_val[i];
        }
        
        return (PyObject *)res;
    }
    
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2Array_nb_subtract(PyObject * lhs, PyObject * rhs){
     if(Py_TYPE(lhs) == &GLMMat2Array_Type && Py_TYPE(rhs) == &GLMMat2Array_Type){
        int lhs_size = ((GLMMat2Array *)lhs)->size;
        int rhs_size = ((GLMMat2Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat2Array * res;
        res->size = lhs_size;
        res->val = new glm::mat2[res->size + 1];

        glm::mat2 * lhs_val = ((GLMMat2Array *)lhs)->val;
        glm::mat2 * rhs_val = ((GLMMat2Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] - rhs_val[i];
        }
        
        return (PyObject *)res;
    }
    
    Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMMat2Array_nb_multiply(PyObject * lhs, PyObject * rhs){
    if(Py_TYPE(lhs) == &GLMMat2Array_Type && Py_TYPE(rhs) == &GLMMat2Array_Type){
        int lhs_size = ((GLMMat2Array *)lhs)->size;
        int rhs_size = ((GLMMat2Array *)rhs)->size;

        if(lhs_size != rhs_size){
            PyErr_Format(PyExc_Exception, "different sizes");
            return 0;
        }

        GLMMat2Array * res;
        res->size = lhs_size;
        res->val = new glm::mat2[res->size + 1];

        glm::mat2 * lhs_val = ((GLMMat2Array *)lhs)->val;
        glm::mat2 * rhs_val = ((GLMMat2Array *)rhs)->val;

        for(int i = 0; i < res->size; ++i){
            res->val[i] = lhs_val[i] * rhs_val[i];
        }
        
        return (PyObject *)res;
    }

    if(Py_TYPE(lhs) == &GLMMat2Array_Type){
        if(Py_TYPE(rhs) == &GLMVec2Array_Type){
            int lhs_size = ((GLMMat2Array *)lhs)->size;
            int rhs_size = ((GLMVec2Array *)rhs)->size;

            if(lhs_size != rhs_size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            GLMVec2Array * res;
            res->size = lhs_size;
            res->val = new glm::vec2[res->size + 1];

            glm::mat2 * lhs_val = ((GLMMat2Array *)lhs)->val;
            glm::vec2 * rhs_val = ((GLMVec2Array *)rhs)->val;

            for(int i = 0; i < res->size; ++i){
                res->val[i] = lhs_val[i] * rhs_val[i];
            }

            return (PyObject *)res;
   
        }

        if(Py_TYPE(rhs) == &PyFloat_Type){
            float scalar = PyFloat_AsDouble(rhs);

            GLMMat2Array * res;
            res->size = ((GLMMat2Array*)lhs)->size;
            res->val = new glm::mat2[res->size + 1];
            
            for(int i = 0; i < res->size; ++i){
                res->val[i] = ((GLMMat2Array *)lhs)->val[i] * scalar;
            }

            return (PyObject *)res;

        }
    }
}