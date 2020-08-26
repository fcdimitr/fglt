# FGλT <br/> Fast Graphlet Transform

[![DOI](http://joss.theoj.org/papers/10.21105/joss.01577/status.svg)](https://doi.org/10.21105/joss.01577)
[![DOI](https://zenodo.org/badge/196885143.svg)](https://zenodo.org/badge/latestdoi/196885143)
[![GitHub license](https://img.shields.io/github/license/fcdimitr/fglt.svg)](https://github.com/fcdimitr/flgt/blob/master/LICENCE)
[![GitHub issues](https://img.shields.io/github/issues/fcdimitr/fglt.svg)](https://github.com/fcdimitr/fglt/issues/)

-   [Summary](#overview)
-   [Getting started](#getting-started)
    -   [System environment](#system-environment)
    -   [Installation](#installation)
    -   [Usage demo](#usage-demo)
    -   [MATLAB interface](#matlab-interface)
-   [License and community guidelines](#license-and-community-guidelines)
-   [Contributors](#contributors)

# Summary

We introduce...

![](figs/table-overview.png)

# Getting started 

## System environment 

The FGλT library has been tested under Ubuntu 18.04 and macOS Catalina
v10.15.6. The only prerequisite is a `C++` compiler (optionally, with `cilk` support, see [Installation](#installation))

## Installation 

To generate the FGλT library and program:

    mkdir build; cd build
    ../configure
    make all

To specify the `C++` compiler:

    ./configure CXX=<compiler-executable>

*Note*: If the specified compiler supports `cilk`, the compiled
program will automatically use `cilk` for parallelism. Otherwise, the
program will run in sequential mode.

If you wish to install the executable `fglt`, issue:

    make install
    
*Note*: Depending on your setup, you might need `sudo` privileges for
this operation.

To generate the documentation (assuming `Doxygen` is installed on your
machine):

    cd docs
    make
    open html/index.html


## Usage demo

The FGλT executable is named `fglt`. Usage:
    
    fglt <filename>
    
where `<filename>` is the path to a sparse matrix stored in symmetric,
coordinate, MatrixMarket format. The graphlet frequencies are exported
in `freq_net.txt`. For example,

    wget https://suitesparse-collection-website.herokuapp.com/MM/Pajek/GD96_c.tar.gz --no-check-certificate
    tar -xzvf GD96_c.tar.gz
    fglt GD96_c/GD96_c.mtx
    less freq_net.csv

## MATLAB interface 

To build the `MATLAB` interface to FGλT, issue

    fgtmake
    
in `MATLAB` command window, under `MATLAB` directory.

A `MATLAB` demo script is provided under `MATLAB`:

    demo.m
    
which showcases the use of FGλT on a couple of test graphs.

# Building with Meson

You can use [Meson](mesonbuild.com) to build a shared library and link the demo executable against it.
You need to build the shared library to use FGλT with Julia or Python.

After installing meson and ninja, you can simply run:

    meson build
    cd build
    ninja
    sudo ninja install # optional: install the shared library system-wide

# License and community guidelines 

The FGlT library is licensed under the [GNU general public
license v3.0](https://github.com/fcdimitr/fglt/blob/master/LICENSE).
To contribute to FGlT or report any problem, follow our
[contribution
guidelines](https://github.com/fcdimitr/fglt/blob/master/CONTRIBUTING.md)
and [code of
conduct](https://github.com/fcdimitr/fglt/blob/master/CODE_OF_CONDUCT.md).

# Contributors 

*Design and development*:\
Dimitris Floros<sup>1</sup>, Nikos Pitsianis<sup>1,2</sup>, 
Xiaobai Sun<sup>2</sup>\

*Development of Julia and Python wrappers*:\
Jason Barmparesos<sup>1</sup>

<sup>1</sup> Department of Electrical and Computer Engineering,
Aristotle University of Thessaloniki, Thessaloniki 54124, Greece\
<sup>2</sup> Department of Computer Science, Duke University, Durham, NC
27708, USA
