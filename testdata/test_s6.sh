#!/bin/bash

DIR_TESTDATA=$(cd "$(dirname "$0")" && pwd)

FGLT=${1:-./fglt}

${FGLT} "${DIR_TESTDATA}"/s6.mtx
diff freq_net.csv "${DIR_TESTDATA}"/s6_freq_net_gold.csv
