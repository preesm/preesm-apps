# MAD-based RFI mitigator deployed on multiple target architectures

### PROJECT :satellite:
The aim of this project is to provide a method that allow the deployement of an application on several CPU-based multicore architecture. 

The methode consist in describing an application with th Synchronous Dataflow (SDF) model, adapt it's granularity with the Scaling up of Cluster of Actor on the Processing Element (SCAPE) method [[1]](https://hal.science/hal-04089941v1/file/DASIP__Architecture_aware_Clustering_of_Dataflow_Actors_for_Controlled_Scheduling_Complexity.pdf) [[2]](https://hal.science/hal-04253298/document) [3].

The method is implemented in the [PREESM ](https://preesm.github.io/) rapid prototyping tool. The tool integrates dedicated resources allocation techniques for each target and aims to generalize it in once.
The implementation of CPU-based resource allocation is the most advanced implementation in our tool, and the one we'd like to move towards for others target architectures.


The use case to demonstrate the relevance of the method is a MAD-based RFI mitigator.

### USE CASE PRINCIPLE :loud_sound: --> :sound:
The process involves filtering Radio Frequency Interference (RFI) from an acquisition file obtained by a radio telescope. The file is in the ".dada" format (DADA stand for **Distributed Acquisition and Data Analysis**) and is comprised of two parts: the header, which contains information about the radio telescope, and the data part.

The data part consists of complex numbers. The first step of the process is to separate the real and imaginary components of the data in order to apply filters to both.

Two filters are computed simultaneously, and one of them is applied to the data. 
- The first filter is the Standard Deviation (STD) filter. See [Wiki STD deviation](https://en.wikipedia.org/wiki/Standard_deviation)

$$ {\displaystyle MAD = median (|X_{i}-{\tilde {X}}|)} $$

- The second filter is the Median Average Deviation (MAD) filter. See [Wiki MAD deviation](https://en.wikipedia.org/wiki/Median_absolute_deviation).

$$ \sigma =\sqrt{\frac{1}{N}\sum\limits_{i=1}^N (x_i - \mu)}$$

Both filters aim to find a threshold and remove data points above this threshold.

Finally, the filtered real and imaginary parts are combined by taking their conjugates to reconstruct the complex numbers. These reconstructed complex numbers are then used to generate a new ".dada" file.

### ON TARGET EXECUTION :desktop_computer:
The CPU plateform used for example is my personnal computer 8 core x86 CPUs.

> - Make sure you have install [GNU](https://psrchive.sourceforge.net/third/autotools/) before.
> - And of course:
>
> $ sudo make install
> - install GNUplot:
>
> $ sudo apt-get update
>
> $ sudo apt-get install gnuplot

> - Compile the code on the Code/ folder:

> $ cmake .
>
> $ make
>
> $ cd cmake-build-debug
>
> $ ./rfi
 
RFI_filter.png should illustrate the visual results expected from running the RFI filter

 ### References
[[1] O. Renaud, D. Gageot, K. Desnos, J.-F. Nezan, SCAPE: HW-Aware Clustering of Dataflow Actors for Tunable Scheduling Complexity, IETR, 2023](https://hal.science/hal-04089941v1/file/DASIP__Architecture_aware_Clustering_of_Dataflow_Actors_for_Controlled_Scheduling_Complexity.pdf). 

[[2] O. Renaud, N. Haggui, K. Desnos, J.-F, Nezan. Automated Clustering and Pipelining of Dataflow Actors for Controlled Scheduling Complexity, IETR, 2023.](https://hal.science/hal-04253298/document)

[3] O. Renaud, H. Miomandre, K. Desnos, J.-F. Nezan ,Automated Level-Based Clustering of Dataflow Actors for Controlled Scheduling Complexity, IETR, 202_.
