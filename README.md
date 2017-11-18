# miniglm

```shell
pip install miniglm
```

- [github](https://github.com/cprogrammer1994/miniglm)
- [docs](http://miniglm.readthedocs.io)
- [pypi](https://pypi.python.org/pypi/miniglm)

Yet another module implementing vector math for python.
Most of the cases Numpy and Pyrr do great job. I have had performance issues so I implemented these features in C++.
This module is a minimalist implementation of the GLM features. It was optimized for speed in the following cases:

- Calculate a single mvp matrix from a perspective projection and a look at matrix.
- Passing vectors and matrices easily to OpenGL without extra memory allocations.

I prefer using tuples for represending 3D vectors, they are json serializable and standard Python types. An alternative solution is to use bytes, bytearray or anything that supports the buffer interface.
