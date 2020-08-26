/*!
  \file   fglt.cpp
  \brief  Fast Graphlet Transform source file

  \author Dimitris Floros
  \date   2020-08-18
*/

#ifdef HAVE_CONFIG_H
  #include "../config.h"
#endif

#ifdef HAVE_CILK_CILK_H
  #include <cilk/cilk.h>
  #include <cilk/cilk_api.h>
  #define FOR cilk_for
#else
  #define FOR for
#endif

#include "fglt.hpp"
#include <algorithm>

struct timeval tic(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv;
}
  
static double toc(struct timeval begin){
  struct timeval end;
  gettimeofday(&end, NULL);
  double stime = ((double) (end.tv_sec - begin.tv_sec) * 1000 ) +
    ((double) (end.tv_usec - begin.tv_usec) / 1000 );
  stime = stime / 1000;
  return(stime);
}



extern "C" int getWorkers(){
#ifdef HAVE_CILK_CILK_H
  return __cilkrts_get_nworkers();
#else
  return 1;
#endif
}

static void remove_neighbors
(
 int *isNgbh,
 mwIndex i,
 mwIndex *ii,
 mwIndex *jStart
){

  // --- remove neighbors
  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){

    // get the column (k)
    mwIndex k = ii[id_i];

    isNgbh[k] = 0;
  }
  
}


static void raw2net
(
 double        ** const f,
 double  const ** const d,
 mwIndex const          i
){
  f[ 0][i]  =  d[ 0][i];
  f[ 1][i]  =  d[ 1][i];
  f[ 2][i]  =  d[ 2][i] -  2 * d[ 4][i];
  f[ 3][i]  =  d[ 3][i] -      d[ 4][i];
  f[ 4][i]  =  d[ 4][i];
  f[ 5][i]  =  d[ 5][i] -  2 * d[ 9][i] -      d[10][i] -  2 * d[12][i] +  4 * d[13][i] +  2 * d[14][i] -  6 * d[15][i];
  f[ 6][i]  =  d[ 6][i] -      d[10][i] -  2 * d[11][i] -  2 * d[12][i] +  2 * d[13][i] +  4 * d[14][i] -  6 * d[15][i];
  f[ 7][i]  =  d[ 7][i] -      d[ 9][i] -      d[10][i] +  2 * d[13][i] +      d[14][i] -  3 * d[15][i];
  f[ 8][i]  =  d[ 8][i] -      d[11][i] +      d[14][i] -      d[15][i];
  f[ 9][i]  =  d[ 9][i] -  2 * d[13][i] +  3 * d[15][i];
  f[10][i]  =  d[10][i] -  2 * d[13][i] -  2 * d[14][i] +  6 * d[15][i];
  f[11][i]  =  d[11][i] -  2 * d[14][i] +  3 * d[15][i];
  f[12][i]  =  d[12][i] -      d[13][i] -      d[14][i] +  3 * d[15][i];
  f[13][i]  =  d[13][i] -  3 * d[15][i];
  f[14][i]  =  d[14][i] -  3 * d[15][i];
  f[15][i]  =  d[15][i];
}


static void compute_all_available
(
 double **f,
 mwIndex i,
 double *t00,
 double *t01,
 double *t04
){

  f[0][i]   = 1;
  f[3][i]   = f[1][i] * ( f[1][i] - 1 ) * 0.5;
  f[6][i]   = f[2][i]*t01[i] - 2*f[4][i];
  f[8][i]   = f[1][i]*t04[i] / 3;
  f[11][i]  = t00[i] * f[4][i];
}

static void compute_d13
(
 double *f13_i,
 double *c3,
 mwIndex i,
 mwIndex *jStart,
 mwIndex *ii,
 int *isNgbh
 ){

  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){
    mwIndex k = ii[id_i];

    if (c3[id_i] == 0) continue;

    for (mwIndex id_k = jStart[k]; id_k < jStart[k+1]; id_k++){

      // get the column (j)
      mwIndex j = ii[id_k];

      if (j > k || c3[id_k] == 0) continue;

      if (isNgbh[j]) {
        f13_i[0] += c3[id_k]-1;
      }
        
    }
      
  }

}


static void intersection(int *joint, int *arr1, int *arr2, int m, int n) 
{ 
  int i = 0, j = 0, k = 0; 
  while (i < m && j < n) 
  { 
    if (arr1[i] < arr2[j]) 
      i++; 
    else if (arr2[j] < arr1[i]) 
      j++; 
    else /* if arr1[i] == arr2[j] */
    { 
      joint[k++] = arr2[j++]; 
      i++; 
    } 
  } 
} 

