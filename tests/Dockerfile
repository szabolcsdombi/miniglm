FROM python:3.9.1
RUN python3 -m pip install pytest numpy

WORKDIR /build
COPY include /build/include
COPY miniglm.cpp setup.py MANIFEST.in README.md LICENSE /build/
RUN python3 setup.py sdist
RUN python3 -m pip wheel dist/miniglm-*.tar.gz
RUN python3 -m pip install miniglm-*.whl

WORKDIR /tests
COPY tests /tests
CMD python3 -m pytest -v
