# Video Stabilization

## Principle
Since the introduction of embedded imaging sensors in cell phone and other mainstream handheld devices, the popularity of digital video shot in all circumstances has skyrocketed. In these devices where video recording is often a secondary feature, quality of generated video is often poor compared to digital camera. In particular, handheld device often lack ``optical'' image stabilizer that act as a low-pass motion filter by moving the lens or the sensor of a camera in a way that counteracts small and rapid movements of a shaking camera.

The principle of video stabilization filtering is to compensate the movements of a video recorded with a shaky camera ``offline'', as a post-recording processing applied to the recorded video. The main two steps of this process consist of:
* Tracking the movement of the image using image processing techniques,
* Creating a new video where the tracked motion is compensated.

## Algorithm description
The proposed solution is compatible with YUV video sequences with variable resolutions. The header file `./Code/include/applicationParameters.h` contains all the parameters configuring the algorithm. This file already includes parameter values for two video sequences that can be downloaded following guidelines in `./Code/dat/Readme.md`. 

The implemented algorithm follows the following steps for each processed frame *n* of the input video:
1. Split the input frame *n* into blocs of `BLOCK_HEIGHT` by `BLOCK_WIDTH` pixels. 
2. For each bloc, try to find its position in previous frame *n-1* using minimum squared error calculus. Research is restricted to a limited neighborhood of the bloc defined by `MAX_DELTA_X/Y`. For each bloc, a ``motion vector'' is thus obtained. 
3. Analyze the produced ``motion'' vectors in order to identify the dominating motion. The principle of this step is to compare the different motion vectors, using a multivariate Gaussian criteria, in order to find the largest possible group of resembling vectors. Once this group is found, the average vector of this group can be considered to be the dominating motion of the frame. 
4. Accumulate the dominating motion vector. This step includes an optional high-pass filter whose purpose is to avoid compensating slow motions of the camera like a slow camera pan to shoot a landscape. The filter is defined with a unique tap: `HIGH_PASS_FILTER_TAP`. 
5. Render the motion-compensated frame. Create an output image where all pixels are translated by the opposite of the accumulated motion vector. The rendered frame has two times `BORDER` pixels additional pixels than the original video, both horizontally and vertically. These extra pixels are added to allow the rendered motion compensated frame to move within a larger area before leaving the frame of the rendered video. 

## Run the project
To launch the project:
1. Import the project in Preesm
2. Launch a workflow on the desired scenario to generate parallel C code
3. Make sure all required libraries are downloaded in `./Code/lib` (using the readme.)
4. Make sure all required files are downloaded in `./Code/dat`
5. Create a project for your favorite IDE using the CMake project in `./Code`.
6. Compile and run the project.