#pragma once

#include "wire.h"

// gates are functions that add actions to wires
void NAND(Wire A, Wire B, Wire Out);
void NOT(Wire In, Wire Out);

// Implement me:
// 1. AND, OR, XOR, HalfAdder, FullAdder
// 2. Once you have a FullAdder, write a function:
//    void add_bits(int a, int b, int numbits)
//    that can add two numbers together using multiple FullAdders
// 3. Implement Decoder, Logic, FullAdderWithEnable
// 4. Combine the above gates to create ALU


void AND(Wire A, Wire B, Wire Out);
void OR(Wire A, Wire B, Wire Out);
void XOR(Wire A, Wire B, Wire Out);
void HalfAdder(Wire A, Wire B, Wire Sum, Wire Carry);
void FullAdder(Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout);

// using FullAdder, add numbers a and b together and return the result
int add_bits(int a, int b, int numbits);


// build the ALU in Figure 3-19
void Decoder(Wire F0, Wire F1, Wire D0, Wire D1, Wire D2, Wire D3);
void Logic(Wire A, Wire B, Wire D0, Wire D1, Wire D2, Wire AandB, Wire AorB, Wire NotB);
void FullAdderWithEnable(Wire Enable, Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout);
void ALU(Wire F0, Wire F1, Wire A, Wire B, Wire Cin, Wire Out, Wire Cout);
