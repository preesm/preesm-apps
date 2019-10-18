#!/bin/bash -eu

function preesm_project_init_vars() {
  PROJ_PATH=$1

  # take default values from default sobel (especially fetch/build/exec functions)
  source ${PROJ_PATH}/sobel_preesm_integration_config.sh

  export PROJ_NAME="SobelPipelined"

  export SCENARIOS="4core_sobel_pipelined.scenario"

  export REF_SCENARIO=4core_sobel_pipelined.scenario
}
