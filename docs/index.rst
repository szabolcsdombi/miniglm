miniglm
=======

.. automodule:: miniglm

.. currentmodule:: miniglm

- :py:func:`mat4_perspective`
- :py:func:`mat4_ortho`
- :py:func:`mat4_look_at`
- :py:class:`Vec2`
- :py:class:`Vec3`
- :py:class:`Vec4`
- :py:class:`Mat2`
- :py:class:`Mat3`
- :py:class:`Mat4`
- :py:class:`Quat`

-----

.. autofunction:: mat4_perspective(fovy, ratio, znear, zfar) -> Mat4
.. autofunction:: mat4_ortho(left, right, bottom, top, znear, zfar) -> Mat4
.. autofunction:: mat4_look_at(eye, center, up) -> Mat4

.. autoclass:: Vec2

	- :py:attr:`Vec2.length`
	- :py:attr:`Vec2.normal`
	- :py:attr:`Vec2.tup`
	- :py:meth:`Vec2.dot`
	- :py:meth:`Vec2.reflect`
	- :py:meth:`Vec2.refract`

	.. literalinclude:: vec2_example.py

	.. autoattribute:: Vec2.length
	.. autoattribute:: Vec2.normal
	.. autoattribute:: Vec2.tup

	.. automethod:: dot(rhs) -> float
	.. automethod:: reflect(norm) -> Vec2
	.. automethod:: refract(norm, eta) -> Vec2


.. autoclass:: Vec3

	- :py:attr:`Vec3.length`
	- :py:attr:`Vec3.normal`
	- :py:attr:`Vec3.tup`
	- :py:meth:`Vec3.dot`
	- :py:meth:`Vec3.cross`
	- :py:meth:`Vec3.reflect`
	- :py:meth:`Vec3.refract`

	.. literalinclude:: vec3_example.py

	.. autoattribute:: Vec3.length
	.. autoattribute:: Vec3.normal
	.. autoattribute:: Vec3.tup

	.. automethod:: dot(rhs) -> float
	.. automethod:: cross(rhs) -> float
	.. automethod:: reflect(norm) -> Vec3
	.. automethod:: refract(norm, eta) -> Vec3


.. autoclass:: Vec4

	- :py:attr:`Vec4.length`
	- :py:attr:`Vec4.normal`
	- :py:attr:`Vec4.tup`
	- :py:meth:`Vec4.dot`
	- :py:meth:`Vec4.reflect`
	- :py:meth:`Vec4.refract`

	.. literalinclude:: vec4_example.py

	.. autoattribute:: Vec4.length
	.. autoattribute:: Vec4.normal
	.. autoattribute:: Vec4.tup

	.. automethod:: dot(rhs) -> float
	.. automethod:: reflect(norm) -> Vec4
	.. automethod:: refract(norm, eta) -> Vec4


.. autoclass:: Mat2

	- :py:attr:`Mat2.trans`
	- :py:attr:`Mat2.det`
	- :py:attr:`Mat2.inv`
	- :py:attr:`Mat2.tup`
	- :py:meth:`Mat2.row`
	- :py:meth:`Mat2.col`

	.. literalinclude:: mat2x2_example.py

	.. autoattribute:: Mat2.trans
	.. autoattribute:: Mat2.det
	.. autoattribute:: Mat2.inv
	.. autoattribute:: Mat2.tup

	.. automethod:: row(i) -> Vec2
	.. automethod:: col(i) -> Vec2


.. autoclass:: Mat3

	- :py:attr:`Mat3.trans`
	- :py:attr:`Mat3.det`
	- :py:attr:`Mat3.inv`
	- :py:attr:`Mat3.tup`
	- :py:meth:`Mat3.row`
	- :py:meth:`Mat3.col`

	.. literalinclude:: mat3x3_example.py

	.. autoattribute:: Mat3.trans
	.. autoattribute:: Mat3.det
	.. autoattribute:: Mat3.inv
	.. autoattribute:: Mat3.tup

	.. automethod:: row(i) -> Vec3
	.. automethod:: col(i) -> Vec3


.. autoclass:: Mat4

	- :py:attr:`Mat4.trans`
	- :py:attr:`Mat4.det`
	- :py:attr:`Mat4.inv`
	- :py:attr:`Mat4.tup`
	- :py:meth:`Mat4.row`
	- :py:meth:`Mat4.col`

	.. literalinclude:: mat4x4_example.py

	.. autoattribute:: Mat4.trans
	.. autoattribute:: Mat4.det
	.. autoattribute:: Mat4.inv
	.. autoattribute:: Mat4.tup

	.. automethod:: row(i) -> Vec4
	.. automethod:: col(i) -> Vec4


.. autoclass:: Quat

	- :py:attr:`Quat.length`
	- :py:attr:`Quat.normal`
	- :py:attr:`Quat.conj`
	- :py:attr:`Quat.inv`
	- :py:attr:`Quat.tup`
	- :py:meth:`Quat.dot`
	- :py:meth:`Quat.cross`
	- :py:meth:`Quat.slerp`

	.. literalinclude:: quat_example.py

	.. autoattribute:: Quat.length
	.. autoattribute:: Quat.normal
	.. autoattribute:: Quat.conj
	.. autoattribute:: Quat.inv
	.. autoattribute:: Quat.tup

	.. automethod:: dot(rhs) -> float
	.. automethod:: cross(rhs) -> Quat
	.. automethod:: slerp(rhs, coef) -> Quat


.. toctree::
   :maxdepth: 2
