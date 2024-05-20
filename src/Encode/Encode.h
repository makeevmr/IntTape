#ifndef INT_TAPE_TAPE_ENCODE
#define INT_TAPE_TAPE_ENCODE

#include <fstream>

// converts an input file of unsigned int into a contiguous sequence of bytes, where each number
// represents a sequence of 4 bytes
void encode(const char *input_file_name, const char *output_file_name);

#endif // INT_TAPE_TAPE_ENCODE
