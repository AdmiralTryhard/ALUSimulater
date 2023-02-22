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
    auto A = make_wire("A");
    auto B = make_wire("B");
    auto Out = make_wire("Out");
    auto NotA = make_wire("NotA");

    NAND(A, B, Out);
    NOT(A, NotA);
    std::cout << "NAND(A,B) -> Out\n";
    print_truth_table({A, B}, {Out});
    std::cout << "NOT(A) -> NotA\n";
    print_truth_table({A}, {NotA});
}
