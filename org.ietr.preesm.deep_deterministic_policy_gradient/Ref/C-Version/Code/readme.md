C's reference code for CACLA algorithm
===

Build Instruction
--

1. ./CMakeGCC.sh
2. cd bin
3. make && ./Release/cacla


Options
--

This is a reference test program. 
You can toggle rendering by using *CTRL+C*.

In the *main.c* file, you have multiple options which are set by define.
- **CACLA_train**: This is the standard training algorithm, same behavior as the Python's reference.
- **CACLA_run**: This only runs the prediction model. After training, if the system converged, you get a network.txt file. 
                 Simply copy and paste the content in actor_mlp.c to replace the current initialization function. 
                 By default, the programm will stop once it converged. You can disable this features by removing *if (action_sampled > MAX_TORQUE)* condition.
- **MLP_cmp:** This compares sequential standard implementation and dataflow one.
- **LEARN_SIN:** This test the learning property of the network by making it learn trigonometric function.
- **BENCH:** This is used to compared result with python's version. The same function is available in the python's implementation and does the exact same thing.
             To use it you should first create a network in python and save it. (*python3 bench -generate-network*) A network.txt file is created in /tmp, copy the result in actor_mlp.c.
             Then you can run the C-Version classically. For the python's version: *python3 bench -mode-use -model-path models/models_[date and time of your model]*.
             NOTE: this a very low level debugging option. Make sure the dimension of the network defined in C and Python are the same.
