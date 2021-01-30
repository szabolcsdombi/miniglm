# miniglm

Minimalist pythonic matrix, vector, quaternion math.

## Types

- `SCALAR` is a python float
- `VECTOR` is a tuple of three floats
- `QUATERNION` is a tuple of four floats (xyzw)
- `MATRIX` is a tuple of nine floats (column-major)

## Methods

```
add(a, b)
    VECTOR VECTOR -> vector addition
    VECTOR SCALAR -> (x, y, z) + s = (x+s, y+s, z+s)

sub(a, b)
    VECTOR VECTOR -> vector subtraction
    VECTOR SCALAR -> (x, y, z) - s = (x-s, y-s, z-s)

mul(a, b)
    VECTOR SCALAR -> vector scaling by a scalar
    VECTOR VECTOR -> element-wise multiplication
    QUATERNION VECTOR -> quaternion scaling by a scalar
    QUATERNION QUATERNION -> quaternion rotates a quaternion resulting in a quaternion
    QUATERNION MATRIX -> quaternion rotates a matrix resulting in a matrix
    MATRIX VECTOR -> matrix rotates a vector resulting in a vector
    MATRIX QUATERNION -> matrix rotates a quaternion resulting in a quaternion
    MATRIX MATRIX -> matrix rotates a matrix resulting in a matrix

mix(a, b, s)
    SCALAR SCALAR -> simple mix of scalars
    VECTOR VECTOR -> simple mix of vectors
    QUATERNION QUATERNION -> quaternion rotation spherical interpolation (slerp)
    MATRIX MATRIX -> matrix rotation spherical interpolation (slerp)

normalize(a)
    VECTOR -> vector normalize
    QUATERNION -> quaternion normalize
    MATRIX -> normalized quaternion derived from the matrix converted back to a matrix

inverse(a)
    QUATERNION -> inverse quaternion
    MATRIX -> inverse matrix

cast(a)
    QUATERNION -> converts the quaternion to a matrix
    MATRIX -> converts the matrix to a quaternion

swizzle(a, b, swizzle)
    VECTOR -> swaps vector elements
    QUATERNION -> swaps quaternion elements

pack(a)
    SCALAR -> packed float resulting in 4 bytes
    VECTOR -> packed vector resulting in 12 bytes
    QUATERNION -> packed quaternion resulting in 16 bytes (xyzw)
    MATRIX -> packed matrix resulting in 36 bytes (column-major)
```
