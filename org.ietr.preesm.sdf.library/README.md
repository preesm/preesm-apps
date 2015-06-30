This project gathers frequently used PREESM files.

*WORKFLOWS*
CLI_Workflows are workflows using no GUI, and thus usable through eclipse command line interface.
The Workflows folder contains the most frequenty used workflows for PiSDF algorithm descriptions:
-Scheduling.workflow is a workflow which will transform a PiSDF algorithm in a set of static SDFs using the simulation parameters given in the scenario and then schedule each of the static SDFs;
-Codegen.workflow generates C code for each of the static SDFs;
-MemoryOptimization.wokflow generates the same code after memory optimization in order to reduce the memory footprint of each SDFs execution.
The easiest way to use these workflows is to copy/paste them in your projects and adapt them to your needs by adding/removing tasks.
