#!/bin/bash

FGLT=${1:-./fglt}

${FGLT} ../testdata/s6.mtx
diff freq_net.csv ../testdata/s6_freq_net_gold.csv
