from mytest import fglt
from scipy.io import mmread

if __name__ == '__main__':
    # Code to obtain matrix A goes here
    # We will just load it from the file
    A = mmread('./GD96_c/GD96_c.mtx')

    # Pass the matrix in CSC format
    fn, f = fglt(A.tocsc())

    print(fn)