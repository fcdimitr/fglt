project('fglt', 'cpp',
        version : '1.0.0',
        default_options: ['buildtype=release'] )

cc = meson.get_compiler('cpp')

is_icpc     = cc.get_id() == 'intel' or cc.get_id() == 'intel-cl'
enable_cilk = cc.has_header('cilk/cilk.h') and ( is_icpc or cc.has_argument('-fcilkplus') )

if is_icpc
  add_global_arguments(['-wd3947,3946,10006,3950'], language : 'cpp')
endif

if get_option('prefer_openmp')
  dep_cilk = []
  warning('openMP selected')
else
  dep_cilk = dependency('cilkrts', required : false)

  if not dep_cilk.found()
    dep_cilk = cc.find_library( 'cilkrts', required : false,
                                has_headers : ['cilk/cilk.h',
                                               'cilk/cilk_api.h'] )
  endif

  if enable_cilk and dep_cilk.found()
    add_global_arguments(['-fcilkplus', '-DHAVE_CILK_CILK_H'], language : 'cpp')
    add_global_link_arguments(['-lcilkrts'], language : 'cpp')
  endif
endif

dep_openmp = dependency('openmp', language : 'cpp', required : false)

fglthpp = configure_file(copy: true,
                         input: 'lib/fglt.hpp',
                         output: 'fglt.hpp')

install_headers('lib/fglt.hpp')

fglt_static = static_library('fglt', 'lib/fglt.cpp',
                             dependencies : [dep_openmp, dep_cilk],
                             install : true)

fglt_shared = shared_library('fglt', 'lib/fglt.cpp',
                             soversion : '0',
                             dependencies : [dep_openmp, dep_cilk],
                             install : true)

e = executable('fglt', 'src/fglt_mtx.cpp',
               link_with : fglt_shared,
               dependencies : [dep_openmp, dep_cilk],
               install : true)

# tests

t1 = find_program( 'testdata/test_s6.sh')
t2 = find_program( 'testdata/test_s12.sh')
test('Validation on s6 synthetic graph', t1, is_parallel : false)
test('Validation on s12 synthetic graph', t2, is_parallel : false)
