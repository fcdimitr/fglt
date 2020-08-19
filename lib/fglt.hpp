/*!
  \file   fglt.hpp
  \brief  

  <long description>

  \author Dimitris Floros
  \date   2020-08-18
*/


#ifndef FGLT_H_
#define FGLT_H_

#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <ctype.h>


// type definitions
#ifdef MX_COMPAT_32
typedef int mwSize;
typedef int mwIndex;
#else
typedef size_t    mwSize;         /* unsigned pointer-width integer */
typedef size_t    mwIndex;        /* unsigned pointer-width integer */
#endif

#define USAGE "usage: C = fgt (A)"

#define NGRAPHLET 16

int getWorkers();


  void compute
  (
   double **f,
   mwIndex *ii,
   mwIndex *jStart,
   mwSize n,
   mwSize m,
   mwSize np
   );

#endif /* FGLT_H_ */