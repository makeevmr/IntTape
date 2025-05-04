#include "include/sort_tape.hpp"

#include <algorithm>

static constexpr const char* kTmpTape1 = "../tmp/tmp_tape1.txt";
static constexpr const char* kTmpTape2 = "../tmp/tmp_tape2.txt";

void SortTape::sortTape(const char* input_tape_file,
                        const char* output_tape_file,
                        const std::size_t max_ram_used,
                        const TapeDelays& tape_delays) {
    Tape input_tape(input_tape_file, tape_delays);
    std::size_t input_tape_size = input_tape.getSize();
    Tape output_tape(output_tape_file, tape_delays,
                     std::optional<std::size_t>(input_tape_size));
    std::size_t sorted_chunk_size = max_ram_used >= 4 ? max_ram_used / 4 : 1;
    std::size_t tail_size = input_tape_size % sorted_chunk_size;
    std::size_t iterations = input_tape_size / sorted_chunk_size;
    if (tail_size > 0) {
        ++iterations;
    }
    if (max_ram_used >= 8) {
        std::size_t max_buffer_size =
            std::min(input_tape_size, sorted_chunk_size);
        uint32_t* buffer = new uint32_t[max_buffer_size];
        std::size_t buffer_size = 0;
        for (std::size_t curr_iter = 0; curr_iter < iterations; ++curr_iter) {
            buffer_size = max_buffer_size;
            if ((curr_iter == iterations - 1) && (tail_size > 0)) {
                buffer_size = tail_size;
            }
            for (std::size_t i = 0; i < buffer_size; ++i) {
                buffer[i] = input_tape.read();
                input_tape.shiftRight();
            }
            std::sort(buffer, buffer + buffer_size);
            for (std::size_t i = 0; i < buffer_size; ++i) {
                output_tape.write(buffer[i]);
                output_tape.shiftRight();
            }
        }
        delete[] buffer;
    } else {
        for (std::size_t _ = 0; _ < iterations; ++_) {
            output_tape.write(input_tape.read());
            input_tape.shiftRight();
            output_tape.shiftRight();
        }
    }
    if (iterations > 1) {
        naturalMergeSort(output_tape, tape_delays, iterations,
                         sorted_chunk_size, tail_size);
    }
}

void SortTape::splitTape(Tape& output_tape, Tape& tmp_tape1, Tape& tmp_tape2,
                         const std::size_t& output_tape_size,
                         const std::size_t& sorted_chunk_size) {
    bool is_tape1_write = true;
    uint32_t written = 0;
    for (std::size_t i = 0; i < output_tape_size; ++i) {
        uint32_t new_number = output_tape.read();
        output_tape.shiftRight();
        if (written == sorted_chunk_size) {
            is_tape1_write = !is_tape1_write;
            written = 0;
        }
        if (is_tape1_write) {
            tmp_tape1.write(new_number);
            tmp_tape1.shiftRight();
        } else {
            tmp_tape2.write(new_number);
            tmp_tape2.shiftRight();
        }
        ++written;
    }
    output_tape.rewindLeft(output_tape_size - 1);
    tmp_tape1.rewindLeft(tmp_tape1.getSize() - 1);
    tmp_tape2.rewindLeft(tmp_tape2.getSize() - 1);
}

void SortTape::writeToOutputTape(Tape& output_tape, Tape& other_tape,
                                 std::size_t& other_tape_chunk_read,
                                 std::size_t& other_tape_read,
                                 uint32_t& other_tape_prev_num,
                                 uint32_t& other_tape_new_num) {
    output_tape.write(other_tape_new_num);
    ++other_tape_chunk_read;
    ++other_tape_read;
    other_tape.shiftRight();
    other_tape_prev_num = other_tape_new_num;
    other_tape_new_num = other_tape.read();
    output_tape.shiftRight();
}

