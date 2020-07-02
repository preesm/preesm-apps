# org.ietr.preesm.squeezenet project
## Project description 

This preesm project is an implementation of the SqueezeNet neural networks [https://arxiv.org/abs/1602.07360]. 
It uses pre-trained weights and biases.

The project mainly contains:

* A PREESM workflow with application flattening, mapping and code generation
* A dataflow version of the application and a sequential C version of the application.

## Guide for the Dataflow version

* Import the org.ietr.preesm.squeezenet project into your Workspace
* Right-click on the workflow. Choose the unique scenario
* Wait for the end of the mapping
* Use CMakeLists to generate your C project
* The squeezenet-c and squeezenet-c-sequential executables are generated in the bin/Release folder
* Launch the execution

## Guide for the Sequential version

* Go into the Code directory.
* Create a bin directory and move into it.
* Run the command ``` cmake .. ```
* Run the command ``` make squeezenet-c-sequential ```
* Run the executable with ``` ./Release/squeezenet-c-sequential [image] ```

## Notes
* The weights and biases are provided with sample images.
