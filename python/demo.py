from fglt import fglt
from scipy.io import mmread

if __name__ == '__main__':
    # Code to obtain matrix A goes here
    # We will just load it from the file
    try:
        A = mmread('../testdata/s12.mtx')
    except:
        print('ERROR: File not found. Download again from GitHub project page.')
        exit()
        
    print('Starting Calculations')
    # Pass the matrix in CSC format
    fn, f = fglt(A.tocsc())
    print('Calculations Finished')

    # Do stuff with fn and f here...
    #
    #
