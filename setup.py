from setuptools import setup, Extension

module = Extension(
    'quicklz',
    sources=['quicklzmodule.c', 'quicklz.c'],  # 包含 QuickLZ 的源码文件
    include_dirs=['.'],  # 包含头文件的路径
)

setup(
    name='quicklz',
    version='1.4.1',
    description='Python wrapper for QuickLZ',
    ext_modules=[module],
)