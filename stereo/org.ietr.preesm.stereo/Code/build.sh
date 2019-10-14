#!/bin/bash

DIR=$(cd $(dirname $0) && pwd)

rm -rf ${DIR}/bin
mkdir -p ${DIR}/bin
(cd ${DIR}/bin && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=5 " .. && make VERBOSE=1)
