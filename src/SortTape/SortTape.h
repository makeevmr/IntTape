#ifndef INT_TAPE_SORT_TAPE
#define INT_TAPE_SORT_TAPE

#include "../Tape/Tape.h"
#include <vector>

#define TMP_TAPE1 "tmp/tmp_tape1.txt"
#define TMP_TAPE2 "tmp/tmp_tape2.txt"

class SortTape {
public:
    static void sort(const char *input_tape_file, const char *output_tape_file,
                     const TapeDelays &delays);

private:
    static void naturalMergeSort(Tape &output_tape, const TapeDelays &delays,
                                 std::size_t parts_to_merge, std::size_t buffer_size,
                                 std::size_t tail_size);
};

#endif // INT_TAPE_SORT_TAPE
