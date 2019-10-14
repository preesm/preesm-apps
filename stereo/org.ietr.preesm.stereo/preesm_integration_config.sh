#!/bin/bash -eu

export PROJ_PATH=$(cd $(dirname $0) && pwd)
export PROJ_NAME="Stereo"

export SCENARIOS="1core.scenario 4core.scenario"
export WORKFLOWS="StaticPiMMCodegen.workflow StaticPiMMCodegenMemoryScripts.workflow CodegenMemoryScriptsMixedMerged.workflow"

export REF_SCENARIO=1core.scenario
export REF_WORKFLOW=StaticPiMMCodegen.workflow

function preesm_build_project () {
  mkdir -p Code/bin && cd Code/bin && rm -rf * && cmake -D CMAKE_C_FLAGS="-DPREESM_VERBOSE -DPREESM_LOOP_SIZE=5 " .. && make -j4
}

function preesm_exec_project () {
  cd Code/ && ./bin/Release/stereo
}
