#include "gates.h"
#include <iostream>
#include <cmath>


void NAND(Wire A, Wire B, Wire Out) {
    // A circular reference is created if the shared_ptr to A is also
    // stored in the lambda that is given to A.on_change. To avoid this,
    // only store raw pointers A and B inside lambda functions.
    WireObject* pA = A.get();
    WireObject* pB = B.get();


    // Implement me:
    // 1. Create a lambda function that sets the value of Out = !(A && B)
    // 2. Add this action to wires A and B
}


// Note: now that you have defined NAND and the NAND function adds
// actions to wires, you can write all subsequent gates and
// combinations of NANDs.
void NOT(Wire In, Wire Out) {
    NAND(In, In, Out);
}

// Implement me:
// Write the code for the rest of the gates below
