/*!
  \file   fglt.hpp
  \brief  Header file containing basic function definitinos for FGlT

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

/*!
 * \brief Get the number of parallel workers available.
 *
 * \return The number of workers available. Always 1 when built without Cilk support.
 */
int getWorkers();

/*!
 * \brief Perform the FGLT transform.
 *
 * \param f [out] An array-of-pointers of size (n, 16) where the raw frequencies should be stored.
 * \param fn [out] An array-of-pointers of size (n, 16) where the net frequencies should be stored.
 * \param ii [in] The column indices of the adjacency matrix.
 * \param jStart [in] The first non-zero row index of each column.
 * \param n [in] The number of columns of the adjacency matrix.
 * \param m [in] The number of nonzero elements in the adjacency matrix.
 * \param np [in] The number of parallel workers to use for the transform.
 * \return status (0: success, otherwise error)
 */
int compute
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
