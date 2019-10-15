#!/bin/bash -eu


PREESM_BRANCH=fixAutoMd5
PREESM_CLI_BRANCH=master

DIR=$(cd $(dirname $0) && pwd)

${DIR}/check_system.sh
${DIR}/build_preesm.sh $PREESM_BRANCH $PREESM_CLI_BRANCH

PREESM_PATH=${DIR}/preesm/releng/org.preesm.product/target/products/org.preesm.product/linux/gtk/x86_64/

### TODO
###########################
# ajouter la gestion multi app par projet .. (sobel avec pipeline / display / .... RL train/pred ...)

function test_project() {
  set +e
  rm -rf ${DIR}/${PROJ_NAME}/
  mkdir -p ${DIR}/${PROJ_NAME}/
  ERROR=0
  
  echo "   * Fetch data"
  LOG_FILE=${DIR}/${PROJ_NAME}/fetch_data.log
  (cd ${PROJ_PATH}/ && preesm_project_fetch_data ) &> ${LOG_FILE}
  FETCH_RES=$?
  if [ $FETCH_RES != 0 ]; then
    echo "        >> Error while fetching data. See ${LOG_FILE}"
    ERROR=1
  else 
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
          (cd ${PROJ_PATH}/ && preesm_project_build &> ${LOG_FILE})
          BUILD_RES=$?
          if [ $BUILD_RES != 0 ]; then
            echo "        >> Error. See ${LOG_FILE}"
            ERROR=1
          else 
            echo "      o Exec"
            LOG_FILE=${DIR}/${PROJ_NAME}/exec_${WORKFLOW}_${SCENARIO}.log
            (cd ${PROJ_PATH}/ && preesm_project_exec &> ${LOG_FILE})
            EXEC_RES=$?
            if [ $EXEC_RES != 0 ]; then
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
  fi
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


PROJECTS=$(find ${DIR}/.. -name "*preesm_integration_config.sh")

PROJ_ERROR=0
for PROJECT in ${PROJECTS}; do

  ## Load project specifics
  export PROJ_PATH=$(dirname ${PROJECT})/
  (cd ${PROJ_PATH}/ && source $PROJECT)
  preesm_project_init_vars

  echo " -- Testing $PROJ_NAME from folder $PROJ_PATH"
  
  PROJ_LOG_FILE=${DIR}/${PROJ_NAME}.log
  set +e
  test_project | tee ${PROJ_LOG_FILE}
  PROJ_RES=${PIPESTATUS[0]}
  set -e
  if [ $PROJ_RES != 0 ]; then
    echo "  >> Error in $PROJ_NAME. See ${PROJ_LOG_FILE}"
    PROJ_ERROR=1
  else
    echo "  >> OK"
  fi
  
  unset PROJ_PATH PROJ_NAME SCENARIOS WORKFLOWS REF_SCENARIO REF_WORKFLOW
done

if [ $PROJ_ERROR != 0 ]; then
  echo -e "\n\nERROR: Some error were thrown during tests. See logs.\n\n"
fi

exit $PROJ_ERROR
