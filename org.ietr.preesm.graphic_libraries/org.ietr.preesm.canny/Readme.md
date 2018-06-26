# org.ietr.preesm.canny project
## Project description 

This preesm project is an implementation of the Canny edge detector. A kernel of Sobel filter and a kernel of Canny detection are used to carry out the calculations. To parallelize the application for a better performance, the input images are splitted, treated separately and then merged. Two methods of split and merge are used, one splits the input images horizontally into slices, the other splits the input images horizontally and vertically into blocks. The number of slices and columns can be specified as parameters in the top_display workflow.

The project contains:

* A PREESM workflow with application flattening, mapping and code generation
* An application named top_display (without hierarchy) with the first method of splitting described above and another application named top_display2 with the second method of splitting
* The architecture models of a PC with 1 core and a PC with 4 cores
* The associated code, headers with function prototypes and CMakeLists to execute the code

## Guide
To launch PREESM on this tutorial:

* Import the org.ietr.preesm.canny project into your Workspace
* Right-click on the workflow. Choose the unique scenario
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* Launch the execution
* Check tutorials on http://preesm.sf.net for a more detailed tutorials

Note that the yuv sequence and the ttf font are not provided in the /dat folder.