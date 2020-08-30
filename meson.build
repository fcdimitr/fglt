project('fglt', 'cpp',
        version : '1.0.0',
        default_options: ['buildtype=release'] )

cc = meson.get_compiler('cpp')

opt_dep = cc.has_header('cilk/cilk.h') and cc.has_argument('-fcilkplus')
if opt_dep
   add_global_arguments(['-fcilkplus', '-DHAVE_CILK_CILK_H'], language : 'cpp')
   extralink = '-lcilkrts'
else
  extralink = ''
endif

fglthpp = configure_file(copy: true,
                         input: 'lib/fglt.hpp',
                         output: 'fglt.hpp')

install_headers('lib/fglt.hpp')

fglt_static = static_library('fglt', 'lib/fglt.cpp',
                             link_args: extralink,
                             install : true)

fglt_shared = shared_library('fglt', 'lib/fglt.cpp',
                             soversion : '0',
                             link_args: extralink,
                             install : true)

e = executable('fglt', 'src/fglt_mtx.cpp',
           link_with : fglt_shared,
           install : true)

# tests

t1 = find_program( 'testdata/test_s6.sh')
t2 = find_program( 'testdata/test_s12.sh')
test('Validation on s6 synthetic graph', t1, is_parallel : false)
test('Validation on s12 synthetic graph', t2, is_parallel : false)
