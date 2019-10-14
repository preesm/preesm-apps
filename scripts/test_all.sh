#!/bin/bash -eu

DIR=$(cd $(dirname $0) && pwd)

${DIR}/check_system.sh
${DIR}/build_preesm.sh

PREESM_PATH=${DIR}/preesm/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/

### TODO
###########################
# ajouter la gestion multi projet (multi preesm apps)
# ajouter le fetch des données ...

function test_project() {
  set +e
  echo " -- Exec Preesm on Stereo & Run"
  rm -rf ${DIR}/${PROJ_NAME}/
  mkdir -p ${DIR}/${PROJ_NAME}/
  ERROR=0
  for SCENARIO in ${SCENARIOS}; do
    for WORKFLOW in ${WORKFLOWS}; do
      echo "   * ${WORKFLOW} ${SCENARIO}"
      echo "      o Generate"
      LOG_FILE=${DIR}/${PROJ_NAME}/preesm_${WORKFLOW}_${SCENARIO}.log
      ${DIR}/preesm-cli/commandLinePreesm.sh "${PREESM_PATH}" "${PROJ_PATH}" ${WORKFLOW} ${SCENARIO} &> ${LOG_FILE}
      PREESM_RES=$?
      if [ $PREESM_RES != 0 ]; then
        echo "        >> Error. See ${LOG_FILE}"
        ERROR=1
      else 
        echo "      o Build"
        LOG_FILE=${DIR}/${PROJ_NAME}/build_${WORKFLOW}_${SCENARIO}.log
        (cd ${PROJ_PATH}/ && preesm_build_project &> ${LOG_FILE})
        BUILD_RES=$?
        if [ $BUILD_RES != 0 ]; then
          echo "        >> Error. See ${LOG_FILE}"
          ERROR=1
        else 
          echo "      o Exec"
          LOG_FILE=${DIR}/${PROJ_NAME}/exec_${WORKFLOW}_${SCENARIO}.log
          (cd ${PROJ_PATH}/ && preesm_exec_project &> ${LOG_FILE})
          EXEC_RES=$?
          if [ $BUILD_RES != 0 ]; then
            echo "        >> Error. See ${LOG_FILE}"
            ERROR=1
          else
            cat ${DIR}/${PROJ_NAME}/exec_${WORKFLOW}_${SCENARIO}.log | grep "^preesm_md5" | sort > ${DIR}/${PROJ_NAME}/md5_${WORKFLOW}_${SCENARIO}
            if [ "${SCENARIO}" == "${REF_SCENARIO}" ] && [ "${WORKFLOW}" == "${REF_WORKFLOW}" ]; then
              mv ${DIR}/${PROJ_NAME}/md5_${WORKFLOW}_${SCENARIO} ${DIR}/${PROJ_NAME}/md5_reference
            fi
          fi
        fi
      fi
    done
  done
  set -e

  echo " -- Compare MD5 files"
  set +e
  for MD5_FILE in $(ls ${DIR}/${PROJ_NAME}/md5_*); do
    diff ${DIR}/${PROJ_NAME}/md5_reference $MD5_FILE &> /dev/null
    RES_DIFF=$?
    if [ "${RES_DIFF}" == "1" ]; then
      echo "   >> Error in ${MD5_FILE}"
      ERROR=1
    fi
  done
  set -e
  return $ERROR
}


PROJECTS=$(find ${DIR}/.. -name "preesm_integration_config.sh")

PROJ_ERROR=0
for PROJECT in ${PROJECTS}; do
  source $PROJECT
  export PROJ_PATH=$(dirname ${PROJECT})/
  echo " -- Testing $PROJ_NAME from folder $PROJ_PATH"
  
  PROJ_LOG_FILE=${PROJ_NAME}.log
  set +e
  test_project | tee ${PROJ_LOG_FILE}
  PROJ_RES=$?
  set -e
  if [ $PROJ_RES != 0 ]; then
    echo "    >> Error. See ${PROJ_LOG_FILE}"
    PROJ_ERROR=1
  else
    echo "    >> OK"
  fi
  
  unset PROJ_PATH PROJ_NAME SCENARIOS WORKFLOWS REF_SCENARIO REF_WORKFLOW
done

exit $PROJ_ERROR
