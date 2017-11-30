#include <Python.h>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct GLMVec2 {
	PyObject_HEAD
	glm::vec2 val;
};

struct GLMVec3 {
	PyObject_HEAD
	glm::vec3 val;
};

struct GLMVec4 {
	PyObject_HEAD
	glm::vec4 val;
};

struct GLMMat2 {
	PyObject_HEAD
	glm::mat2x2 val;
};

struct GLMMat3 {
	PyObject_HEAD
	glm::mat3x3 val;
};

struct GLMMat4 {
	PyObject_HEAD
	glm::mat4x4 val;
};

struct GLMQuat {
	PyObject_HEAD
	glm::quat val;
};

struct GLMVec2Array {
	PyObject_HEAD
	glm::vec2 * val;
	int size;
};

struct GLMVec3Array {
	PyObject_HEAD
	glm::vec3 * val;
	int size;
};

struct GLMVec4Array {
	PyObject_HEAD
	glm::vec4 * val;
	int size;
};

struct GLMQuatArray {
	PyObject_HEAD
	glm::quat * val;
	int size;
};

struct GLMMat2Array {
	PyObject_HEAD
	glm::mat2 * val;
	int size;
};

struct GLMMat3Array {
	PyObject_HEAD
	glm::mat3 * val;
	int size;
};

struct GLMMat4Array {
	PyObject_HEAD
	glm::mat2 * val;
	int size;
};


extern PyTypeObject GLMVec2_Type;
extern PyTypeObject GLMVec3_Type;
extern PyTypeObject GLMVec4_Type;

extern PyTypeObject GLMMat2_Type;
extern PyTypeObject GLMMat3_Type;
extern PyTypeObject GLMMat4_Type;

extern PyTypeObject GLMQuat_Type;

extern PyTypeObject GLMVec2Array_Type;
extern PyTypeObject GLMVec3Array_Type;
extern PyTypeObject GLMVec4Array_Type;

extern PyTypeObject GLMMat2Array_Type;
extern PyTypeObject GLMMat3Array_Type;
extern PyTypeObject GLMMat4Array_Type;

extern PyTypeObject GLMQuatArray_Type;

PyObject * GLMVec2_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMVec3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMVec4_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMMat2_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMat3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMat4_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMQuat_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMVec2Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMVec3Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMVec4Array_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMMat2_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMat3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMat4_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMMatArray2_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMatArray3_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);
PyObject * GLMMatArray4_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMQuatArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

PyObject * GLMVec2_Tuple(GLMVec2 * self);
PyObject * GLMVec3_Tuple(GLMVec3 * self);
PyObject * GLMVec4_Tuple(GLMVec4 * self);

PyObject * GLMMat2_Tuple(GLMMat2 * self);
PyObject * GLMMat3_Tuple(GLMMat3 * self);
PyObject * GLMMat4_Tuple(GLMMat4 * self);

PyObject * GLMQuat_Tuple(GLMQuat * self);

PyObject * GLMVec2Array_Tuple(GLMVec2Array * self);
PyObject * GLMVec3Array_Tuple(GLMVec4Array * self);
PyObject * GLMVec4Array_Tuple(GLMVec4Array * self);

PyObject * GLMMat2Array_Tuple(GLMMat2Array * self);
PyObject * GLMMat2Array_Tuple(GLMMat3Array * self);
PyObject * GLMMat2Array_Tuple(GLMMat4Array * self);

PyObject * GLMQuatArray_Tuple(GLMQuatArray * self);

glm::vec2 vec2_from_iterable(PyObject * iterable);
glm::vec3 vec3_from_iterable(PyObject * iterable);
glm::vec4 vec4_from_iterable(PyObject * iterable);

glm::mat2 mat2_from_iterable(PyObject * iterable);
glm::mat3 mat3_from_iterable(PyObject * iterable);
glm::mat4 mat4_from_iterable(PyObject * iterable);

glm::quat quat_from_iterable(PyObject * iterable);

