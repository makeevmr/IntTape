#ifndef INT_TAPE_TAPE_ENCODE
#define INT_TAPE_TAPE_ENCODE

#include <fstream>
// TODO remove include
#include <iostream>

// converts an input file of unsigned int into a contiguous sequence of bytes, where each number
// represents a sequence of 4 bytes
void tapeEncode(const char *file_name);

#endif // INT_TAPE_TAPE_ENCODE
