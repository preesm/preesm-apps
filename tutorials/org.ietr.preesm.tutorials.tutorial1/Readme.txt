This tutorial project contains:

- A PREESM workflow with application flattening, mapping and code generation, in folder Workflows (Codegen.workflow)
- A simple application named TestCom (without hierarchy), in folder Algo (graphical version: TestCom.diagram, xml one: TestCom.pi)
- The architecture model of a PC with 2 cores interconnected by a shared memory, in folder Archi (2CoreX86.slam)
- The associated code, headers with function prototypes and CMakeLists to execute the code, in folder Code

To launch PREESM on this tutorial:

- Import the org.ietr.preesm.tutorials.tutorial1 project into your Workspace
- Right-click on the workflow. Choose the unique scenario
- Wait for the end of the mapping or stop it from the "Best Latency" editor
- Use CMakeLists to generate your C project
- Launch the execution