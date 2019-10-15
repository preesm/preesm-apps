#!/bin/bash -eu

export PROJ_NAME="Sobel"

export SCENARIOS="1core_sobel.scenario 4core_sobel.scenario 4core_sobel_memory.scenario"
export WORKFLOWS="Codegen.workflow CodegenMemory.workflow"

export REF_SCENARIO=1core_sobel.scenario
export REF_WORKFLOW=Codegen.workflow

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
  (cd Code/ && xvfb-run -a --server-args="-screen 0 1280x1024x16" ./bin/Release/sobel)
  return $?
}
