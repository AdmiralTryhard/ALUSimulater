#include "gates.h"
#include "truth.h"
#include <iostream>


void test_nand();

int main() {
    try {
        test_nand();
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
}


void test_nand() {
    auto F0 = make_wire("F0");
    auto F1 = make_wire("F1");
    auto Cin = make_wire("Cin");
    auto Cout = make_wire("Cout");
    auto A = make_wire("A");
    auto B = make_wire("B");
    auto Out = make_wire("Out");
    auto NotA = make_wire("NotA");
    ALU(F0, F1, A, B, Cin, Out, Cout);

    std::cout << "Here is some addition\n";
    int added = add_bits(255, 255, 8);

    std::cout << "\n Here is the final result \n" << added <<'\n';


}
