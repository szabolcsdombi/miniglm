from setuptools import Extension, setup

ext = Extension(
    name='mymodule',
    sources=['./mymodule.cpp'],
    extra_compile_args=['-fpermissive'],
    include_dirs=['include'],
    library_dirs=[],
    libraries=[],
)

setup(
    name='mymodule',
    version='0.1.0',
    ext_modules=[ext],
)
