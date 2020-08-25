project('fglt', 'cpp')

fglt_shared = shared_library('fglt', 'lib/fglt.cpp', version : '0.1.0', soversion : '0', install : true)

executable('fglt', 'src/fglt_mtx.cpp', link_with : fglt_shared)
