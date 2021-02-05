from setuptools import Extension, setup

ext = Extension(
    name='miniglm',
    sources=['./miniglm.cpp'],
    extra_compile_args=['-fpermissive'],
    include_dirs=['include'],
    library_dirs=[],
    libraries=[],
)

with open('README.md') as readme:
    long_description = readme.read()

setup(
    name='miniglm',
    version='0.3.1',
    ext_modules=[ext],
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/cprogrammer1994/miniglm',
    author='Szabolcs Dombi',
    author_email='cprogrammer1994@gmail.com',
    license='MIT',
)
