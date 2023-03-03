#include "gates.h"
#include "truth.h"
#include <iostream>

void DLatch(Wire D, Wire CLK, Wire Out);

int main() {
    auto D = make_wire("D");
    auto CLK = make_wire("CLK");
    auto Out = make_wire("Out");
    DLatch(D, CLK, Out);
    probe(D);
    probe(CLK);
    probe(Out);

    std::cout << "_________________________ \n";
    D->set(true);
    CLK->set(true);
    CLK->set(false);

    std::cout << "_________________________ \n";
    D->set(false);
    CLK->set(true);
    CLK->set(false);

    std::cout << "_________________________ \n";
    D->set(true);
    CLK->set(true);
    CLK->set(false);
}

void DLatch(Wire D, Wire CLK, Wire Out){
    auto A = make_wire("A");
    auto B = make_wire("B");
    auto C = make_wire("C");
    auto NotD = make_wire("NotD");
    AND(D, CLK, A);
    NOT(D ,NotD);
    AND(NotD, CLK, B);
    NOR(A, Out, C);
    NOR(B, C, Out);

}