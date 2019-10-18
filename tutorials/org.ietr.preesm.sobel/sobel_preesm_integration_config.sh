#!/bin/bash -eu

function preesm_project_init_vars() {
  PROJ_PATH=$1

  export PROJ_NAME="Sobel"

  export SCENARIOS="1core_sobel.scenario 4core_sobel.scenario 4core_sobel_memory.scenario"

  REALPATH=$(realpath ${1})
  export WORKFLOWS=$(find ${REALPATH}/Workflows/IntegrationWorkflows/ -name Codegen*.workflow | sed -e "s#${REALPATH}/Workflows/##g")

  export REF_SCENARIO=1core_sobel.scenario
  export REF_WORKFLOW=IntegrationWorkflows/NoScriptsNoUpdate/BasicAlloc/Codegen_basic_memory_noalign.workflow
}

function preesm_project_fetch_data () {
  TTF_FILE=Code/dat/DejaVuSans.ttf
  YUV_FILE=Code/dat/akiyo_cif.yuv
  [ ! -f $TTF_FILE ] && wget -O Code/dat/DejaVuSans.ttf https://preesm.github.io/assets/downloads/DejaVuSans.ttf
  [ ! -f $YUV_FILE ] && wget -O Code/dat/akiyo_cif.7z https://preesm.github.io/assets/downloads/akiyo_cif.7z && (cd Code/dat/ && 7z x -aoa akiyo_cif.7z)
  return 0
}

function preesm_project_build () {
  (mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=500 " .. && make -j4)
  return $?
}

function preesm_project_exec () {
  (cd Code/ && ./bin/Release/sobel)
  return $?
}
