#include <fglt.hpp>

#include "mex.h"

#define ERROR(message)                                      \
{                                                           \
    mexErrMsgIdAndTxt ("GrB:error", message) ;              \
}

#define USAGE "usage: [Fnet, Fraw] = fgt (A) ; A must be sparse"

void usage_info       // check usage and make sure GrB.init has been called
(
    bool ok,                // if false, then usage is not correct
    const char *message     // error message if usage is not correct
)
{

  if (!ok) {
    ERROR (message) ;
  }

}


void parseInputs
(
 mwIndex **ii,
 mwIndex **jStart,
 mwSize *n,
 mwSize *m,
 mwSize *np,
 const mxArray *pargin [ ],
 const int nargin
){
  
  // column indices of A
  ii[0] = mxGetIr( pargin[0] );
    
  // starting index of each column
  jStart[0] = mxGetJc( pargin[0] );
    
  // number of columns in the matrix
  n[0]  = mxGetN( pargin[0] );

  // number of edges
  m[0] =  *(jStart[0] + n[0]);


  np[0] = getWorkers();
  
}

void mexFunction
(
 int nargout,
 mxArray *pargout [ ],
 int nargin,
 const mxArray *pargin [ ]
 )
{

  usage_info (nargin == 1 && nargout <=2 && mxIsSparse(pargin[0]) , USAGE) ;

  mwIndex *ii, *jStart;
  double **f  = (double **) malloc(NGRAPHLET*sizeof(double *));
  double **fn = (double **) malloc(NGRAPHLET*sizeof(double *));
  mwSize n, m, np;

  parseInputs( &ii, &jStart, &n, &m, &np, pargin, nargin );
  
  pargout[0] = mxCreateDoubleMatrix(n, NGRAPHLET, mxREAL);
  for (int igraph = 0; igraph < NGRAPHLET; igraph++)
    fn[igraph] = &( (mxGetPr(pargout[0]))[igraph*n] );

  if ( nargout > 1 ){
    pargout[1] = mxCreateDoubleMatrix(n, NGRAPHLET, mxREAL);
    for (int igraph = 0; igraph < NGRAPHLET; igraph++)
      f[igraph] = &( (mxGetPr(pargout[1]))[igraph*n] );
  } else {
    for (int igraph = 0; igraph < NGRAPHLET; igraph++)
      f[igraph] = (double *) calloc( n, sizeof(double) );
  }


  compute( f, fn, ii, jStart, n, m, np );
  

  if (nargout <= 1){
    for (int igraph = 0; igraph < NGRAPHLET; igraph++)
      free(f[igraph]);
  }
  
  free( f  );
  free( fn );

  
}
