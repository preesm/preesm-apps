#!/bin/bash -eu

function preesm_project_init_vars() {
  # take default values from default sobel (especially fetch/build/exec functions)
  source sobel_preesm_integration_config.sh

  export PROJ_NAME="Sobel Instrumented"

  export SCENARIOS="1core_sobel.scenario 4core_sobel.scenario 4core_sobel_memory.scenario"
  export WORKFLOWS="CodegenMemoryInstrumentation.workflow"

  export REF_SCENARIO=1core_sobel.scenario
  export REF_WORKFLOW=CodegenMemoryInstrumentation.workflow
}
