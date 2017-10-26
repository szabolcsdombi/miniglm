from setuptools import setup, Extension

glm = Extension(
    'miniglm.glm',
    sources=[
        'src/vector2.cpp',
        'src/vector3.cpp',
        'src/vector4.cpp',
        'src/matrix2.cpp',
        'src/matrix3.cpp',
        'src/matrix4.cpp',
        'src/quaternion.cpp',
        'src/module.cpp',
        'src/others.cpp',
        'src/tools.cpp',
    ]
)

setup(
    name='miniglm',
    version='0.2.0',
    packages=['miniglm'],
    ext_modules=[glm],
)
