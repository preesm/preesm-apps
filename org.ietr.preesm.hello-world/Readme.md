# org.ietr.preesm.hello-world project
## Project description 

This project contains two applications that may be used to debug/verify that workers are correctly distributed between computation cores. 
Tokens are sent to an "HelloWorld" actor that print out the value received. Once every token have been printed in console, a final actor is executed to verify tokens order.
Two graphs is available to describe the application:
- A flat one, suited for shared memory architecture.
- A hierarchical one, suited for distributed memory architecture with the help of OpenMP for fine-grained parallelism.

## Guide

To launch PREESM on this tutorial:

* Import the org.ietr.preesm.hello-world project into your Workspace
* Right-click on the workflow of your choice.
  * CodegenFlat.workflow is suited for shared memory architecture, please select a scenario that takes in input the flat graph.
  * CodegenHierarchical.workflow is suited for distributed memory architecture (example: Kalray MPPA 2), please select a scenario that takes in input the hierarchical graph.
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* Launch the execution