#!/bin/bash -eu

function preesm_project_init_vars() {
  export PROJ_NAME="Stabilization"

  export SCENARIOS="1coreX86.scenario 4coresX86.scenario 12coresX86.scenario"
  REALPATH=$(realpath ${1})

  export WORKFLOWS=$(find ${REALPATH}/Workflows/IntegrationWorkflows/ -name Codegen*.workflow | sed -e "s#${REALPATH}/Workflows/##g")

  export REF_SCENARIO=1coreX86.scenario
  export REF_WORKFLOW=IntegrationWorkflows/NoScriptsNoUpdate/BasicAlloc/Codegen_basic_memory_noalign.workflow
}

function preesm_project_fetch_data () {
  TTF_FILE=Code/dat/DejaVuSans.ttf
  YUV_FILE=Code/dat/JaguarAndCroco360x202-375f.yuv
  [ ! -f $TTF_FILE ] && wget -O Code/dat/DejaVuSans.ttf https://preesm.github.io/assets/downloads/DejaVuSans.ttf
  [ ! -f $YUV_FILE ] && wget -O Code/dat/JaguarAndCroco720x404-375f.mp4 http://i.imgur.com/WMqwno7.mp4 && (cd Code/dat && ffmpeg -i JaguarAndCroco720x404-375f.mp4 -vf scale=360:202 -c:v rawvideo -pix_fmt yuv420p JaguarAndCroco360x202-375f.yuv)
  return 0
}

function preesm_project_build () {
  (mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=375 " .. && make -j4 VERBOSE=1)
  return $?
}

function preesm_project_exec () {
  (cd Code/ && ./bin/Release/stabilization)
  return $?
}
