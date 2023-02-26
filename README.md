# RISC-V Simulator
A RISC-V simulator that runs in your browser.

A user will upload a compiled object file of their choice. That file will be parsed
to give an instruction set in assembly to C++ code using WebAssembly.

After the file is processed, the user has a few choices. They can run one instruction,
run ten instructions, or autoplay at a speed of their choice in milliseconds.

When running the file, there are views to see the current instruction being run, the register
values that are being changed, and the memory locations for the entire system.

Created for RIT's 2023 BrickHack 9 hackathon.
