from setuptools import setup, Extension

module = Extension(
    'Adamlibrary',
    sources=['adam.c']
)

setup(
    name='Adamlibrary',
    version='1.0',
    description='A C library for Python with additional C functions',
    ext_modules=[module]
)
