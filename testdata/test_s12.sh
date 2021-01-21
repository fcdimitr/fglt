#!/bin/bash

FGLT=${1:-./fglt}

${FGLT} ../testdata/s12.mtx
diff freq_net.csv ../testdata/s12_freq_net_gold.csv
