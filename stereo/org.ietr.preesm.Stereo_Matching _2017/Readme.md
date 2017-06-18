# Stereo Matching Project

## Project description 
This PREESM project aims to generate code for stereo matching. "top_display.diagram" allows the user 
to select the algorithms he wants to use in the generated process. Parameters for the chosen algorithms are also
easily selectable  in "top_display.diagram". 
It is possible to generate parallel processes. To do so the input images are splitted in slices along the vertical
axis. The number of slices is defined by the parameter "n_slice". The idea is to choose a number of slices close 
to the parallelism degree of the target (ex: 12 slices for an 6 cores processor with 12 threads). The number 
of slices does not need to be a multiple of the image height.  

## Required Libraries
	- libpng (http://www.libpng.org/pub/png/libpng.html)
	- zlib (https://zlib.net/)	
	
## Input and output Images

	- Images to proceed has to be stored in Code/Images
	- The input images are chosen in Code/include/load_images_preesm.h by PATH_L and PATH_R
	for left and right image, respectively.
	- The output disparity map is saved in Code/Images/output.ppm

## Algorithms, Architectures and Scenarios 
	- top_display.diagram is the global diagram
	- Cost_Construction.diagram, Cost_aggregation.diagram and Disparity_Selection.diagram are
	the IBSDF graph to refine actor of the same name in top_display
	
	- .slam files for 1, 2, 4, 8, 12, 48, 256 x86 cores are provided in Archi directory
	the scenarios for 1,4 and 12 cores are provided in Scenarios directory. 
	
## Modelling Parameters:

Image metrics:

	- height height of the input image
	- width height of the input image
	
Stereo Matching Process Parameters:

	- n_disp
	- n_slice
	
Algorithm selection:

	- select_construction: 
		0 --> Census
		1 --> Absolute Difference (With threshold) (AD)
		
	- select_aggregation: 
		0 --> No Aggregation
		1 --> Bilateral Filter (BFA) // Not working yet
	
	- select_selection: 
		0 --> Belief Propagation 1 Dimension (BP1D)
		1 --> Winner Takes it All (WTA)
		
Algorithm Parameters:

	- Census:
		census_size: Size of the census window (must be odd >= 3)
		
	- AD:
		threshold_SAD: Threshold applied to similarity 
	
	- BFA:
		threshold_BFA
		n_iter number of iterations of BFA refinement
		d_max distance max for refinement
		cst_cd
	
	- BP1D:
		phi0
	

		
    
    