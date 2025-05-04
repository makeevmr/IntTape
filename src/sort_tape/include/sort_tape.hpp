#ifndef INT_TAPE_SRC_SORT_TAPE
#define INT_TAPE_SRC_SORT_TAPE

#include "../../tape/include/tape.hpp"

class SortTape {
public:
    static void sortTape(const char* input_tape_file,
                         const char* output_tape_file,
                         const std::size_t max_ram_used,
                         const TapeDelays& tape_delays);

private:
    static void splitTape(Tape& output_tape, Tape& tmp_tape1, Tape& tmp_tape2,
                          const std::size_t& output_tape_size,
                          const std::size_t& sorted_chunk_size);

    static void writeToOutputTape(Tape& output_tape, Tape& other_tape,
                                  std::size_t& other_tape_chunk_read,
                                  std::size_t& other_tape_read,
                                  uint32_t& other_tape_prev_num,
                                  uint32_t& other_tape_new_num);

    static void mergeTapes(Tape& output_tape, Tape& tmp_tape1, Tape& tmp_tape2,
                           std::size_t& parts_to_merge,
                           std::size_t& sorted_chunk_size,
                           std::size_t& tail_size,
                           const std::size_t& output_tape_size);

    static void naturalMergeSort(Tape& output_tape,
                                 const TapeDelays& tape_delays,
                                 std::size_t parts_to_merge,
                                 std::size_t sorted_chunk_size,
                                 std::size_t tail_size);
};

#endif  // INT_TAPE_SRC_SORT_TAPE
