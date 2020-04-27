# org.ietr.preesm.gaussian-pyramid project
## Project description 

This PREESM project is an implementation of the Gaussian pyramid using the dataflow principle. The input image is firstly processed by a Gaussian filter, then sampled to form a half-scale image. The half-scale image can be processed by another pyramid actor in series to form a level-three image. The principle of split and merge can be used to further augment the performance.

The project mainly contains:
* A Gaussian-pyramid actor
* First-level, second-level and third-level diagrams
* A workflow to generate the code
* The CMake files to generate the Makefile

## Guide
To launch PREESM:

* Import the org.ietr.preesm.gaussian-pyramid project into your Workspace
* Add the TTF file and the yuv sequence to be processed into the /dat folder
* Right-click on the workflow. Choose the corresponding scenario
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* Launch the execution

## Notes
* The TTF file and the yuv sequences are not provided
* The "scale" parameters in the workflow should correspond to the number of levels of the pyramid