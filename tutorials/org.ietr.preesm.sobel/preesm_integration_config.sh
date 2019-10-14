#!/bin/bash -eu

export PROJ_NAME="Sobel"

export SCENARIOS="1core_sobel.scenario 4core_sobel.scenario 4core_sobel_memory.scenario"
export WORKFLOWS="Codegen.workflow CodegenMemory.workflow CodegenMemoryInstrumentation.workflow"

export REF_SCENARIO=1core_sobel.scenario
export REF_WORKFLOW=Codegen.workflow

function preesm_build_project () {
  (mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=500 " .. && make -j4)
}

function preesm_exec_project () {
  (cd Code/ && xvfb-run -a --server-args="-ac -screen 0 1280x1024x16" ./bin/Release/sobel)
}
