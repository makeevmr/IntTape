#include "include/convert_file.hpp"

#include <fstream>
#include <cassert>
#include <stdexcept>
#include <cstdint>

#define assertm(exp, msg) assert((void(msg), exp))

// converts an input file of uint32_t into a contiguous sequence of bytes,
// where each number represents a sequence of 4 bytes
void encode(const char* input_file_name, const char* output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);
    std::ofstream output_file(output_file_name, std::ios::binary);
    assertm(output_file.is_open(), ("Couldn't open encode output file"));
    if (!input_file.is_open()) {
        throw std::runtime_error(std::string("Couldn't open file: ") +
                                 std::string(input_file_name));
    }
    uint32_t in_number = 0;
    while (input_file.peek() != EOF) {
        input_file >> in_number;
        input_file.get();
        output_file << static_cast<uint8_t>(in_number >> 24);
        output_file << static_cast<uint8_t>((in_number >> 16) & 0xFF);
        output_file << static_cast<uint8_t>((in_number >> 8) & 0xFF);
        output_file << static_cast<uint8_t>(in_number & 0xFF);
    }
    input_file.close();
    output_file.close();
}

// converts an input file where a number is a sequence of 4 bytes into an output
// file of uint32_t
void decode(const char* input_file_name, const char* output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);
    std::ofstream output_file(output_file_name, std::ios::binary);
    assertm(input_file.is_open(), ("Couldn't open decode input file"));
    if (!output_file.is_open()) {
        throw std::runtime_error(std::string("Couldn't open file: ") +
                                 std::string(output_file_name));
    }
    char new_symbol = 0;
    uint32_t out_number = 0;
    uint8_t iter = 0;
    while (input_file.peek() != EOF) {
        ++iter;
        input_file.get(new_symbol);
        out_number |= (static_cast<uint32_t>(static_cast<uint8_t>(new_symbol))
                       << (32 - 8 * iter));
        if (iter == 4) {
            iter = 0;
            output_file << out_number << '\n';
            out_number = 0;
        }
    }
    input_file.close();
    output_file.close();
}
