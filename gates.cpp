#include "gates.h"
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <string>


void NAND(Wire A, Wire B, Wire Out) {
    // A circular reference is created if the shared_ptr to A is also
    // stored in the lambda that is given to A.on_change. To avoid this,
    // only store raw pointers A and B inside lambda functions.

    WireObject* pA = A.get();
    WireObject* pB = B.get();

    Action perform = [pA, pB, Out]() {Out->set(!(pA->get() && pB->get()));};

    // Implement me:
    // 2. Add this action to wires A and B
    A->on_change(perform);
    B->on_change(perform);
}


// Note: now that you have defined NAND and the NAND function adds
// actions to wires, you can write all subsequent gates and
// combinations of NANDs.
void NOT(Wire In, Wire Out) {
    NAND(In, In, Out);
}

void NOR(Wire A, Wire B, Wire Out){
    Wire ORed = make_wire("ORed");
    OR(A, B, ORed);
    NOT(ORed, Out);
}

void AND(Wire A, Wire B, Wire Out){
    Wire step1 = make_wire("step1");
    NAND(A, B, step1);
    NAND(step1, step1, Out);
}

void XOR(Wire A, Wire B, Wire Out){
    Wire step1 = make_wire("step1");
    Wire step2 = make_wire("step2");
    Wire step3 = make_wire("step3");
    NAND(A, B, step1);
    NAND(A, step1, step2);
    NAND(B, step1, step3);
    NAND(step2, step3, Out);
}
void OR(Wire A, Wire B, Wire Out){
    Wire step1 = make_wire("step1");
    Wire step2 = make_wire("step2");
    NAND(A, A, step1);
    NAND(B, B, step2);
    NAND(step1, step2, Out);
}

void Decoder(Wire F0, Wire F1, Wire D0, Wire D1, Wire D2, Wire D3){
    //D0 is AB
    //D1 is A+B
    //D2 is !B
    //D3 is adder
    Wire NF0 = make_wire("NF0");
    Wire NF1 = make_wire("NF1");
    NOT(F0, NF0);
    NOT(F1, NF1);
    AND(NF0, NF1, D0);
    AND(NF0, F1, D1);
    AND(F0, NF1, D2);
    AND(F0, F1, D3);

}

void Logic(Wire A, Wire B, Wire D0, Wire D1, Wire D2, Wire AandB, Wire AorB, Wire NotB){
    Wire AB = make_wire("AB");
    Wire AoB = make_wire("A+B");
    Wire NB = make_wire("NB");
    AND(A, B, AB);
    OR(A, B, AoB);
    NOT(B, NB);
    AND(AB, D0, AandB);
    AND(AoB, D1, AorB);
    AND(NB, D2, NotB);
}

void HalfAdder(Wire A, Wire B, Wire Sum, Wire Carry){
    XOR(A, B, Sum);
    AND(A, B, Carry);
}


void FullAdder(Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout){
    Wire FirstPreEnable = make_wire("FirstPreEnable");
    Wire SecondPreEnable = make_wire("SecondPreEnable");
    Wire HalfCarry1 = make_wire("HalfCarry1");
    Wire HalfCarry2 = make_wire("HalfCarry2");
    Wire AxB = make_wire("AxB");
    XOR(A, B, AxB);
    //Sum
    XOR(AxB, Cin, Sum);

    //carry out
    AND(A, B, HalfCarry1);
    AND(AxB, Cin, HalfCarry2);
    OR(HalfCarry1, HalfCarry2, Cout);
    
}

void FullAdderWithEnable(Wire Enable, Wire A, Wire B, Wire Cin, Wire Sum, Wire Cout){
    Wire FirstPreEnable = make_wire("FirstPreEnable");
    Wire SecondPreEnable = make_wire("SecondPreEnable");
    Wire HalfCarry1 = make_wire("HalfCarry1");
    Wire HalfCarry2 = make_wire("HalfCarry2");
    Wire AxB = make_wire("AxB");
    Wire AxBxC = make_wire("AxBxC");
    XOR(A, B, AxB);
    //Sum
    XOR(AxB, Cin, AxBxC);
    AND(AxBxC, Enable, Sum);
    

    //carry out
    AND(A, B, FirstPreEnable);
    AND(FirstPreEnable, Enable, HalfCarry1);

    AND(AxB, Cin, SecondPreEnable);
    AND(SecondPreEnable, Enable, HalfCarry2);

    OR(HalfCarry1, HalfCarry2, Cout);
    

}
void ALU(Wire F0, Wire F1, Wire A, Wire B, Wire Cin, Wire Out, Wire Cout){
    //decode outputs
    Wire D0 = make_wire("D0");
    Wire D1 = make_wire("D1");
    Wire D2 = make_wire("D2");
    Wire D3 = make_wire("D3");
    //logic outputs
    Wire AandB = make_wire("AandB");
    Wire AorB = make_wire("AorB");
    Wire NotB = make_wire("NotB");
    //Adder output
    Wire Sum = make_wire("Sum");

    //final output
    Wire ABLogic = make_wire("ABLogic");
    Wire NBorSum = make_wire("NBorSum");

    Decoder(F0, F1, D0, D1, D2, D3);
    Logic(A, B, D0, D1, D2, AandB, AorB, NotB);
    FullAdderWithEnable(D3, A, B, Cin, Sum, Cout);

    OR(AandB, AorB, ABLogic);
    OR(NotB, Sum, NBorSum);
    OR(ABLogic, NBorSum, Out);


}
int add_bits(int a, int b, int numbits){
    int compounding_sum{0};
    Wire Cin = make_wire("Cin");
    Wire A = make_wire("A");
    Wire B = make_wire("B");
    Wire Cout = make_wire("Cout");
    Wire Sum = make_wire("Sum");

    std::vector<bool> a_bits(numbits), b_bits(numbits), total_bits(numbits + 1);
    for(int i = 0; i < numbits; i++){
        bool bit_a = (a >> i) & 1; // extract the ith bit
        bool bit_b = (b >> i) & 1;
        a_bits.at(i) = bit_a;
        std::cout << "\n This is what A is right now " << bit_a << '\n';
        b_bits.at(i) = bit_b;
        A->set(bit_a);
        B->set(bit_b);
        Cin->set(Cout->get());
        FullAdder(A, B, Cin, Sum, Cout);
        total_bits.at(i) = Sum->get();
        if(total_bits.at(i)){
        compounding_sum += std::pow(2,i);
        std::cout << "\n Here is the sum so far \n" << compounding_sum;
        }
    }
    if(Cout->get()){
        compounding_sum += std::pow(2,numbits);
    }

    return compounding_sum;
}
