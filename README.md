# FGλT <br/> Fast Graphlet Transform

[![DOI](http://joss.theoj.org/papers/10.21105/joss.01577/status.svg)](https://doi.org/10.21105/joss.01577)
[![DOI](https://zenodo.org/badge/196885143.svg)](https://zenodo.org/badge/latestdoi/196885143)
[![GitHub license](https://img.shields.io/github/license/fcdimitr/fglt.svg)](https://github.com/fcdimitr/flgt/blob/master/LICENCE)
[![GitHub issues](https://img.shields.io/github/issues/fcdimitr/fglt.svg)](https://github.com/fcdimitr/fglt/issues/)

-   [Summary](#overview)
-   [Getting started](#getting-started)
    -   [System environment](#system-environment)
    -   [Installation](#installation)
    -   [MATLAB interface](#matlab-interface)
    -   [Usage demo](#usage-demo)
-   [License and community guidelines](#license-and-community-guidelines)
-   [Contributors](#contributors)

# Summary

We introduce...

# Getting started 

## System environment 

The FGλT library has been tested under Ubuntu 18.04 and macOS Catalina
v10.15.6. The only prerequisite is a `C++` compiler (optionally, with `cilk` support, see [Installation](#installation))

## Installation 

To generate the FGλT library:

    mkdir build; cd build
    ../configure
    make all

To specify the `C++` compiler:

    ./configure CXX=<compiler-executable>

*Note*: If the specified compiler supports `cilk`, the compiled
program will automatically use `cilk` for parallelism. Otherwise, the
program will run in sequential mode.

## MATLAB interface 

To build the `MATLAB` interface to FGλT, issue

    fgtmake
    
in `MATLAB` command window, under `MATLAB` directory.

## Usage demo 

A `MATLAB` demo script is provided under `MATLAB`:

    demo.m
    
which showcases the use of FGλT on a couple of test graphs.

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
<sup>1</sup> Department of Electrical and Computer Engineering,
Aristotle University of Thessaloniki, Thessaloniki 54124, Greece\
<sup>2</sup> Department of Computer Science, Duke University, Durham, NC
27708, USA
