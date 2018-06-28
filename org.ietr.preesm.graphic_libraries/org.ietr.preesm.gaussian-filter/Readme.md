# org.ietr.preesm.harris project
## Project description 

This PREESM project is an implementation of the Harris corner detector. It uses the Sobel and Harris algorithms to detect the possible corners in an input image or video within a certain margin. The developer can change the upper and lower thresholds in order to allow more or less points in the output. A pixel is marked with white in the output if it is detected as a corner, otherwise, it is marked with black. To fully expoit the parallelism of these algorithms, the principle of splitting and conquering is applied. The input image or video sequence are splitted into smaller units, treated separately and in parallel, then merged together. Two methods of splitting and merging are provided. One splits the input horizontally into slices, the other splits the input horizontally and vertically into blocks. A sequential implemention of this algorithm is also provided as a comparison.

This project mainly contains:

* A PREESM workflow with application flattening, mapping and code generation
* A first application named top_display with the first method of splitting and merging and a second application named top_display2 using the second method of splitting and merging
* The architecture models of a PC with 1 core and a PC with 4 core
* The associated code, headers with function prototypes and CMakeLists to execute the code

## Guide

* Import the org.ietr.preesm.harris project into your Workspace
* Right-click on the workflow. Choose the unique scenario
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* The harris and harris-sequential executables are generated in the /bin/Release folder
* Launch the execution

Note that the yuv sequences and the ttf font are not provided.