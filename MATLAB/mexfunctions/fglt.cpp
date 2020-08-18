#include <fglt.hpp>

#include "mex.h"

#define ERROR(message)                                      \
{                                                           \
    mexErrMsgIdAndTxt ("GrB:error", message) ;              \
}



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

  // set threads
  if (nargin > 1) setWorkers( (int) mxGetScalar(pargin[1]) );

  np[0] = getWorkers();
  // printf( "workers: %d\n", np[0] );
  
}

void mexFunction
(
 int nargout,
 mxArray *pargout [ ],
 int nargin,
 const mxArray *pargin [ ]
 )
{

  usage_info (nargin <= 2 && nargout <=4, USAGE) ;


  mwIndex *ii, *jStart;
  double **f = (double **) malloc(NGRAPHLET*sizeof(double *));
  mwSize n, m, np;
  double **t = (double **) malloc(NTIME*sizeof(double *));
  double **pid = (double **) malloc(NPASS*sizeof(double *));
  double *totTime;
  
  parseInputs( &ii, &jStart, &n, &m, &np, pargin, nargin );
  
  pargout[0] = mxCreateDoubleMatrix(n, NGRAPHLET, mxREAL);
  for (int igraph = 0; igraph < NGRAPHLET; igraph++)
    f[igraph] = &( (mxGetPr(pargout[0]))[igraph*n] );

  if ( nargout > 1 ){
    pargout[1] = mxCreateDoubleMatrix(n, NTIME, mxREAL);
    for (int igraph = 0; igraph < NTIME; igraph++)
      t[igraph] = &( (mxGetPr(pargout[1]))[igraph*n] );
  } else {
    for (int igraph = 0; igraph < NTIME; igraph++)
      t[igraph] = NULL;
  }

  if ( nargout > 2 ){
    pargout[2] = mxCreateDoubleMatrix(n, NPASS, mxREAL);
    for (int ipass = 0; ipass < NPASS; ipass++)
      pid[ipass] = &( (mxGetPr(pargout[2]))[ipass*n] );
  } else {
    for (int ipass = 0; ipass < NPASS; ipass++)
      pid[ipass] = NULL;
  }

  if ( nargout > 3 ){
    pargout[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
    totTime = mxGetPr(pargout[3]);
  } else {
    totTime = NULL;
  }

  struct timeval timer = tic();
  compute( f, t, pid, ii, jStart, n, m, np );
  if (totTime) totTime[0] = toc( timer );
  
  free( f );
  free( t );
  free( pid );
  
}
