from fglt import fglt
from scipy.io import mmread
import errno
import os

if __name__ == '__main__':
    # Code to obtain matrix A goes here
    # We will just load it from the file
    dirname = os.path.dirname(__file__)
    filename = os.path.join(dirname, '../testdata/s12.mtx')
    try:
        A = mmread(filename)
    except FileNotFoundError:
        raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), filename +
                                ' ERROR: File not found. Download again from GitHub'
                                ' project page.')
    print('Starting Calculations')
    # Pass the matrix in CSC format
    fn, f = fglt(A.tocsc())
    print('Calculations Finished')

    # Do stuff with fn and f here...
    #
    #
