#!/bin/bash -eu

DIR=$(cd $(dirname $0) && pwd)

(cd ${DIR}/.. && git clean -xdf)
while true; do
  (cd ${DIR}/.. && git clean -xdf)
  ${DIR}/preesm_test_all.sh
done