static void compute_k4
(
 double *f15,
 mwIndex i,
 mwIndex *jStart,
 mwIndex *ii,
 int *isNgbh,
 mwIndex *k4cmn
){

  // --- compute K_4
  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){

    // working with edge (i,j)
    mwIndex j = ii[id_i];

    if (j < i) continue;

    // counter for common nodes
    mwIndex cntCmn = 0;

    // collect common
    for (mwIndex id_j = jStart[j]; id_j < jStart[j+1]; id_j++){
      // get the column (j)
      mwIndex k = ii[id_j];

      if (k < j) continue;
      
      // if common to (i) and (j) add to list
      if (isNgbh[k]) {
        k4cmn[cntCmn++] = k;
        isNgbh[k] = -1;
      }

    }

    // check every combination
    for (mwIndex k_1 = 0; k_1 < cntCmn; k_1++){
      mwIndex k = k4cmn[k_1];
      for (mwIndex id_l = jStart[k]; id_l < jStart[k+1]; id_l++){
        mwIndex l = ii[id_l];

        if (l < k) continue;

        if (isNgbh[l] == -1) {
          f15[i]++;
          f15[j]++;
          f15[k]++;
          f15[l]++;
        }
        
      }
    }

    for (mwIndex k_1 = 0; k_1 < cntCmn; k_1++) isNgbh[k4cmn[k_1]] = 1;
          
  }

  // f15_i[0] /= 6;
  
}

static void spmv_second_pass
(
 double *f5_i,
 double *f9_i,
 double *f2,
 double *f4,
 double *t02,
 mwIndex i,
 mwIndex *jStart,
 mwIndex *ii,
 int *isNgbh
){

  // --- loop through every nonzero element A(i,k)
  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){
    mwIndex k = ii[id_i];
    f5_i[0] += f2[k];
    f9_i[0] += f4[k];

    isNgbh[k] = 1;
      
  }

  f5_i[0] -= t02[i] + 2*f4[i];
  f9_i[0] -= 2 * f4[i];
  
}

static void spmv_first_pass
(
 double *f2_i,
 double *f7_i,
 double *f1,
 double *t04,
 mwIndex i,
 mwIndex *jStart,
 mwIndex *ii
){

  // --- loop through every nonzero element A(i,k)
  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){

    // get the column (k)
    mwIndex k = ii[id_i];
      
    // --- matrix-vector products
    f2_i[0] += f1[k];
    f7_i[0] += t04[k];
      
  }

  f2_i[0]  -= f1[i];
  
}

static void p2
(
 double *f4_i,
 double *f10_i,
 double *f12_i, 
 double *f14_i,
 double *c3,
 double *t00,
 mwIndex i,
 mwIndex *jStart,
 mwIndex *ii,
 double *fl,
 int *pos,
 int *isNgbh,
 mwIndex *isUsed
){

  // setup the count of nonzero columns (j) visited for this row (i)
  mwIndex cnt = 0;

  // --- loop through every nonzero element A(i,k)
  for (mwIndex id_i = jStart[i]; id_i < jStart[i+1]; id_i++){

    // get the column (k)
    mwIndex k = ii[id_i];

    isNgbh[k] = id_i+1;
      
    // --- loop through all nonzero elemnts A(k,j)
    for (mwIndex id_k = jStart[k]; id_k < jStart[k+1]; id_k++){

      // get the column (j)
      mwIndex j = ii[id_k];

      if (i == j) continue;

      // if this column is not visited yet for this row (i), then set it
      if (!isUsed[j]) {
        fl[j]      = 0;  // initialize corresponding element
        isUsed[j]  = 1;  // set column as visited
        pos[cnt++] = j;  // add column position to list of visited
      }

      // increase count of A(i,j)
      fl[j]++;
        
    }

  }

  // --- perform reduction on [cnt] non-empty columns (j) 
  for (mwIndex l=0; l<cnt; l++) {

    // get next column number (j)
    mwIndex j = pos[l];

    // reduction
    f12_i[0] += (fl[j] * (fl[j]-1) );

    if (isNgbh[j]) {
      c3[isNgbh[j]-1]  = fl[j];
        
      f4_i[0]  += fl[j];
      f10_i[0] += fl[j]*t00[j];
      f14_i[0] += (fl[j] * fl[j]);
    }
      
    // declare it non-used
    isUsed[j] = 0;
  }

  f4_i[0]  /= 2;
  f12_i[0] /= 2;

  f14_i[0] /= 2;
  f14_i[0] -= f4_i[0];
    
}

static int all_nonzero
(
 double **f,
 mwIndex i
 ){               

  for (int d = 0; d < NGRAPHLET-1; d++)
    if (f[d][i] == 0) return 0;

  return 1;
  
}
  


