project('fglt', 'cpp',
        version : '1.0.1',
        license : 'GPL-3.0-or-later',
        meson_version : '>=0.49.0',
        default_options: ['buildtype=release',
                          'default_library=both'])

# ========== compiler options

cc = meson.get_compiler('cpp')

is_icpc         = cc.get_id() == 'intel' or cc.get_id() == 'intel-cl'
enable_opencilk = not is_icpc \
                  and cc.has_argument('-fopencilk') \
                  and cc.has_header('cilk/cilk.h') \
                  and cc.has_header('cilk/cilk_api.h')
enable_cilkplus = not enable_opencilk \
                  and (is_icpc or cc.has_argument('-fcilkplus')) \
                  and cc.has_header('cilk/cilk.h') \
                  and cc.has_header('cilk/cilk_api.h')

if is_icpc
  add_global_arguments(['-wd3947,3946,10006,3950'], language : 'cpp')
endif

if enable_opencilk
  add_global_arguments(['-fopencilk', '-DHAVE_CILK_CILK_H'], language : 'cpp')
  add_global_link_arguments(['-fopencilk'], language : 'cpp')
elif enable_cilkplus
  add_global_arguments(['-fcilkplus', '-DHAVE_CILK_CILK_H'], language : 'cpp')
  add_global_link_arguments(['-lcilkrts'], language : 'cpp')
endif

# ========== OpenCilk tools

cpp_args_cs     = []
link_args_cs    = []
str_cs          = ''
cpp_args_bench  = []
link_args_bench = []
str_bench       = ''
cpp_args_san    = []
link_args_san   = []
str_san         = ''

if get_option('cilktool') == 'cilkscale' # ----- Cilkscale
  if not enable_opencilk
    warning('Cilkscale tool specified but not using OpenCilk compiler;'
            + ' skipping instrumentation...')
  else
    cpp_args_cs     = ['-fcilktool=cilkscale', '-DCILKSCALE']
    link_args_cs    = ['-fcilktool=cilkscale']
    str_cs          = '-cilkscale'
    cpp_args_bench  = ['-fcilktool=cilkscale-benchmark', '-DCILKSCALE']
    link_args_bench = ['-fcilktool=cilkscale-benchmark']
    str_bench       = str_cs + '-bench'
  endif
endif

if get_option('cilktool') == 'cilksan' # ----- Cilksan
  if not enable_opencilk
    warning('Cilksan tool specified but not using OpenCilk compiler'
            + ' skipping instrumentation...')
  else
    if not get_option('debug')
      warning('Cilksan instrumentation without debug symbols!')
    endif
    cpp_args_san  = ['-fsanitize=cilk','-fno-stripmine',
                     '-fno-vectorize','-fno-unroll-loops']
    link_args_san = ['-fsanitize=cilk']
    # FIXME There does not seem to be a way to add static-only arguments to
    # build targets defined via `library()`.
    # See also: https://github.com/mesonbuild/meson/issues/3304
    if get_option('default_library') != 'static'
      link_args_san += ['-shared-libasan']
    endif
    str_san = '-cilksan'
  endif
endif

# ========== build targets

fglthpp = configure_file(copy: true,
                         input: 'lib/fglt.hpp',
                         output: 'fglt.hpp')

install_headers('lib/fglt.hpp')

fglt_lib = library('fglt' + str_cs + str_san, 'lib/fglt.cpp',
                   cpp_args : cpp_args_cs + cpp_args_san,
                   link_args : link_args_cs + link_args_san,
                   install : true, install_dir : 'lib',
                   soversion : '0')

e = executable('fglt' + str_cs + str_san, 'src/fglt_mtx.cpp',
               link_with : fglt_lib,
               cpp_args : cpp_args_cs + cpp_args_san,
               link_args : link_args_cs + link_args_san,
               install : true,
               install_rpath : get_option('prefix') / 'lib')

#  Cilkscale-benchmark targets
if cpp_args_bench != []
  fglt_lib_bench = library('fglt' + str_bench, 'lib/fglt.cpp',
                           cpp_args : cpp_args_bench,
                           link_args : link_args_bench,
                           install : true, install_dir : 'lib',
                           soversion : '0')
  e_bench = executable('fglt' + str_bench, 'src/fglt_mtx.cpp',
                       link_with : fglt_lib_bench,
                       cpp_args : cpp_args_bench,
                       link_args : link_args_bench,
                       install : true,
                       install_rpath : get_option('prefix') / 'lib')
endif

# ========== tests & benchmark

subdir('testdata')
