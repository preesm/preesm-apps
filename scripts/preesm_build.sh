#!/bin/bash -eu

DIR=$(cd $(dirname $0) && pwd)

function preesm_fetch_build() {
  PREESM_BRANCH=$1
  PREESM_CLI_BRANCH=$2

  PREESM_BUILD=1
  echo " -- Fetch repos"
  if [ ! -d ${DIR}/preesm-cli ]; then
    echo "   * Clone Preesm CLI"
    (cd ${DIR}/ && git clone https://github.com/preesm/preesm-cli.git -b ${PREESM_CLI_BRANCH} &> ${DIR}/preesm_cli_clone.log)
  else
    echo "   * Preesm CLI present - update"
    (cd ${DIR}/preesm-cli && git clean -xdf && git reset --hard &&  git fetch --all -p && git checkout ${PREESM_CLI_BRANCH} && git pull --rebase) &> ${DIR}/preesm_cli_update.log
  fi
  if [ ! -d ${DIR}/preesm ]; then
    echo "   * Clone Preesm"
    (cd ${DIR}/ && git clone https://github.com/preesm/preesm.git -b ${PREESM_BRANCH} &> ${DIR}/preesm_clone.log)
  else
    echo "   * Preesm present"
    CURRENT_PREESM_BRANCH=$(cd ${DIR}/preesm && git branch --no-color | colrm 1 2)
    if [ "${CURRENT_PREESM_BRANCH}" != "${PREESM_BRANCH}" ]; then
      echo "    - clean, switch branch, pull"
      (cd ${DIR}/preesm && git clean -xdf && git reset --hard && git fetch --all -p && git checkout ${PREESM_BRANCH} && git pull --rebase)  &> ${DIR}/preesm_update.log
    else 
      (cd ${DIR}/preesm && git fetch --all -p) &> ${DIR}/preesm_update.log
      NB_DIFF=$(cd ${DIR}/preesm && git diff --stat ${PREESM_BRANCH}..origin/${PREESM_BRANCH} | wc -l)
      if [ $NB_DIFF == 0 ]; then
        echo "    - already up to date"
        PREESM_BUILD=0
      else
        echo "    - clean, pull"
        (cd ${DIR}/preesm && git clean -xdf && git reset --hard && git checkout ${PREESM_BRANCH} && git pull --rebase)  &>> ${DIR}/preesm_update.log
      fi
    fi
  fi

  export PREESM_PATH=${DIR}/preesm/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/
  
  echo " -- Build Preesm"
  if [ ! -x ${PREESM_PATH}/eclipse ]; then
    PREESM_BUILD=1
  fi

  if [ $PREESM_BUILD != 0 ]; then
    set +e
    LOG_FILE=${DIR}/preesm_build.log
    ${DIR}/preesm/releng/build_and_test.sh --notest &> ${LOG_FILE}
    PREESM_BUILD_RES=$?
    if [ $PREESM_BUILD_RES != 0 ]; then
      echo -e "Error: could not build Preesm.\nSee ${LOG_FILE}"
      exit 1
    fi
    set -e
  else
    echo "   * Skip: no git update and product present"
  fi

}
