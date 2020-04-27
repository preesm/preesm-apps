# SIFT implementation in PREESM

Scale-Invariant Feature Transform (SIFT) is an image processing application that detects keypoints, see the
original publication of Lowe for more details :
https://www.cs.ubc.ca/~lowe/papers/iccv99.pdf




## ezSIFT

The code used in this repo has been modified from the
following original code: https://github.com/robertwgh/ezSIFT

The new implementation mades it available as a Synchronous DataFlow graph,
under the PREESM environment (editor, scheduler and code generator).


## folder architecture

The root folder follows the PREESM template, with two additional subfolders:
- Ref/ : contains a sequential and OpenMP version closer to ezSIFT
- misc/ : contains a few files, useful when modifying the PREESM application parameters (as number of keypoints and parallelism level)


