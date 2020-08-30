from fglt import fglt
from scipy.io import mmread

if __name__ == '__main__':
    # Code to obtain matrix A goes here
    # We will just load it from the file
    try:
        A = mmread('../build/GD96_c/GD96_c.mtx')
    except:
        print('ERROR: File GD96_c.mtx not found. Make sure you followed the previous instructions at Usage Demo.')
        exit()
        
    print('Starting Calculations')
    # Pass the matrix in CSC format
    fn, f = fglt(A.tocsc())
    print('Calculations Finished')

    # Do stuff with fn and f here...
    #
    #