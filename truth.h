#pragma once
// A collection useful functions for building truth tables of gates

#include "wire.h"
#include <vector>

using Bits = std::vector<bool>;

// Generate all possible bit combinations
void generate_combinations(Bits& bits, std::size_t i, std::vector<Bits>& output);
std::vector<Bits> generate_all_bits(int N);

// Main function to use!
// Generates an ascii truth table by changing inputs and recording resulting outputs
void print_truth_table(Wires inputs, Wires outputs);
