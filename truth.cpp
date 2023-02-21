#include "truth.h"
#include <iostream>

void generate_combinations(Bits& bits, std::size_t i, std::vector<Bits>& output) {
    if (i == bits.size()) {
        output.push_back(bits);
        return;
    }

    bits[i] = false;
    generate_combinations(bits, i+1, output);

    bits[i] = true;
    generate_combinations(bits, i+1, output);
}

std::vector<Bits> generate_all_bits(int N) {
    std::vector<bool> bits(N);
    std::vector<std::vector<bool>> results;
    generate_combinations(bits, 0, results);
    return results;
}

void print_truth_table(Wires inputs, Wires outputs) {
    // print table heading from labels of inputs and outputs
    // A B | Out
    // ---------
    int dashes = 0;
    for (Wire input : inputs) {
        auto label = input->get_label();
        std::cout << label << ' ';
        dashes += label.length() + 1;
    }
    std::cout << "| ";
    for (Wire output : outputs) {
        auto label = output->get_label();
        std::cout << label << ' ';
        dashes += label.length() + 1;
    }
    std::cout << '\n';
    for (int i = 0; i < dashes+1; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';

    // print rows of input and output bit values
    auto bit_sequence = generate_all_bits(inputs.size());
    for (auto bits : bit_sequence) {
        for (std::size_t i = 0; i < inputs.size(); ++i) {
            inputs[i]->set(bits[i]); // set inputs to bit values
        }

        // print bit values of inputs
        for (Wire input : inputs) {
            std::cout << input->get();
            for (std::size_t i = 0; i < input->get_label().length(); ++i) {
                std::cout << ' ';
            }
        }
        std::cout << "| ";

        // print bit values of outputs
        for (Wire output : outputs) {
            std::cout << output->get();
            for (std::size_t i = 0; i < output->get_label().length(); ++i) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
