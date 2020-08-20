# FGλT: Fast Graphlet Transform

## Getting started 

### System environment 

The FGλT library has been tested under Ubuntu 18.04 and macOS Catalina
v10.15.6. The only prerequisite is a `C++` compiler (optionally, with `cilk` support, see [Installation](#installation))

### Installation 

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

### Usage demo

The FGλT executable is named `fglt`. Usage:
    
    fglt <filename>
    
where `<filename>` is the path to a sparse matrix stored in symmetric,
coordinate, MatrixMarket format. The graphlet frequencies are exported
in `freq_net.txt`. For example,

    wget https://suitesparse-collection-website.herokuapp.com/MM/Pajek/GD96_c.tar.gz --no-check-certificate
    tar -xzvf GD96_c.tar.gz
    fglt GD96_c/GD96_c.mtx
    less freq_net.txt

### MATLAB interface 

To build the `MATLAB` interface to FGλT, issue

    fgtmake
    
in `MATLAB` command window, under `MATLAB` directory.

A `MATLAB` demo script is provided under `MATLAB`:

    demo.m
    
which showcases the use of FGλT on a couple of test graphs.
