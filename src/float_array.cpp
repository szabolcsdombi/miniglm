#include "common.hpp"

PyObject * GLMFloatArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	GLMFloatArray * self = (GLMFloatArray *)type->tp_alloc(type, 0);

	if (self) {
		self->val = 0;
	}

	return (PyObject *)self;
}

void GLMFloatArray_tp_dealloc(GLMFloatArray * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int GLMFloatArray_tp_init(GLMFloatArray * self, PyObject * args, PyObject * kwargs) {
	PyObject * iterable;

    int arg_ok = PyArg_ParseTuple(args, "O", &iterable);

    if(!arg_ok){
        return -1;
    }

	if (Py_TYPE(iterable) == &PyTuple_Type) {
		int size = PyTuple_GET_SIZE(iterable);
		self->val = new float[size + 1];
		self->size = size;

		for (int i = 0; i < size; ++i) {
			self->val[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(iterable, i));
		}

        if (PyErr_Occurred()) {
			return -1;
		}

		return 0;
	}

	PyObject * iterator = PyObject_GetIter(iterable);
	int size = PyObject_Size(iterable);

	if (!iterator || size < 0) {
		PyErr_Format(PyExc_Exception, "not iterable or wrong size");
		return 0;
	}

	size = size;

	self->val = new float[size + 1];
	self->size = size;

	for (int k = 0; k < size; ++k) {
        PyObject * item = PyIter_Next(iterator);
        self->val[k] = (float)PyFloat_AsDouble(item);
        Py_DECREF(item);
	}

	Py_DECREF(iterator);

	if (PyErr_Occurred()) {
		return -1;
	}

	return 0;
}

PyObject * GLMFloatArray_tp_repr(GLMFloatArray * self) {
	PyObject * temp = GLMFloatArray_Tuple(self);
	PyObject * res = PyObject_Repr(temp);
	Py_DECREF(temp);
	return res;
}

PyObject * GLMFloatArray_nb_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMFloatArray_Type) {
		if( Py_TYPE(rhs) == &GLMFloatArray_Type){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int lhs_size = ((GLMFloatArray *)lhs)->size;
            int rhs_size = ((GLMFloatArray *)rhs)->size;
            if (lhs_size != rhs_size) {
                PyErr_Format(PyExc_Exception, "different size");
                return 0;
            }
            float * lhs_val = ((GLMFloatArray *)lhs)->val;
            float * rhs_val = ((GLMFloatArray *)rhs)->val;
            res->size = lhs_size;
            res->val = new float[lhs_size + 1];
            for (int i = 0; i < lhs_size; ++i) {
                res->val[i] = lhs_val[i] + rhs_val[i];
            }
            return (PyObject *)res;
        }

        float rhs_val = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int size = ((GLMFloatArray *)lhs)->size;
            res->size = size;
            res->val = new float[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] + rhs_val;
            }

            return (PyObject *)res;
        }
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMFloatArray_Type) {
		if( Py_TYPE(rhs) == &GLMFloatArray_Type){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int lhs_size = ((GLMFloatArray *)lhs)->size;
            int rhs_size = ((GLMFloatArray *)rhs)->size;
            if (lhs_size != rhs_size) {
                PyErr_Format(PyExc_Exception, "different size");
                return 0;
            }
            float * lhs_val = ((GLMFloatArray *)lhs)->val;
            float * rhs_val = ((GLMFloatArray *)rhs)->val;
            res->size = lhs_size;
            res->val = new float[lhs_size + 1];
            for (int i = 0; i < lhs_size; ++i) {
                res->val[i] = lhs_val[i] - rhs_val[i];
            }
            return (PyObject *)res;
        }

        float rhs_val = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int size = ((GLMFloatArray *)lhs)->size;
            res->size = size;
            res->val = new float[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] - rhs_val;
            }

            return (PyObject *)res;
        }
	}

	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMFloatArray_Type) {
        if(Py_TYPE(rhs) == &GLMFloatArray_Type){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int lhs_size = ((GLMFloatArray *)lhs)->size;
            int rhs_size = ((GLMFloatArray *)rhs)->size;
            if (lhs_size != rhs_size) {
                PyErr_Format(PyExc_Exception, "different size");
                return 0;
            }
            float * lhs_val = ((GLMFloatArray *)lhs)->val;
            float * rhs_val = ((GLMFloatArray *)rhs)->val;
            res->size = lhs_size;
            res->val = new float[lhs_size + 1];
            for (int i = 0; i < lhs_size; ++i) {
                res->val[i] = lhs_val[i] * rhs_val[i];
            }
            return (PyObject *)res;
        }

        if(Py_TYPE(rhs) == &GLMVec2Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec2Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec2[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMVec2Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMVec3Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec3Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec3[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMVec3Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMVec4Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec4Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec4[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMVec4Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat2Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat2Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat2Array * res = (GLMMat2Array *)GLMMat2Array_tp_new(&GLMMat2Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat2[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMMat2Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat3Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat3Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat3[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMMat3Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat4Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat4Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat4Array * res = (GLMMat4Array *)GLMMat4Array_tp_new(&GLMMat4Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat4[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMMat4Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMQuatArray_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMQuatArray *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMQuatArray * res = (GLMQuatArray *)GLMQuatArray_tp_new(&GLMQuatArray_Type, 0, 0);
            res->size = size;
            res->val = new glm::quat[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * ((GLMQuatArray *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        float rhs_val = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int size = ((GLMFloatArray *)lhs)->size;
            res->size = size;
            res->val = new float[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] * rhs_val;
            }

            return (PyObject *)res;
        }
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(lhs) == &GLMFloatArray_Type) {
        if(Py_TYPE(rhs) == &GLMFloatArray_Type){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int lhs_size = ((GLMFloatArray *)lhs)->size;
            int rhs_size = ((GLMFloatArray *)rhs)->size;
            if (lhs_size != rhs_size) {
                PyErr_Format(PyExc_Exception, "different size");
                return 0;
            }
            float * lhs_val = ((GLMFloatArray *)lhs)->val;
            float * rhs_val = ((GLMFloatArray *)rhs)->val;
            res->size = lhs_size;
            res->val = new float[lhs_size + 1];
            for (int i = 0; i < lhs_size; ++i) {
                res->val[i] = lhs_val[i] / rhs_val[i];
            }
            return (PyObject *)res;
        }

        if(Py_TYPE(rhs) == &GLMVec2Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec2Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec2Array * res = (GLMVec2Array *)GLMVec2Array_tp_new(&GLMVec2Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec2[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMVec2Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMVec3Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec3Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec3Array * res = (GLMVec3Array *)GLMVec3Array_tp_new(&GLMVec3Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec3[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMVec3Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMVec4Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMVec4Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMVec4Array * res = (GLMVec4Array *)GLMVec4Array_tp_new(&GLMVec4Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::vec4[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMVec4Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat2Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat2Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat2Array * res = (GLMMat2Array *)GLMMat2Array_tp_new(&GLMMat2Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat2[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMMat2Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat3Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat3Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat3Array * res = (GLMMat3Array *)GLMMat3Array_tp_new(&GLMMat3Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat3[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMMat3Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        if(Py_TYPE(rhs) == &GLMMat4Array_Type){
            if(((GLMFloatArray *)lhs)->size != ((GLMMat4Array *)rhs)->size){
                PyErr_Format(PyExc_Exception, "different sizes");
                return 0;
            }

            int size = ((GLMFloatArray *)lhs)->size;
            GLMMat4Array * res = (GLMMat4Array *)GLMMat4Array_tp_new(&GLMMat4Array_Type, 0, 0);
            res->size = size;
            res->val = new glm::mat4[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / ((GLMMat4Array *)rhs)->val[i];
            }

            return (PyObject *) res;
        }

        float rhs_val = (float)PyFloat_AsDouble(rhs);
        if(!PyErr_Occurred()){
            GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
            int size = ((GLMFloatArray *)lhs)->size;
            res->size = size;
            res->val = new float[size + 1];

            for(int i = 0; i < size; ++i){
                res->val[i] = ((GLMFloatArray *)lhs)->val[i] / rhs_val;
            }

            return (PyObject *)res;
        }
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_inplace_add(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMFloatArray_Type) {
		int lhs_size = ((GLMFloatArray *)lhs)->size;
		int rhs_size = ((GLMFloatArray *)rhs)->size;
		
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}

		for (int i = 0; i < lhs_size; ++i) {
			((GLMFloatArray *)lhs)->val[i] += ((GLMFloatArray *)rhs)->val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_val = (float)PyFloat_AsDouble(rhs);

	if(!PyErr_Occurred()){
		int size = ((GLMFloatArray *)lhs)->size;

		for(int i = 0; i < size; ++i){
			((GLMFloatArray *)lhs)->val[i] += rhs_val;
		}
		Py_INCREF(lhs);
		return lhs;
	}
	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_inplace_subtract(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMFloatArray_Type) {
		int lhs_size = ((GLMFloatArray *)lhs)->size;
		int rhs_size = ((GLMFloatArray *)rhs)->size;
		if (lhs_size != rhs_size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		for (int i = 0; i < lhs_size; ++i) {
			((GLMFloatArray *)lhs)->val[i] -= ((GLMFloatArray *)rhs)->val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_val = (float)PyFloat_AsDouble(rhs);

	if(!PyErr_Occurred()){
		int size = ((GLMFloatArray *)lhs)->size;

		for(int i = 0; i < size; ++i){
			((GLMFloatArray *)lhs)->val[i] -= rhs_val;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;

}

PyObject * GLMFloatArray_nb_inplace_multiply(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMVec2Array_Type) {
		if (((GLMFloatArray *)lhs)->size != ((GLMFloatArray *)rhs)->size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}

		int size = ((GLMFloatArray *)rhs)->size;

		for (int i = 0; i < size; ++i) {
			((GLMFloatArray *)lhs)->val[i] *= ((GLMFloatArray *)rhs)->val[i];
		}
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMFloatArray *)lhs)->size;
		for (int i = 0; i < size; ++i) {
			((GLMFloatArray *)lhs)->val[i] *= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_inplace_true_divide(PyObject * lhs, PyObject * rhs) {
	if (Py_TYPE(rhs) == &GLMFloatArray_Type) {
		if (((GLMFloatArray *)lhs)->size != ((GLMFloatArray *)rhs)->size) {
			PyErr_Format(PyExc_Exception, "different size");
			return 0;
		}
		
		int size = ((GLMFloatArray *)rhs)->size;

		for (int i = 0; i < size; ++i) {
			((GLMFloatArray *)lhs)->val[i] /= ((GLMFloatArray *)rhs)->val[i];
		}
		
		Py_INCREF(lhs);
		return lhs;
	}

	float rhs_float = (float)PyFloat_AsDouble(rhs);
	if (!PyErr_Occurred()) {
		int size = ((GLMFloatArray *)lhs)->size;

		for (int i = 0; i < size; ++i) {
			((GLMFloatArray *)lhs)->val[i] /= rhs_float;
		}
		Py_INCREF(lhs);
		return lhs;
	}

	PyErr_Clear();
	Py_RETURN_NOTIMPLEMENTED;
}

PyObject * GLMFloatArray_nb_negative(GLMFloatArray * self) {
	GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
	int size = ((GLMFloatArray *)self)->size;
	float * val = ((GLMFloatArray *)self)->val;
	res->size = size;
	res->val = new float[size + 1];
	for (int i = 0; i < size; ++i) {
		res->val[i] = -val[i];
	}
	return (PyObject *)res;
}

PyObject * GLMFloatArray_nb_positive(GLMFloatArray * self) {
	GLMFloatArray * res = (GLMFloatArray *)GLMFloatArray_tp_new(&GLMFloatArray_Type, 0, 0);
	int size = ((GLMFloatArray *)self)->size;
	float * val = ((GLMFloatArray *)self)->val;
	res->size = size;
	res->val = new float[size];
	for (int i = 0; i < size; ++i) {
		res->val[i] = +val[i];
	}
	return (PyObject *)res;
}

PyNumberMethods GLMFloatArray_tp_as_number = {
	(binaryfunc)GLMFloatArray_nb_add, // binaryfunc nb_add;
	(binaryfunc)GLMFloatArray_nb_subtract, // binaryfunc nb_subtract;
	(binaryfunc)GLMFloatArray_nb_multiply, // binaryfunc nb_multiply;
	0, // binaryfunc nb_remainder;
	0, // binaryfunc nb_divmod;
	0, // ternaryfunc nb_power;
	(unaryfunc)GLMFloatArray_nb_negative, // unaryfunc nb_negative;
	(unaryfunc)GLMFloatArray_nb_positive, // unaryfunc nb_positive;
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
	(binaryfunc)GLMFloatArray_nb_inplace_add, // binaryfunc nb_inplace_add;
	(binaryfunc)GLMFloatArray_nb_inplace_subtract, // binaryfunc nb_inplace_subtract;
	(binaryfunc)GLMFloatArray_nb_inplace_multiply, // binaryfunc nb_inplace_multiply;
	0, // binaryfunc nb_inplace_remainder;
	0, // ternaryfunc nb_inplace_power;
	0, // binaryfunc nb_inplace_lshift;
	0, // binaryfunc nb_inplace_rshift;
	0, // binaryfunc nb_inplace_and;
	0, // binaryfunc nb_inplace_xor;
	0, // binaryfunc nb_inplace_or;
	0, // binaryfunc nb_floor_divide;
	(binaryfunc)GLMFloatArray_nb_true_divide, // binaryfunc nb_true_divide;
	0, // binaryfunc nb_inplace_floor_divide;
	(binaryfunc)GLMFloatArray_nb_inplace_true_divide, // binaryfunc nb_inplace_true_divide;
	0, // unaryfunc nb_index;
	// binaryfunc nb_matrix_multiply;
	// binaryfunc nb_inplace_matrix_multiply;
};

Py_ssize_t GLMFloatArray_sq_length(GLMFloatArray * self) {
	return self->size;
}

PyObject * GLMFloatArray_sq_item(GLMFloatArray * self, Py_ssize_t key) {
	if (key < self->size) {
		return PyFloat_FromDouble(self->val[key]);
	} else {
		return 0;
	}
}

int GLMFloatArray_sq_ass_item(GLMFloatArray * self, Py_ssize_t key, PyObject * value) {
	if (key < self->size) {
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

PySequenceMethods GLMFloatArray_tp_as_sequence = {
	(lenfunc)GLMFloatArray_sq_length, // lenfunc sq_length;
	0, // binaryfunc sq_concat;
	0, // ssizeargfunc sq_repeat;
	(ssizeargfunc)GLMFloatArray_sq_item, // ssizeargfunc sq_item;
	0, // void *was_sq_slice;
	(ssizeobjargproc)GLMFloatArray_sq_ass_item, // ssizeobjargproc sq_ass_item;
	0, // void *was_sq_ass_slice;
	0, // objobjproc sq_contains;
	0, // binaryfunc sq_inplace_concat;
	0, // ssizeargfunc sq_inplace_repeat;
};

int GLMFloatArray_bf_getbuffer(GLMFloatArray * self, Py_buffer * view, int flags) {
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

PyBufferProcs GLMFloatArray_tp_as_buffer = {
	(getbufferproc)GLMFloatArray_bf_getbuffer, // getbufferproc bf_getbuffer;
	0, // releasebufferproc bf_releasebuffer;
};



PyObject * GLMFloatArray_tp_get_tup(GLMFloatArray * self, void * closure) {
	return GLMFloatArray_Tuple(self);
}


PyTypeObject GLMFloatArray_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"glm.FloatArray", // tp_name
	sizeof(GLMFloatArray), // tp_basicsize
	0, // tp_itemsize
	(destructor)GLMFloatArray_tp_dealloc, // tp_dealloc
	0, // tp_print
	0, // tp_getattr
	0, // tp_setattr
	0, // tp_reserved
	(reprfunc)GLMFloatArray_tp_repr, // tp_repr
	&GLMFloatArray_tp_as_number, // tp_as_number
	&GLMFloatArray_tp_as_sequence, // tp_as_sequence
	0, // tp_as_mapping
	0, // tp_hash
	0, // tp_call
	0, // tp_str
	0, // tp_getattro
	0, // tp_setattro
	&GLMFloatArray_tp_as_buffer, // tp_as_buffer
	Py_TPFLAGS_DEFAULT, // tp_flags
	0, // tp_doc
	0, // tp_traverse
	0, // tp_clear
	0, // tp_richcompare
	0, // tp_weaklistoffset
	0, // tp_iter
	0, // tp_iternext
	0, // tp_methods
	0, // tp_members
	0, // tp_getset
	0, // tp_base
	0, // tp_dict
	0, // tp_descr_get
	0, // tp_descr_set
	0, // tp_dictoffset
	(initproc)GLMFloatArray_tp_init, // tp_init
	0, // tp_alloc
	GLMFloatArray_tp_new, // tp_new
};

PyObject * GLMFloatArray_Tuple(GLMFloatArray * self) {
	int size = self->size;

	PyObject * tuple = PyTuple_New(self->size);
	for (int i = 0; i < size; ++i) {
		PyTuple_SetItem(tuple, i, PyFloat_FromDouble(self->val[i]));
	}

	if(PyErr_Occurred()){
		return 0;
	}

	return tuple;
}
