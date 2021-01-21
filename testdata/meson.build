# ----- small tests

t1 = find_program('test_s6.sh')
t2 = find_program('test_s12.sh')
test('Validation on s6 synthetic graph', t1, args : e, is_parallel : false)
test('Validation on s12 synthetic graph', t2, args : e, is_parallel : false)

# ----- benchmark

if get_option('enable_benchmark')

  id_bench = 'coPapersDBLP'

  fs = import('fs')
  if not fs.is_file(id_bench + '.mtx') # download and extract benchmark data

    dl_mtx = find_program('download_benchmark_mtx.sh')
    if not dl_mtx.found()
      warning('Could not find `testdata/download_benchmark_mtx.sh`, ' +
              'needed to download the benchmark adjacency matrix. ' +
              'Disabling `benchmark` target.')
    else
      message('Downloading and extracting ' + id_bench + '.mtx ' +
              'from the SuiteSparse matrix collection website.')
      dl_mtx_result = run_command(dl_mtx, [id_bench + '.tar.gz'])
      if dl_mtx_result.returncode() != 0
        warning('Something went wrong while configuring the ' + id_bench + ' data. ' +
                'The `benchmark` target may not work.')
      endif
    endif

  endif

  dat_bench = files(id_bench + '.mtx')
  benchmark('suitesparse/coPapersDBLP', e, args : dat_bench)

endif
