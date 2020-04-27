#!/bin/bash -eu

function preesm_project_init_vars() {
  export PROJ_NAME="Stereo"

  export SCENARIOS="1core.scenario 4core.scenario"

  REALPATH=$(realpath ${1})
  export WORKFLOWS="NEWSynthesisAPI.workflow  $(find ${REALPATH}/Workflows/IntegrationWorkflows/ -name Codegen*.workflow | sed -e "s#${REALPATH}/Workflows/##g")"

  export REF_SCENARIO=1core.scenario
  export REF_WORKFLOW=IntegrationWorkflows/NoScriptsNoUpdate/BasicAlloc/Codegen_basic_memory_noalign.workflow
}

function preesm_project_fetch_data () {
  TTF_FILE=Code/dat/DejaVuSans.ttf
  LEFT_FILE=Code/dat/im0.ppm
  RIGHT_FILE=Code/dat/im1.ppm
  [ ! -f $TTF_FILE ] && wget -O $TTF_FILE https://preesm.github.io/assets/downloads/DejaVuSans.ttf
  [ ! -f $LEFT_FILE ] && wget -O Code/dat/im_434x380.7z https://preesm.github.io/assets/downloads/im_434x380.7z && (cd Code/dat/ && 7z x -aoa im_434x380.7z)
  [ ! -f $RIGHT_FILE ] && wget -O Code/dat/im_434x380.7z https://preesm.github.io/assets/downloads/im_434x380.7z && (cd Code/dat/ && 7z x -aoa im_434x380.7z)
  return 0
}

function preesm_project_build () {
  (mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=5 " .. && make -j4 VERBOSE=1)
  return $?
}

function preesm_project_exec () {
  (cd Code/ && ./bin/Release/stereo)
  return $?
}
