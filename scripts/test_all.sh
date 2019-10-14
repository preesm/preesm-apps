#!/bin/bash -eu

./check_system.sh

./build_preesm.sh

### TODO
###########################
# ajouter la gestion multi projet (multi preesm apps)
# ajouter le fetch des données ...

DIR=$(cd $(dirname $0) && pwd)

# INIT VARIABLES
PREESM_PATH=${DIR}/preesm/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/
PROJ="stereo/org.ietr.preesm.stereo"
PROJ_PATH=${DIR}/../${PROJ}/

SCENARIOS="1core.scenario 4core.scenario"
WORKFLOWS="StaticPiMMCodegen.workflow StaticPiMMCodegenMemoryScripts.workflow CodegenMemoryScriptsMixedMerged.workflow"

REF_SCENARIO=1core.scenario
REF_WORKFLOW=StaticPiMMCodegen.workflow

ERROR=0

set +e
echo " -- Exec Preesm on Stereo & Run"
for SCENARIO in ${SCENARIOS}; do
  for WORKFLOW in ${WORKFLOWS}; do
    echo "   * ${WORKFLOW} ${SCENARIO}"
    echo "      o Generate"
    LOG_FILE=${DIR}/preesm_${WORKFLOW}_${SCENARIO}.log
    ${DIR}/preesm-cli/commandLinePreesm.sh "${PREESM_PATH}" "${PROJ_PATH}" ${WORKFLOW} ${SCENARIO} &> ${LOG_FILE}
    PREESM_RES=$?
    if [ $PREESM_RES != 0 ]; then
      echo "        >> Error. See ${LOG_FILE}"
      ERROR=1
    else 
      echo "      o Build"
      LOG_FILE=${DIR}/build_${WORKFLOW}_${SCENARIO}.log
      (cd ${PROJ_PATH}/Code/ && ./build.sh &> ${LOG_FILE})
      BUILD_RES=$?
      if [ $BUILD_RES != 0 ]; then
        echo "        >> Error. See ${LOG_FILE}"
        ERROR=1
      else 
        echo "      o Exec"
        LOG_FILE=${DIR}/exec_${WORKFLOW}_${SCENARIO}.log
        (cd ${PROJ_PATH}/Code/ && ./exec.sh &> ${LOG_FILE})
        EXEC_RES=$?
        if [ $BUILD_RES != 0 ]; then
          echo "        >> Error. See ${LOG_FILE}"
          ERROR=1
        else
          cat ${DIR}/exec_${WORKFLOW}_${SCENARIO}.log | grep "^preesm_md5" | sort > ${DIR}/md5_${WORKFLOW}_${SCENARIO}
          if [ "${SCENARIO}" == "${REF_SCENARIO}" ] && [ "${WORKFLOW}" == "${REF_WORKFLOW}" ]; then
            mv ${DIR}/md5_${WORKFLOW}_${SCENARIO} ${DIR}/md5_reference
          fi
        fi
      fi
    fi
  done
done
set -e

echo " -- Compare MD5 files"
set +e
for MD5_FILE in $(ls ${DIR}/md5_*); do
  diff ${DIR}/md5_reference $MD5_FILE
  RES_DIFF=$?
  if [ "${RES_DIFF}" == "1" ]; then
    echo "Error in ${MD5_FILE}"
    ERROR=1
  fi
done
set -e


exit


echo " -- Fetch repos"
if [ ! -d preesm-cli ]; then
  echo "   * Clone Preesm CLI"
  git clone https://github.com/preesm/preesm-cli.git -b ${PREESM_CLI_BRANCH} &> ${DIR}/preesm_cli_clone.log
else
  echo "   * Preesm CLI present - update"
  (cd preesm-cli && git clean -xdf && git reset --hard && git checkout ${PREESM_CLI_BRANCH} && git fetch --all -p && git pull) &> ${DIR}/preesm_cli_update.log
fi
if [ ! -d preesm ]; then
  echo "   * Clone Preesm CLI"
  git clone https://github.com/preesm/preesm.git -b ${PREESM_BRANCH} &> ${DIR}/preesm_clone.log
else
  echo "   * Preesm present - update"
  (cd preesm && git clean -xdf && git reset --hard && git checkout ${PREESM_BRANCH} && git fetch --all -p && git pull)  &> ${DIR}/preesm_update.log
fi

echo " -- Build Preesm"
set +e
LOG_FILE=${DIR}/preesm_build.log
./preesm/releng/build_and_test.sh --notest &> ${LOG_FILE}
PREESM_BUILD_RES=$?
if [ $PREESM_BUILD_RES != 0 ]; then
  echo -e "Error: could not build Preesm.\nSee ${LOG_FILE}"
  exit 1
fi
set -e
