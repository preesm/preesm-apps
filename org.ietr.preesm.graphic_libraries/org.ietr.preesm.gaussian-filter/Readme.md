# org.ietr.preesm.gaussian-filter project
## Project description 

This preesm project is an implementation of the Gaussian filter. It aims to parallelize the calculations in multi-core architectures to augment the performance of the Gaussian algorithm. In order to do so, the input images or video sequences need to be splitted into smaller units, treated separately and in parallel, then merged together. Two methods of splitting are proposed, one splits the input horizontally into slices and the other splits the input horizontally and vertically into blocks. A sequential version of this program is also provided as a comparison.

This project mainly contains:

* A PREESM workflow with application flattening, mapping and code generation
* An application named top_display using the first method of splitting and an application named top_display2 using the other method
* The architecture models of a PC with 1 core and a PC with 4 cores
* The associated code, headers with function prototypes and CMakeLists to execute the code

## Guide

* Import the org.ietr.preesm.gaussian-filter project into your Workspace
* Right-click on the workflow. Choose one of the scenarios
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* The parallel and sequential implementations are generated in the bin/Release folder
* Launch the execution