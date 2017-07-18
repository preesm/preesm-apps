# org.ietr.preesm.spider.sobel project
## Project description 

This tutorial project contains:

* A PREESM workflow with application Spider code generation
* A simple reconfigurable application named top_display (without hierarchy)
* Architecture models of a PC with 1 and 4 cores 
* The associated code, headers with function prototypes and CMakeLists to execute the code

## Guide
To launch PREESM on this tutorial:

* Import the org.ietr.preesm.spider.sobel project into your Workspace
* Right-click on the workflow. Choose a scenario
* Wait for the end of the generation
* Make sure all libraries are available: Pthread (>2.10.0), SDL 2.0, Spider
* Use CMakeLists to generate your C project
* Launch the execution
* Check tutorials on http://preesm.sf.net for a more detailed tutorials