extern "C" int compute
(
 double ** const f,
 double ** const fn,
 mwIndex *ii,
 mwIndex *jStart,
 mwSize n,
 mwSize m,
 mwSize np
 ){

  struct timeval timer_all = tic();

  


  // --- setup helpers
  double *t00 = (double *) calloc( n, sizeof(double) );
  double *t01 = (double *) calloc( n, sizeof(double) );
  double *t02 = (double *) calloc( n, sizeof(double) );
  double *t04 = (double *) calloc( n, sizeof(double) );

  if ( t00 == NULL || t01 == NULL || t02 == NULL || t04 == NULL ){
    printf( "Working memory allocation failed at helpers, aborting...\n" );
    return 1;
  }
    


  FOR (mwSize i=0;i<n;i++) {
    // get degree of vertex (i)
    f[1][i] = jStart[i+1] - jStart[i];
    t00[i]  = f[1][i] - 2;
    t01[i]  = f[1][i] - 1;
    t02[i]  = f[1][i] * t01[i];
    t04[i]  = (t00[i] * t01[i]) / 2;
    
  }
  
  
  // --- setup auxilliary vectors (size n)
  double *fl = (double *) calloc( n*np, sizeof(double) );
  int *pos = (int *) calloc( n*np, sizeof(int) );
  mwIndex *isUsed    = (mwIndex *) calloc( n*np, sizeof(mwIndex) );
  
  double *c3 = (double *) calloc( m, sizeof(double) );
  int *isNgbh = (int *) calloc( n*np, sizeof(int) );

  if ( fl == NULL || pos == NULL || isUsed == NULL || c3 == NULL || isNgbh == NULL ){
    printf( "Working memory allocation failed at auxilliary vectors, aborting...\n" );
    return 1;
  }
  
  // --- first pass
  FOR (mwIndex i=0; i<n;i++) {
#ifdef HAVE_CILK_CILK_H
    int ip = __cilkrts_get_worker_number();
#else
    int ip = 0;
#endif


    // d_4 d_10 d_12 d_14
    p2(  &f[4][i], &f[10][i], &f[12][i], &f[14][i],
         c3, t00, i, jStart, ii,
         &fl[ip*n], &pos[ip*n], &isNgbh[ip*n], &isUsed[ip*n] );

    
    // d_2 d_7
    spmv_first_pass( &f[2][i], &f[7][i], f[1], t04, i, jStart, ii );

    
    // d_3 d_6 d_8 d_11
    compute_all_available(f, i, t00, t01, t04);
    remove_neighbors(&isNgbh[ip*n], i, ii, jStart);
        

    
  }

  free(fl);
  free(pos);
  free(isUsed);

  free(t00);
  free(t01);

  free(t04);

  mwIndex *k4cmn   = (mwIndex *) calloc( n*np, sizeof(mwIndex) );
  double  *k4num   = (double *)  calloc( n*np, sizeof(mwIndex) );

  if ( k4cmn == NULL || k4num == NULL ){
    printf( "Working memory allocation failed at K_4 auxilliary vectors, aborting...\n" );
    return 1;
  }
  
  
  // --- second pass
  FOR (mwIndex i=0; i<n;i++) {
#ifdef HAVE_CILK_CILK_H
    int ip = __cilkrts_get_worker_number();
#else
    int ip = 0;
#endif

    
    // d_5 d_9
    spmv_second_pass( &f[5][i], &f[9][i], f[2], f[4], t02, i, jStart, ii, &isNgbh[ip*n] );

    
    // d_13
    compute_d13( &f[13][i], c3, i, jStart, ii, &isNgbh[ip*n] );

    
    // d_15 (only if all others are nonzero)
    if ( all_nonzero(f, i) )
      compute_k4( &k4num[ip*n], i, jStart, ii,
                  &isNgbh[ip*n], &k4cmn[ip*n] );    
    
    remove_neighbors(&isNgbh[ip*n], i, ii, jStart);
    
    
    
  }

  // merge k4 counts
  FOR (mwIndex i=0; i<n;i++){

#ifdef HAVE_CILK_CILK_H
    int ip = __cilkrts_get_worker_number();
#else
    int ip = 0;
#endif
    
    for (mwIndex ip=0; ip<np;ip++)
      f[15][i] += k4num[ip*n + i];

    
    // transform to net
    raw2net( (double ** const) fn, (double const ** const) f, i );

    
  }
  
  free(isNgbh);
  free(k4cmn);
  free(k4num);

  free(t02);
  free(c3);

  printf( "Total elapsed time: %.4f sec\n", toc( timer_all ) );
  
  return 0;
  
}
