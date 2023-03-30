# ALUSimulater

This is a neat way to show how Arithmetic Logic Units (ALUs) work down to a logic gate level.

The entire system is built around wires, NAND gates, and abstraction to perform tasks that all CPUs do at the hardware layer.  

## Building the Simulator
To use this, use CMake. The CMakeList file shows how the program is assembled. After that, the executable will be in the new build folder.
Navigate a terminal to the base directory.

```ps1
cd build
./test-gates
```
Then the simulator will begin according to the code in test-gates.cpp

## Testing the Simulator
It is up to whoever writes main() in test-gates.cpp to use the ALUSimulator. Here are some things you can do with it.

Comparing numbers bit by bit  
Adding Integers using ALUs stringed together in a loop.  
And, Or, and Not functions with A input (and B as needed)  
