# FGlT <br/> Fast Graphlet Transform

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.4633459.svg)](https://doi.org/10.5281/zenodo.4633459)
[![GitHub license](https://img.shields.io/github/license/fcdimitr/fglt.svg)](https://github.com/fcdimitr/fglt/blob/master/LICENCE)
[![GitHub issues](https://img.shields.io/github/issues/fcdimitr/fglt.svg)](https://github.com/fcdimitr/fglt/issues/)
![ci_build](https://github.com/fcdimitr/fglt/workflows/ci_build/badge.svg)
![tests](https://github.com/fcdimitr/fglt/workflows/tests/badge.svg)

-   [Summary](#summary)
-   [Getting started](#getting-started)
    -   [System environment](#system-environment)
    -   [Prerequisites](#prerequisites)
    -   [Installation](#installation)
    -   [Testing](#testing)
    -   [Usage demo](#usage-demo)
    -   [Python 3](#python-3)
    -   [Julia](#julia)
    -   [MATLAB](#matlab)
-   [License and community guidelines](#license-and-community-guidelines)
-   [Contributors](#contributors)

# Summary

We provide `FGlT`, a `C/C++` multi-threading library, for Fast
Graphlet Transform of large, sparse, undirected networks/graphs. The
graphlets in dictionary Σ<sub>16</sub>, shown in
Figure 1, are used as encoding elements to capture
topological connectivity quantitatively and transform a graph
G=(V,E) into a |V| x 16 array of graphlet frequencies at all
vertices. The 16-element vector at each vertex represents the
frequencies of induced subgraphs, incident at the vertex, of the
graphlet patterns. The transformed data array serves multiple types of
network analysis: statistical or/and topological measures, comparison,
classification, modeling, feature embedding and dynamic variation,
among others. The library `FGlT` is distinguished in
the following key aspects.
(1) It is based on the [fast, sparse and exact transform formulas](https://arxiv.org/abs/2007.11111)
which are of the lowest time and space complexities
among known algorithms, and, at the same time, in ready form for
globally streamlined computation in matrix-vector operations.
(2) It leverages prevalent multi-core processors, with multi-threaded
programming in [`Cilk`](http://cilk.mit.edu), and uses sparse graph computation
techniques to deliver high-performance network analysis to individual
laptops or desktop computers.
(3) It has `Python`, `Julia`, and `MATLAB` interfaces for easy integration
with, and extension of, existing network analysis software.

![](figs/table-overview.png)

# Getting started 

## System environment 

The `FGlT` library has been tested under Ubuntu 18.04 and macOS Catalina
v10.15.6. The prerequisites is a `C++` compiler and the
[Meson](https://mesonbuild.com) package with [Ninja](https://ninja-build.org)
support. If the specified compiler supports `Cilk`, (e.g., the
[OpenCilk](https://opencilk.org) `clang` compiler, GNU `g++-7`, Intel `icpc`
versions prior to 2019, or Cilk Plus/LLVM `clang`), the compiled program will
run in parallel.

## Prerequisites

You can install `meson` and `ninja` issuing

    pip install meson
    pip install ninja

## Installation 

After installing `meson` and `ninja`, you can build `FGlT` in a `build`
directory:

    meson build
    meson compile -C build

To specify the `C++` compiler, set the `CXX` environment variable when
configuring the build directory. For example, to use the
[OpenCilk](https://opencilk.org) compiler, installed under `/usr/pkg/opencilk`,
you can issue the command:

    env CXX=/usr/pkg/opencilk/bin/clang++ meson build

If you wish to install system-wide the header files, libraries, and
the `fglt` executable, issue (after building `FGlT`):

    meson install -C build
    
*Note*: Depending on your setup, you might need `sudo` privileges for this
operation. To change the default installation prefix, specify the
`-Dprefix=/path/to/install/dir` option when configuring the build directory.

To generate the documentation (assuming `doxygen` is installed on your
machine):

    cd docs
    make
    open html/index.html

## Testing

To test whether installation was successful, issue

    ninja test
    
under `build` directory.

## Usage demo

The `FGlT` executable is named `fglt`. Usage:
    
    fglt <filename>
    
where `<filename>` is the path to a sparse matrix stored in symmetric,
coordinate, MatrixMarket format. The graphlet frequencies are exported
in the file `freq_net.csv`, within the working directory. For example,

    fglt ../testdata/s12.mtx
    less freq_net.csv

## Python 3

In order to run the `fglt()` C++ function we will need the `scipy` library:

    pip install scipy

A `Python` demo script is provided under the `python` directory, which can be invoked by:

    python demo.py
    
and showcases the use of `FGlT` on a couple of test graphs.

## Julia

You can use `FGlT` with Julia with the
[FGLT.jl](https://github.com/NorthSailor/FGLT.jl) package. Further
instructions and demo scripts are available within.

## MATLAB

To build the `MATLAB` interface to FGlT, issue

    fgltmake
    
in `MATLAB` command window, under `MATLAB` directory.

A `MATLAB` demo script is provided under `MATLAB`:

    demo.m
    
which showcases the use of `FGlT` on a couple of test graphs.

# License and community guidelines 

The `FGlT` library is licensed under the [GNU general public
license v3.0](https://github.com/fcdimitr/fglt/blob/master/LICENSE).
To contribute to FGlT or report any problem, follow our
[contribution
guidelines](https://github.com/fcdimitr/fglt/blob/master/CONTRIBUTING.md)
and [code of
conduct](https://github.com/fcdimitr/fglt/blob/master/CODE_OF_CONDUCT.md).

# Contributors 

*Design and development*:<br>
Dimitris Floros<sup>1</sup>, Nikos Pitsianis<sup>1,2</sup>, 
Xiaobai Sun<sup>2</sup>

*Development of Julia and Python wrappers*:<br>
Jason Barmparesos<sup>1</sup>, Konstantinos Kitsios<sup>1</sup>

*We also thank the following, for helpful comments and bug fixes*:<br>
George Bisbas


<sup>1</sup> Department of Electrical and Computer Engineering,
Aristotle University of Thessaloniki, Thessaloniki 54124, Greece<br>
<sup>2</sup> Department of Computer Science, Duke University, Durham, NC
27708, USA
