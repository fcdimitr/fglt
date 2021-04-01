#!/bin/bash

MTX=${1:-coPapersDBLP.tar.gz}

wget "https://suitesparse-collection-website.herokuapp.com/MM/DIMACS10/${MTX}"
tar -xvzf "${MTX}" --strip 1
