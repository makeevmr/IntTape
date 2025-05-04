#ifndef INT_TAPE_SRC_SORT_TAPE
#define INT_TAPE_SRC_SORT_TAPE

#include "../../tape/include/tape.hpp"

void sortTape(const char* input_tape_file, const char* output_tape_file,
              const std::size_t max_ram_used, const TapeDelays& tape_delays);

#endif  // INT_TAPE_SRC_SORT_TAPE