void SortTape::mergeTapes(Tape& output_tape, Tape& tmp_tape1, Tape& tmp_tape2,
                          std::size_t& parts_to_merge,
                          std::size_t& sorted_chunk_size,
                          std::size_t& tail_size,
                          const std::size_t& output_tape_size) {
    const std::size_t tmp_tape1_size = tmp_tape1.getSize();
    const std::size_t tmp_tape2_size = tmp_tape2.getSize();
    std::size_t tmp_tape1_read = 0;
    std::size_t tmp_tape2_read = 0;
    while ((tmp_tape1_read < tmp_tape1_size) &&
           (tmp_tape2_read < tmp_tape2_size)) {
        std::size_t tmp_tape1_chunk_read = 0;
        std::size_t tmp_tape2_chunk_read = 0;
        uint32_t prev_number1 = 0;
        uint32_t prev_number2 = 0;
        uint32_t new_number1 = tmp_tape1.read();
        uint32_t new_number2 = tmp_tape2.read();
        while ((tmp_tape1_read < tmp_tape1_size) &&
               (tmp_tape2_read < tmp_tape2_size) &&
               (tmp_tape1_chunk_read < sorted_chunk_size) &&
               (tmp_tape2_chunk_read < sorted_chunk_size)) {
            if (new_number1 <= new_number2) {
                writeToOutputTape(output_tape, tmp_tape1, tmp_tape1_chunk_read,
                                  tmp_tape1_read, prev_number1, new_number1);
            } else {
                writeToOutputTape(output_tape, tmp_tape2, tmp_tape2_chunk_read,
                                  tmp_tape2_read, prev_number2, new_number2);
            }
        }
        while ((tmp_tape1_read < tmp_tape1_size) &&
               (tmp_tape1_chunk_read < sorted_chunk_size)) {
            writeToOutputTape(output_tape, tmp_tape1, tmp_tape1_chunk_read,
                              tmp_tape1_read, prev_number1, new_number1);
        }
        while ((tmp_tape2_read < tmp_tape2_size) &&
               (tmp_tape2_chunk_read < sorted_chunk_size)) {
            writeToOutputTape(output_tape, tmp_tape2, tmp_tape2_chunk_read,
                              tmp_tape2_read, prev_number2, new_number2);
        }
    }
    while ((tmp_tape1_read < tmp_tape1_size)) {
        output_tape.write(tmp_tape1.read());
        ++tmp_tape1_read;
        tmp_tape1.shiftRight();
        output_tape.shiftRight();
    }
    while ((tmp_tape2_read < tmp_tape2_size)) {
        output_tape.write(tmp_tape2.read());
        ++tmp_tape2_read;
        tmp_tape2.shiftRight();
        output_tape.shiftRight();
    }
    parts_to_merge = (parts_to_merge / 2) + (parts_to_merge % 2);
    sorted_chunk_size *= 2;
    tail_size = output_tape_size % sorted_chunk_size;
}

void SortTape::naturalMergeSort(Tape& output_tape,
                                const TapeDelays& tape_delays,
                                std::size_t parts_to_merge,
                                std::size_t sorted_chunk_size,
                                std::size_t tail_size) {
    const std::size_t output_tape_size = output_tape.getSize();
    while (parts_to_merge > 1) {
        std::size_t tape1_size = (parts_to_merge / 2) * sorted_chunk_size;
        std::size_t tape2_size = 0;
        if (parts_to_merge % 2 == 1) {
            tape2_size = (parts_to_merge / 2) * sorted_chunk_size;
            if (tail_size == 0) {
                tape1_size += sorted_chunk_size;
            } else {
                tape1_size += tail_size;
            }
        } else {
            tape2_size = (parts_to_merge / 2 - 1) * sorted_chunk_size;
            if (tail_size == 0) {
                tape2_size += sorted_chunk_size;
            } else {
                tape2_size += tail_size;
            }
        }
        output_tape.rewindLeft(output_tape_size - 1);
        Tape tmp_tape1(kTmpTape1, tape_delays,
                       std::optional<std::size_t>(tape1_size));
        Tape tmp_tape2(kTmpTape2, tape_delays,
                       std::optional<std::size_t>(tape2_size));
        splitTape(output_tape, tmp_tape1, tmp_tape2, output_tape_size,
                  sorted_chunk_size);
        mergeTapes(output_tape, tmp_tape1, tmp_tape2, parts_to_merge,
                   sorted_chunk_size, tail_size, output_tape_size);
    }
}
