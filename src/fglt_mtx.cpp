/*!
  \file   fglt_mtx.cpp
  \brief  Run FGλT on Matrix-Market arrays.

  \author Dimitris Floros
  \date   2020-08-19
*/


#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>

#include "../lib/fglt.hpp"

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void readMTX
(
 mwIndex       **       row,
 mwIndex       **       col,
 mwSize         * const n,
 mwSize         * const m,
 char    const  * const filename
){

  // ~~~~~~~~~~ variable declarations
  mwIndex *row_coo, *col_coo;
  mwSize  n_col, m_mat;
  char mmx[20], b1[20], b2[20], b3[20], b4[20];
  bool issymmetric = false;
  
  // ~~~~~~~~~~ read matrix
  
  // open the file
  std::ifstream fin( filename );

  // check if file exists
  if( fin.fail() ){
    std::cerr << "File " << filename << " could not be opened! Aborting..." << std::endl;
    exit(1);
  }

  // read banner
  fin >> mmx >> b1 >> b2 >> b3 >> b4;

  // parse banner
  switch ( str2int(b1) ) {
  case str2int( "matrix" ):
     break;
  default:
    std::cerr << "Currently works only with 'matrix' option, aborting..." << std::endl;
    exit(1);
    break;
  }

  switch ( str2int(b2) ) {
  case str2int( "coordinate" ):
     break;
  default:
    std::cerr << "Currently works only with 'coordinate' option, aborting..." << std::endl;
    exit(1);
    break;
  }
  
  switch ( str2int(b3) ) {
  case str2int( "pattern" ):
    break;
  default:
    std::cerr << "Currently works only with 'pattern' format, aborting..." << std::endl;
    exit(1);
    break;
  }

  switch ( str2int(b4) ) {
  case str2int( "symmetric" ):
    issymmetric = true;
    break;
  }



  // ignore headers and comments
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (fin.peek() == '%') fin.ignore(2048, '\n');

  // read defining parameters
  fin >> n[0] >> n_col >> m[0];

  if (issymmetric) m_mat = 2*m[0];
  else             m_mat = m[0];
  
  assert( n[0] == n_col );

  // allocate space for COO format
  row_coo = static_cast<mwIndex *>( malloc(m_mat * sizeof(mwIndex)) );
  col_coo = static_cast<mwIndex *>( malloc(m_mat * sizeof(mwIndex)) );
  
  // read the COO data
  mwIndex k = 0;
  for (mwIndex l = 0; l < m[0]; l++){
    fin >> row_coo[k] >> col_coo[k];
    if (issymmetric)
      if (row_coo[k] == col_coo[k])  m_mat -= 2; // we do not keep self-loop, remove edges
      else { row_coo[k+1] = col_coo[k]; col_coo[k+1] = row_coo[k]; k += 2; } // put symmetric edge
    else
      if (row_coo[k] == col_coo[k])  m_mat -= 1; // we do not keep self-loop, remove edge
      else k++;
  }

  m[0] = m_mat;
  row_coo =static_cast<mwIndex *>( realloc( row_coo, m[0] * sizeof(mwIndex) ) );
  col_coo =static_cast<mwIndex *>( realloc( col_coo, m[0] * sizeof(mwIndex) ) );

  // close connection to file
  fin.close();

  // ~~~~~~~~~~ transform COO to CSC
  row[0] = static_cast<mwIndex *>( malloc( m[0]   * sizeof(mwIndex)) );
  col[0] = static_cast<mwIndex *>( calloc( (n[0]+1),  sizeof(mwIndex)) );

  // ----- find the correct column sizes
  for (mwSize l = 0; l < m[0]; l++){            
    col[0][ col_coo[l]-1 ]++;
  }
  
  for(mwSize i = 0, cumsum = 0; i < n[0]; i++){     
    int temp = col[0][i];
    col[0][i] = cumsum;
    cumsum += temp;
  }
  col[0][n[0]] = m[0];
  
  // ----- copy the row indices to the correct place
  for (mwSize l = 0; l < m[0]; l++){
    int col_l = col_coo[l]-1;
    int dst = col[0][col_l];
    row[0][dst] = row_coo[l]-1;
    
    col[0][ col_l ]++;
  }
  
  // ----- revert the column pointers
  for(mwSize i = 0, last = 0; i < n[0]; i++) {     
    int temp = col[0][i];
    col[0][i] = last;

    last = temp;
  }

  // ~~~~~~~~~~ deallocate memory
  free( row_coo );
  free( col_coo );

}


std::ostream& output(std::ostream& outfile, double** arr, int rows, int cols) {

  outfile
    << "\"Node id (0-based)\","
    << "\"[0] vertex (==1)\","
    << "\"[1] degree\","
    << "\"[2] 2-path\","
    << "\"[3] bifork\","
    << "\"[4] 3-cycle\","
    << "\"[5] 3-path, end\","
    << "\"[6] 3-path, interior\","
    << "\"[7] claw, leaf\","
    << "\"[8] claw, root\","
    << "\"[9] paw, handle\","
    << "\"[10] paw, base\","
    << "\"[11] paw, center\","
    << "\"[12] 4-cycle\","
    << "\"[13] diamond, off-cord\","
    << "\"[14] diamond, on-cord\","
    << "\"[15] 4-clique\""
    << std::endl;
  
  for (int i = 0; i < rows; i++){
    outfile << i << ",";
    for(int j = 0; j < cols-1; j++)
      outfile << arr[j][i] << ",";
    outfile << arr[cols-1][i] << std::endl;
  }
  return outfile;
}


int main(int argc, char **argv)
{

  // ~~~~~~~~~~ variable declarations
  mwIndex *row, *col;
  mwSize  n, m, np;
  std::string filename = "graph.mtx";

  // ~~~~~~~~~~ parse inputs

  // ----- retrieve the (non-option) argument:
  if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
    // there is NO input...
    std::cout << "No filename provided, using 'graph.mtx'." << std::endl;
  }
  else {
    // there is an input...
    filename = argv[argc-1];
    std::cout << "Using graph stored in '" << filename << "'." << std::endl;
  }
  
  readMTX( &row, &col, &n, &m, filename.c_str() );

  double **f  = (double **) malloc(NGRAPHLET*sizeof(double *));
  double **fn = (double **) malloc(NGRAPHLET*sizeof(double *));

  for (int igraph = 0; igraph < NGRAPHLET; igraph++){
    f [igraph] = (double *) calloc( n, sizeof(double) );
    fn[igraph] = (double *) calloc( n, sizeof(double) );
  }

  np = getWorkers();
  compute(f,fn,row,col,n,m,np);

  std::cout << "Computation complete, outputting frequency counts to 'freq_net.csv'" << std::endl;
  
  // output
  std::fstream ofnet("freq_net.csv", std::ios::out );

  if ( ofnet.is_open() ){
    output( ofnet, fn, n, NGRAPHLET );
  }

  std::cout << "Finished, cleaning up..." << std::endl;
  
  for (int igraph = 0; igraph < NGRAPHLET; igraph++){
    free(f [igraph]);
    free(fn[igraph]);
  }
  
  free( f );
  free( fn );
  free( row );
  free( col );
  
}
