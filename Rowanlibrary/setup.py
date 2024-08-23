from distutils.core import setup, Extension

module = Extension('megaognezyum',
                   sources=['rowan.c'])

setup(name='megaognezyum',
      version='1.0',
      description='Mega Ognezyum Module',
      ext_modules=[module])
