#include "SortTape.h"

// public
void SortTape::sort(const char *input_tape_file, const char *output_tape_file,
                    const TapeDelays &delays) {
    Tape input_tape(input_tape_file, delays);
    std::size_t input_tape_size = input_tape.getSize();
    std::size_t max_buffer_size = Tape::getPageFileSize();
    Tape output_tape(output_tape_file, delays, input_tape_size);
    std::size_t tail_size = input_tape_size % max_buffer_size;
    std::size_t iterations = (tail_size == 0) ? (input_tape_size / max_buffer_size)
                                              : (input_tape_size / max_buffer_size + 1);
    std::vector<unsigned int> array(std::min(input_tape_size, max_buffer_size));
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
        for (std::size_t i = 0; i < array_len; ++i) {
            output_tape.write(array[i]);
            output_tape.shiftRight();
        }
        input_tape.shiftRight();
    }
    if (iterations > 1) {
        naturalMergeSort(output_tape, delays, iterations, max_buffer_size, tail_size);
    }
}

// private
void SortTape::naturalMergeSort(Tape &output_tape, const TapeDelays &delays,
                                std::size_t parts_to_merge, std::size_t buffer_size,
                                std::size_t tail_size) {
    const std::size_t output_tape_size = output_tape.getSize();
    while (parts_to_merge > 1) {
        std::size_t tape1_size = (parts_to_merge / 2) * buffer_size;
        std::size_t tape2_size = 0;
        if (parts_to_merge % 2 == 1) {
            tape2_size = (parts_to_merge / 2) * buffer_size;
            if (tail_size == 0) {
                tape1_size += buffer_size;
            } else {
                tape1_size += tail_size;
            }
        } else {
            tape2_size = (parts_to_merge / 2 - 1) * buffer_size;
            if (tail_size == 0) {
                tape2_size += buffer_size;
            } else {
                tape2_size += tail_size;
            }
        }
        output_tape.rewindLeft(output_tape_size - 1);
        Tape tmp_tape1(TMP_TAPE1, delays, tape1_size);
        Tape tmp_tape2(TMP_TAPE2, delays, tape2_size);
        unsigned int first_number = output_tape.read();
        tmp_tape1.write(first_number);
        tmp_tape1.shiftRight();
        bool tape1_write = true;
        unsigned int prev_number = first_number;
        for (std::size_t i = 1; i < output_tape_size; ++i) {
            output_tape.shiftRight();
            unsigned int new_number = output_tape.read();
            if (prev_number > new_number) {
                tape1_write = !tape1_write;
            }
            if (tape1_write) {
                tmp_tape1.write(new_number);
                tmp_tape1.shiftRight();
            } else {
                tmp_tape2.write(new_number);
                tmp_tape2.shiftRight();
            }
            prev_number = new_number;
        }
        output_tape.rewindLeft(output_tape_size - 1);
        tmp_tape1.rewindLeft(tmp_tape1.getSize() - 1);
        tmp_tape2.rewindLeft(tmp_tape2.getSize() - 1);
        bool is_tape1_end = false;
        bool is_tape2_end = false;
        while (!is_tape1_end && !is_tape2_end) {
            unsigned int prev_number1 = 0;
            unsigned int prev_number2 = 0;
            unsigned int new_number1 = tmp_tape1.read();
            unsigned int new_number2 = tmp_tape2.read();
            while (!is_tape1_end && !is_tape2_end && (prev_number1 <= new_number1) &&
                   (prev_number2 <= new_number2)) {
                if (new_number1 <= new_number2) {
                    output_tape.write(new_number1);
                    is_tape1_end = !tmp_tape1.shiftRight();
                    prev_number1 = new_number1;
                    new_number1 = tmp_tape1.read();
                } else {
                    output_tape.write(new_number2);
                    is_tape2_end = !tmp_tape2.shiftRight();
                    prev_number2 = new_number2;
                    new_number2 = tmp_tape2.read();
                }
                output_tape.shiftRight();
            }
            while (!is_tape1_end && (prev_number1 <= new_number1)) {
                output_tape.write(new_number1);
                is_tape1_end = !tmp_tape1.shiftRight();
                output_tape.shiftRight();
                prev_number1 = new_number1;
                new_number1 = tmp_tape1.read();
            }
            while (!is_tape2_end && (prev_number2 <= new_number2)) {
                output_tape.write(new_number2);
                is_tape2_end = !tmp_tape2.shiftRight();
                output_tape.shiftRight();
                prev_number2 = new_number2;
                new_number2 = tmp_tape2.read();
            }
        }
        while (!is_tape1_end) {
            output_tape.write(tmp_tape1.read());
            output_tape.shiftRight();
            is_tape1_end = !tmp_tape1.shiftRight();
        }
        while (!is_tape2_end) {
            output_tape.write(tmp_tape2.read());
            output_tape.shiftRight();
            is_tape2_end = !tmp_tape2.shiftRight();
        }
        parts_to_merge = (parts_to_merge / 2) + (parts_to_merge % 2);
        buffer_size *= 2;
        tail_size = output_tape_size % buffer_size;
    }
}
