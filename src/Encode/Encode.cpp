#include "Encode.h"

// converts an input file of unsigned int into a contiguous sequence of bytes, where each number
// represents a sequence of 4 bytes
void encode(const char *input_file_name, const char *output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);
    std::ofstream output_file(output_file_name, std::ios::binary);
    unsigned int new_number = 0;
    if (input_file.is_open() && output_file.is_open()) {
        while (input_file.peek() != EOF) {
            input_file >> new_number;
            input_file.get();
            output_file << static_cast<unsigned char>(new_number >> 24);
            output_file << static_cast<unsigned char>((new_number >> 16) & 0xFF);
            output_file << static_cast<unsigned char>((new_number >> 8) & 0xFF);
            output_file << static_cast<unsigned char>(new_number & 0xFF);
        }
    }
    input_file.close();
    output_file.close();
}
