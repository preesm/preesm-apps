# org.ietr.preesm.canny project
## Project description 

This preesm project is an implementation of the Canny edge detector. It uses the Sobel and Canny algorithms to detect possible edge pixels in an input image or video within a certain margin. The developer can change the upper and lower thresholds to allow more or less points in the output. A pixel is marked with white if it is detected as an edge point, otherwise, it is marked with black. To parallelize the calculations for a better performance, the principle of splitting and conquering is applied. The input images are splitted, treated separately and in parallel, then merged together. Two methods of splitting and merging are used, one splits the input images horizontally into slices, the other splits the input images horizontally and vertically into blocks. The number of slices and columns are specified as parameters in the top_display workflow. A sequential version of this application is also provided as a comparison.

The project mainly contains:

* A PREESM workflow with application flattening, mapping and code generation
* A first application named top_display with the first method of splitting and a second application named top_display2 with the other method of splitting
* The architecture models of a PC with 1 core and a PC with 4 cores
* The associated code, headers with function prototypes and CMakeLists to execute the code

## Guide

* Import the org.ietr.preesm.canny project into your Workspace
* Right-click on the workflow. Choose the unique scenario
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* The canny and canny-sequential executables are generated in the bin/Release folder
* Launch the execution

## Notes
* The yuv sequence and the ttf font are not provided
* If the nbSlice (or nbColumn) is set to 1, the sliceHeight (columnWidth) parameter should be set to height/nbSlice (width/nbColumn); otherwise, a two-pixel width border should be added, sliceHeight should be (height/nbSlice+4) and columnWidth is(width/nbColumn+4)