#ifndef INT_TAPE_SRC_CONVERT_FILE
#define INT_TAPE_SRC_CONVERT_FILE

// converts an input file of uint32_t into a contiguous sequence of bytes,
// where each number represents a sequence of 4 bytes
void encode(const char* input_file_name, const char* output_file_name);

// converts an input file where a number is a sequence of 4 bytes into an output
// file of uint32_t
void decode(const char* input_file_name, const char* output_file_name);

#endif  // INT_TAPE_SRC_CONVERT_FILE
