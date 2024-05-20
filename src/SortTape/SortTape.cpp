#include "SortTape.h"

// TODO change behaviour
void SortTape::sort(Tape &input_tape) {
    std::size_t tape_size = input_tape.getTapeSize();
    std::size_t page_size = input_tape.getPageFileSize();
    std::size_t tail_size = tape_size % page_size;
    std::size_t iterations =
        (tail_size == 0) ? (tape_size / page_size) : (tape_size / page_size + 1);
    std::vector<unsigned int> array(std::min(tape_size, page_size));
    std::size_t array_len = 0;
    for (std::size_t curr_iter = 0; curr_iter < iterations; ++curr_iter) {
        array[0] = input_tape.read();
        if (curr_iter == iterations - 1) {
            array_len = tail_size > 0 ? tail_size : array.size();
        } else {
            array_len = array.size();
        }
        for (std::size_t i = 1; i < array_len; ++i) {
            input_tape.shiftRight();
            array[i] = input_tape.read();
        }
        std::sort(array.begin(), array.begin() + array_len);
        input_tape.rewindLeft(array_len - 1);
        for (std::size_t i = 0; i < array_len; ++i) {
            input_tape.write(array[i]);
            input_tape.shiftRight();
        }
    }
}
