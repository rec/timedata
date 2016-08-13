import os, platform
import setuptools.extension
from setuptools.command.build_ext import build_ext
import Cython.Build

from . Command import *
from .. import execute, template


class BuildExt(build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

    def finalize_options(self):
        os.makedirs('build/genfiles/timedata', exist_ok=True)
        flags = CONFIG.compiler_flags[platform.system().lower()]
        git_tags = execute.git_tags()
        compile_args = template.substitute_one(
            flags, git_tags=git_tags, time=TIME).split()

        opt_flags = None
        if not platform.system() == 'Windows':
            opt_flags = CONFIG.build_options[FLAGS.buildtype or 'o3'].split()
            if FLAGS.compileropt:
                opt_flags += FLAGS.compileropt.split()
            compile_args += opt_flags
            compile_args.append(
                '-DOPTIMIZATION_FLAGS="%s"' % ' '.join(sorted(opt_flags)))
        is_debian = platform.linux_distribution()[0] == 'debian'
        libraries = ['m'] if is_debian else []

        extension = setuptools.extension.Extension(
            name='timedata',
            sources=['timedata.pyx'],
            libraries=libraries,
            include_dirs=['src/cpp'],
            extra_compile_args=compile_args,
            extra_link_args=opt_flags,
            language='c++',
        )

        module = Cython.Build.cythonize(
            [extension],
            language='c++',
            language_level=3,

            compiler_directives=dict(
                c_string_encoding='ascii',
                # c_string_type='unicode', # Why doesn't this work?
            )
        )
        self.distribution.ext_modules = module
        super().finalize_options()