#!/bin/bash -u

DIR=$(cd $(dirname $0) && pwd)

source ${DIR}/preesm_system.sh
source ${DIR}/preesm_build.sh

PREESM_BRANCH=develop
PREESM_CLI_BRANCH=master

echo " -- Project List:"
if [ ! -z ${1+x} ]; then
  GREPEXP="${1}"
  echo " < Filtering $GREPEXP >"
else
  GREPEXP=""
fi
set +e
PROJECTS=$(find ${DIR}/.. -name "*preesm_integration_config.sh" | grep "${GREPEXP}")
set -e
if [ -z "$PROJECTS" ]; then
  echo "No Projects. Exiting."
  exit 0
fi

for PROJECT in ${PROJECTS}; do
  echo " - $PROJECT"
done

set +e
preesm_check_system
preesm_fetch_build $PREESM_BRANCH $PREESM_CLI_BRANCH
set -e

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
        mkdir -p $(dirname ${LOG_FILE})
        ${DIR}/preesm-cli/commandLinePreesm.sh "${PREESM_PATH}" "${PROJ_PATH}" ${WORKFLOW} ${SCENARIO} &> ${LOG_FILE}
        PREESM_RES=$?
        if [ $PREESM_RES != 0 ]; then
          echo "        >> Error. See ${LOG_FILE}"
          ERROR=1
        else 
          echo "      o Build"
          LOG_FILE=${DIR}/${PROJ_NAME}/build_${WORKFLOW}_${SCENARIO}.log
          mkdir -p $(dirname ${LOG_FILE})
          (cd ${PROJ_PATH}/ && preesm_project_build &> ${LOG_FILE})
          BUILD_RES=$?
          if [ $BUILD_RES != 0 ]; then
            echo "        >> Error. See ${LOG_FILE}"
            ERROR=1
          else 
            echo "      o Exec"
            LOG_FILE=${DIR}/${PROJ_NAME}/exec_${WORKFLOW}_${SCENARIO}.log
            mkdir -p $(dirname ${LOG_FILE})
            (cd ${PROJ_PATH}/ && preesm_project_exec &> ${LOG_FILE})
            EXEC_RES=$?
            if [ $EXEC_RES != 0 ]; then
              echo "        >> Error. See ${LOG_FILE}"
              ERROR=1
            else
              MD5_FILE=${DIR}/${PROJ_NAME}/${WORKFLOW}_${SCENARIO}.md5
              mkdir -p $(dirname ${MD5_FILE})
              cat ${DIR}/${PROJ_NAME}/exec_${WORKFLOW}_${SCENARIO}.log | grep "^preesm_md5" | cut -d':' -f2 | sort > ${MD5_FILE}
              if [ "${SCENARIO}" == "${REF_SCENARIO}" ] && [ "${WORKFLOW}" == "${REF_WORKFLOW}" ]; then
                mv ${MD5_FILE} ${DIR}/${PROJ_NAME}/md5_reference
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
  for MD5_FILE in $(find ${DIR}/${PROJ_NAME}/ -name "*.md5" | grep -v md5_reference); do
    diff ${DIR}/${PROJ_NAME}/md5_reference $MD5_FILE &> /dev/null
    RES_DIFF=$?
    if [ "${RES_DIFF}" == "1" ]; then
      echo "   >> Error in ${MD5_FILE}"
      ERROR=1
    else
      echo "   * ${MD5_FILE} OK"
    fi
  done
  set -e
  return $ERROR
}


preesm_start_xvfb

PROJ_ERROR=0
for PROJECT in ${PROJECTS}; do
  ## Load project specifics
  export PROJ_PATH=$(dirname ${PROJECT})/
  source $PROJECT
  preesm_project_init_vars $PROJ_PATH

  echo " -- Testing $PROJ_NAME from folder $PROJ_PATH"
  PROJ_LOG_FILE=${DIR}/${PROJ_NAME}.log
  set +e
  test_project | tee ${PROJ_LOG_FILE}
  PROJ_RES=${PIPESTATUS[0]}
  set -e
  if [ $PROJ_RES != 0 ]; then
    echo " >> Error in $PROJ_NAME. See ${PROJ_LOG_FILE}"
    PROJ_ERROR=1
  fi

  # make sure variables are unset
  unset PROJ_PATH PROJ_NAME SCENARIOS WORKFLOWS REF_SCENARIO REF_WORKFLOW
done

preesm_kill_xvfb

if [ $PROJ_ERROR != 0 ]; then
  echo -e "\n\nERROR: Some error were thrown during tests. See logs.\n\n"
  exit 1
else
  echo -e "\n\nAll good, all rulez\n\n"
fi


exit 0
