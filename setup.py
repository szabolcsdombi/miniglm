from setuptools import setup, Extension

glm = Extension(
    'miniglm.glm',
    sources=[
        'src/vector2.cpp',
        'src/vector3.cpp',
        'src/vector4.cpp',
        'src/vector2_array.cpp',
        'src/vector3_array.cpp',
        'src/vector4_array.cpp',
        'src/matrix2.cpp',
        'src/matrix3.cpp',
        'src/matrix4.cpp',
        'src/matrix2_array.cpp',
        'src/matrix3_array.cpp',
        'src/matrix4_array.cpp',
        'src/quaternion.cpp',
        'src/quaternion_array.cpp',
        'src/float_array.cpp',
        'src/module.cpp',
        'src/others.cpp',
        'src/tools.cpp',
    ]
)

setup(
    name='miniglm',
    version='0.2.4',
    packages=['miniglm'],
    ext_modules=[glm],
)
