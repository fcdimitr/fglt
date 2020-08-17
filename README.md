# FGlT <br/> Swift Neighbor Embedding of Sparse Stochastic Graphs

[![DOI](http://joss.theoj.org/papers/10.21105/joss.01577/status.svg)](https://doi.org/10.21105/joss.01577)
[![DOI](https://zenodo.org/badge/196885143.svg)](https://zenodo.org/badge/latestdoi/196885143)
[![GitHub license](https://img.shields.io/github/license/fcdimitr/fglt.svg)](https://github.com/fcdimitr/flgt/blob/master/LICENCE)
[![GitHub issues](https://img.shields.io/github/issues/fcdimitr/fglt.svg)](https://github.com/fcdimitr/fglt/issues/)

-   [Summary](#overview)
-   [Getting started](#getting-started)
    -   [System environment](#system-environment)
    -   [Prerequisites](#prerequisites)
    -   [Installation](#installation)
        -   [Basic instructions](#basic-instructions)
        -   [Support of the conventional t-SNE](#support-of-the-conventional-t-sne)
        -   [MATLAB interface](#matlab-interface)
    -   [Usage demo](#usage-demo)
-   [License and community guidelines](#license-and-community-guidelines)
-   [Contributors](#contributors)

# Summary

We introduce SG-t-SNE-<img src="svgs/0c4cdff2a5c675458f5a6629892c26d1.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/>, a high-performance software for swift
embedding of a large, sparse, stochastic graph
<img src="svgs/4ad232c35b5cd188a13d128bb2c1eecc.svg" align=middle width=103.24177049999999pt height=24.65753399999998pt/> into a <img src="svgs/2103f85b8b1477f430fc407cad462224.svg" align=middle width=8.55596444999999pt height=22.831056599999986pt/>-dimensional space
(<img src="svgs/3fa1f779de09763d248814c0c4f40d07.svg" align=middle width=69.74298869999998pt height=22.831056599999986pt/>) on a shared-memory computer. The algorithm SG-t-SNE and the
software t-SNE-<img src="svgs/0c4cdff2a5c675458f5a6629892c26d1.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> were first described in Reference [[1](#Pitsianis2019)].
The algorithm is built upon precursors for embedding a <img src="svgs/63bb9849783d01d91403bc9a5fea12a2.svg" align=middle width=9.075367949999992pt height=22.831056599999986pt/>-nearest
neighbor (<img src="svgs/63bb9849783d01d91403bc9a5fea12a2.svg" align=middle width=9.075367949999992pt height=22.831056599999986pt/>NN) graph, which is distance-based and regular with
constant degree <img src="svgs/63bb9849783d01d91403bc9a5fea12a2.svg" align=middle width=9.075367949999992pt height=22.831056599999986pt/>. In practice, the precursor algorithms are also
limited up to 2D embedding or suffer from overly long latency in 3D
embedding. SG-t-SNE removes the algorithmic restrictions and enables
<img src="svgs/2103f85b8b1477f430fc407cad462224.svg" align=middle width=8.55596444999999pt height=22.831056599999986pt/>-dimensional embedding of arbitrary stochastic graphs, including, but
not restricted to, <img src="svgs/63bb9849783d01d91403bc9a5fea12a2.svg" align=middle width=9.075367949999992pt height=22.831056599999986pt/>NN graphs. SG-t-SNE-<img src="svgs/0c4cdff2a5c675458f5a6629892c26d1.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> expedites the
computation with high-performance functions and materializes 3D
embedding in shorter time than 2D embedding with any precursor algorithm
on modern laptop/desktop computers.

## Getting started 

### System environment 


### Prerequisites 

FGlT uses the following open-source software:

-   [FFTW3](http://www.fftw.org/) 3.3.8
	
-   [METIS](http://glaros.dtc.umn.edu/gkhome/metis/metis/overview) 5.1.0

-   [FLANN](https://www.cs.ubc.ca/research/flann/) 1.9.1

-   [Intel TBB](https://01.org/tbb) 2019

-   [Doxygen](http://www.doxygen.nl/) 1.8.14

On Ubuntu:

    sudo apt-get install libtbb-dev libflann-dev libmetis-dev libfftw3-dev doxygen

On macOS:

    sudo port install flann tbb metis fftw-3 doxygen

### Installation 

#### Basic instructions 

To generate the SG-t-SNE-<img src="svgs/0c4cdff2a5c675458f5a6629892c26d1.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> library, test and demo programs:

    ./configure
    make all

To specify the `C++` compiler:

    ./configure CXX=<compiler-executable>

To test whether the installation is successful:

    bin/test_modules

To generate the documentation:

    make documentation

#### MATLAB interface 

### Usage demo 

## License and community guidelines 

The FGlT library is licensed under the [GNU general public
license v3.0](https://github.com/fcdimitr/fglt/blob/master/LICENSE).
To contribute to FGlT or report any problem, follow our
[contribution
guidelines](https://github.com/fcdimitr/fglt/blob/master/CONTRIBUTING.md)
and [code of
conduct](https://github.com/fcdimitr/fglt/blob/master/CODE_OF_CONDUCT.md).

## Contributors 

*Design and development*:\
Dimitris Floros<sup>1</sup>, Nikos Pitsianis<sup>1,2</sup>, 
Xiaobai Sun<sup>2</sup>\
<sup>1</sup> Department of Electrical and Computer Engineering,
Aristotle University of Thessaloniki, Thessaloniki 54124, Greece\
<sup>2</sup> Department of Computer Science, Duke University, Durham, NC
27708, USA
