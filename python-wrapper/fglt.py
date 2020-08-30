import ctypes
import pathlib
import numpy as np
from scipy.io import mmread
from scipy.sparse import isspmatrix_csc

def fglt(A):
    # # Convert input matrix to CSC format
    # A = A.tocsc()

    # Check that input is sparse matrix in CSC format
    if not isspmatrix_csc(A):
        print('ERROR: Input must be a sparse matrix in CSC format(scipy.sparse.csc.csc_matrix)')
        exit()

    # Check that input is symmetric matrix
    if (A != A.T).nnz != 0:
        print('ERROR: Input must be a symmetric matrix')
        exit()

    # Check that input matrix is binary(only 1s and 0s)
    if not all(A.data == 1):
        print('Error: Input must be a binary matrix, with either 1s or 0s')
        exit()

    # Check that input matrix is zero in the diagonal
    if A.diagonal().any():
        print('Error: Input must be zero in the diagonal')
        exit()
        
    # Shared library location
    libname =  "../build/libfglt.so"
    try:
        c_lib = ctypes.CDLL(libname)
    except:
        print('ERROR: libfglt.so file not found. Make sure you followed the build instructions correctly')
        exit()

    ### Prepare arguments for C++ function. For detailed documentation
    ### see 'lib/fglt.h' and 'lib/fglt.cpp'
    # Column indices of adjacency matrix
    ii = A.indices.tolist()
    ii = (ctypes.c_size_t * len(ii))(*ii)
    # The first non-zero row index of each column.
    jStart = A.indptr.tolist()
    jStart = (ctypes.c_size_t * len(jStart))(*jStart)
    # Number of columns of A
    nValue = A.shape[0]
    n = ctypes.c_size_t(nValue)
    # Number of zeros of A
    m = ctypes.c_size_t(A.nnz)
    # Number of parallel workers(always 1)
    npw = ctypes.c_size_t(1)
    # Output matrix of raw frequencies (nx16)
    fn = ((ctypes.c_double*nValue)*16)()
    # Proper way to pass 2D array to C++, see here:
    # https://stackoverflow.com/questions/36579885/using-ctypes-to-pass-2d-array-of-ints-from-python-to-c
    p_fn = (ctypes.POINTER(ctypes.c_double)*nValue)(*fn)
    # Output matrix of net frequencies (nx16)
    f =  ((ctypes.c_double*nValue)*16)()
    p_f = (ctypes.POINTER(ctypes.c_double)*nValue)(*f)

    # Call the C++ function
    c_lib.compute(ctypes.byref(p_f), ctypes.byref(p_fn), ii, jStart, n, m, npw)

    # Prepare the values to return
    fn_ret = np.zeros((nValue, 16))
    f_ret  = np.zeros((nValue, 16))
    for i in range(nValue):
        for j in range(16):
            fn_ret[i][j] = p_fn[j][i]
            f_ret[i][j]  = p_f[j][i]

    return fn_ret, f_ret
