#!/bin/bash -eu

DIR=$(cd $(dirname $0) && pwd)

PREESM_CLI_BRANCH=master
PREESM_BRANCH=develop

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
time (./preesm/releng/build_and_test.sh --notest &> ${DIR}/preesm_build.log)


# INIT VARIABLES
PREESM_PATH=${DIR}/preesm/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/
PROJ="stereo/org.ietr.preesm.stereo"
PROJ_PATH=${DIR}/../${PROJ}/

SCENARIOS="1core.scenario 4core.scenario"
WORKFLOWS="StaticPiMMCodegen.workflow StaticPiMMCodegenMemoryScripts.workflow CodegenMemoryScriptsMixedMerged.workflow"

REF_SCENARIO=1core.scenario
REF_WORKFLOW=StaticPiMMCodegen.workflow

echo " -- Exec Preesm on Stereo & Run"
for SCENARIO in ${SCENARIOS}; do
  for WORKFLOW in ${WORKFLOWS}; do
    echo "   * ${WORKFLOW} ${SCENARIO}"
    echo "      o Generate"
    ${DIR}/preesm-cli/commandLinePreesm.sh "${PREESM_PATH}" "${PROJ_PATH}" ${WORKFLOW} ${SCENARIO} &> ${DIR}/preesm_${WORKFLOW}_${SCENARIO}.log
    echo "      o Build"
    (cd ${PROJ_PATH}/Code/ && ./build.sh &> ${DIR}/build_${WORKFLOW}_${SCENARIO}.log)
    echo "      o Exec"
    (cd ${PROJ_PATH}/Code/ && ./exec.sh &> ${DIR}/exec_${WORKFLOW}_${SCENARIO}.log)
    cat ${DIR}/exec_${WORKFLOW}_${SCENARIO}.log | grep "^preesm_md5" | sort > ${DIR}/md5_${WORKFLOW}_${SCENARIO}
    if [ "${SCENARIO}" == "${REF_SCENARIO}" ] && [ "${WORKFLOW}" == "${REF_WORKFLOW}" ]; then
      mv ${DIR}/md5_${WORKFLOW}_${SCENARIO} ${DIR}/md5_reference
    fi
  done
done

echo " -- Compare MD5 files"
for MD5_FILE in $(ls ${DIR}/md5_*); do
  diff ${DIR}/md5_reference $MD5_FILE
  RES_DIFF=$?
  if [ "${RES_DIFF}" == "1" ]; then
    echo "Error in ${MD5_FILE}"
  fi
done
