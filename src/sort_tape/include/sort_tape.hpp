#ifndef INT_TAPE_SRC_SORT_TAPE
#define INT_TAPE_SRC_SORT_TAPE

#include "../../tape/include/tape.hpp"

class SortTape {
public:
    static void sort(const char* input_tape_file, const char* output_tape_file,
                     const TapeDelays& delays);

private:
    static void naturalMergeSort(Tape& output_tape, const TapeDelays& delays,
                                 std::size_t parts_to_merge,
                                 std::size_t buffer_size,
                                 std::size_t tail_size);
};

#endif  // INT_TAPE_SRC_SORT_TAPE
