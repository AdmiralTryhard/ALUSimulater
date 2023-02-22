#include "gates.h"
#include <iostream>
#include <cmath>


void NAND(Wire A, Wire B, Wire Out) {
    // A circular reference is created if the shared_ptr to A is also
    // stored in the lambda that is given to A.on_change. To avoid this,
    // only store raw pointers A and B inside lambda functions.
    WireObject* pA = A.get();
    WireObject* pB = B.get();

    auto perform =[](WireObject* pA, WireObject* pB) {return !(pA && pB);};
    Out->set(perform);

    // Implement me:
    // 2. Add this action to wires A and B
}


// Note: now that you have defined NAND and the NAND function adds
// actions to wires, you can write all subsequent gates and
// combinations of NANDs.
void NOT(Wire In, Wire Out) {
    NAND(In, In, Out);
}

void AND(Wire A, Wire B, Wire Out){
    Wire step1;
    NAND(A, B, step1);
    NAND(step1, step1, Out);
}

void XOR(Wire A, Wire B, Wire Out){
    Wire step1, step2, step3;
    NAND(A, B, step1);
    NAND(A, step1, step2);
    NAND(B, step1, step3);
    NAND(step2, step3, Out);
}
void OR(Wire A, Wire B, Wire Out){
    Wire step1, step2;

    NAND(A, A, step1);
    NAND(B, B, step2);
    NAND(step1, step2, Out);
}

// Implement me:
// Write the code for the rest of the gates below
