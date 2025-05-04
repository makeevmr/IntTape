#include "include/tape.hpp"

#include <chrono>
#include <stdexcept>
#include <thread>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// Creates a tape associated with file_name file.
// Changes file size to contain new_file_size elements if new_file_size was
// provided
Tape::Tape(const char* file_name, const TapeDelays& tape_delays,
           const std::optional<std::size_t> new_file_size)
    : fd_(open(file_name, O_RDWR)),
      tape_ind_(0),
      tape_delays_(tape_delays) {
    if (fd_ == -1) {
        throw std::runtime_error(std::string("Couldn't open file: ") +
                                 std::string(file_name));
    }
    if (!new_file_size.has_value()) {
        struct stat sb;
        if (fstat(fd_, &sb) == -1) {
            throw std::runtime_error(
                std::string("Error during fstat() call with code: ") +
                std::to_string(errno));
        }
        tape_size_ = static_cast<std::size_t>(sb.st_size);
    } else {
        std::size_t new_tape_size =
            static_cast<std::size_t>(kShiftSize) * new_file_size.value();
        if (ftruncate(fd_, static_cast<int64_t>(new_tape_size)) == -1) {
            throw std::runtime_error(
                std::string("Error during ftruncate() call with code: ") +
                std::to_string(errno));
        }
        tape_size_ = new_tape_size;
    }
}

Tape::~Tape() {
    close(fd_);
}

void Tape::shiftLeft() {
    if (tape_ind_ > 0) {
        if (lseek(fd_, -kShiftSize, SEEK_CUR) == -1) {
            throw std::runtime_error(
                std::string("Error during lseek() call with code: ") +
                std::to_string(errno));
        }
        tape_ind_ -= static_cast<std::size_t>(kShiftSize);
        std::this_thread::sleep_for(
            std::chrono::microseconds(tape_delays_.shift_));
    }
}

void Tape::shiftRight() {
    if ((tape_ind_ + static_cast<std::size_t>(kShiftSize)) < tape_size_) {
        if (lseek(fd_, kShiftSize, SEEK_CUR) == -1) {
            throw std::runtime_error(
                std::string("Error during lseek() call with code: ") +
                std::to_string(errno));
        }
        tape_ind_ += static_cast<std::size_t>(kShiftSize);
        std::this_thread::sleep_for(
            std::chrono::microseconds(tape_delays_.shift_));
    }
}

void Tape::rewindLeft(std::size_t rewind_length) {
    while ((rewind_length > 0) && (tape_ind_ > 0)) {
        --rewind_length;
        shiftLeft();
    }
}

void Tape::rewindRight(std::size_t rewind_length) {
    while ((rewind_length > 0) &&
           ((tape_ind_ + static_cast<std::size_t>(kShiftSize)) < tape_size_)) {
        --rewind_length;
        shiftRight();
    }
}

[[nodiscard]] uint32_t Tape::read() {
    uint8_t num_buffer[kShiftSize];
    if (::read(fd_, num_buffer, kShiftSize) == -1) {
        throw std::runtime_error(
            std::string("Error during read() call with code: ") +
            std::to_string(errno));
    }
    if (lseek(fd_, -kShiftSize, SEEK_CUR) == -1) {
        throw std::runtime_error(
            std::string("Error during lseek() call with code: ") +
            std::to_string(errno));
    }
    uint32_t num = 0;
    int bit_shift = 8 * kShiftSize;
    for (int i = 0; i < kShiftSize; ++i) {
        bit_shift -= 8;
        num |= (static_cast<uint32_t>(num_buffer[i]) << bit_shift);
    }
    std::this_thread::sleep_for(std::chrono::microseconds(tape_delays_.read_));
    return num;
}

void Tape::write(const uint32_t new_num) {
    uint8_t num_buffer[kShiftSize];
    int bit_shift = 8 * kShiftSize;
    for (int i = 0; i < kShiftSize; ++i) {
        bit_shift -= 8;
        num_buffer[i] = static_cast<uint8_t>((new_num >> bit_shift) & 0xFF);
    }
    if (::write(fd_, num_buffer, kShiftSize) == -1) {
        throw std::runtime_error(
            std::string("Error during write() call with code: ") +
            std::to_string(errno));
    }
    if (lseek(fd_, -kShiftSize, SEEK_CUR) == -1) {
        throw std::runtime_error(
            std::string("Error during lseek() call with code: ") +
            std::to_string(errno));
    }
    std::this_thread::sleep_for(std::chrono::microseconds(tape_delays_.write_));
}

[[nodiscard]] std::size_t Tape::getSize() const noexcept {
    return tape_size_ / kShiftSize;
}
