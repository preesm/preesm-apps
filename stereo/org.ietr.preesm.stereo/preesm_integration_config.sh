#!/bin/bash -eu

function preesm_project_init_vars() {
  export PROJ_NAME="Stereo"

  export SCENARIOS="1core.scenario 4core.scenario"
  export WORKFLOWS="StaticPiMMCodegen.workflow StaticPiMMCodegenMemoryScripts.workflow CodegenMemoryScriptsMixedMerged.workflow"

  export REF_SCENARIO=1core.scenario
  export REF_WORKFLOW=StaticPiMMCodegen.workflow
}

function preesm_project_fetch_data () {
  TTF_FILE=Code/dat/DejaVuSans.ttf
  LEFT_FILE=Code/dat/im0.ppm
  RIGHT_FILE=Code/dat/im1.ppm
  [ ! -f $TTF_FILE ] && wget -O $TTF_FILE https://preesm.github.io/assets/downloads/DejaVuSans.ttf
  [ ! -f $LEFT_FILE ] && wget -O Code/dat/im.7z https://preesm.github.io/assets/downloads/im.7z && (cd Code/dat/ && 7z x -aoa im.7z)
  [ ! -f $RIGHT_FILE ] && wget -O Code/dat/im.7z https://preesm.github.io/assets/downloads/im.7z && (cd Code/dat/ && 7z x -aoa im.7z)
  return 0
}

function preesm_project_build () {
  (mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=5 " .. && make -j4)
  return $?
}

function preesm_project_exec () {
  (cd Code/ && xvfb-run -a --server-args="-screen 0 1280x1024x16" ./bin/Release/stereo)
  return $?
}
