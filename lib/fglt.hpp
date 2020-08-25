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

#include <sys/time.h>

// type definitions
#ifdef MX_COMPAT_32
typedef int mwSize;
typedef int mwIndex;
#else
typedef size_t    mwSize;         /* unsigned pointer-width integer */
typedef size_t    mwIndex;        /* unsigned pointer-width integer */
#endif

#define NGRAPHLET 16

#ifdef __cplusplus
extern "C" {
#endif

int getWorkers();

void compute
  (
   double ** const f,
   double ** const fn,
   mwIndex *ii,
   mwIndex *jStart,
   mwSize n,
   mwSize m,
   mwSize np
   );

#ifdef __cplusplus
}
#endif

#endif /* FGLT_H_ */
