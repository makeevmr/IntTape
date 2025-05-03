#include "include/tape.hpp"

#include <chrono>
#include <thread>

// for mmap:
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// public
// If the new_file_size is 0 then create a tape of size corresponding to the
// input file, otherwise clear the contents of the file and create tape of size
// corresponding new_file_size
Tape::Tape(const char* file_name, const TapeDelays& delays,
           std::size_t new_file_size)
    : buffer_ind_(0),
      file_ind_(0),
      delays_(delays) {
    fd_ = open(file_name, O_RDWR);
    if (fd_ == -1) {
        handleError("Couldn't open file");
    }
    if (new_file_size == 0) {
        struct stat sb;
        if (fstat(fd_, &sb) == -1) {
            handleError("Error during mmap() call occurred");
        }
        file_size_ = sb.st_size;
    } else {
        if (ftruncate(fd_, 4 * new_file_size) == -1) {
            handleError("Error during ftruncate() call occurred");
        }
        file_size_ = 4 * new_file_size;
    }
    max_buffer_size_ = 2 * page_size;
    curr_buffer_size_ = std::min(file_size_, max_buffer_size_);
    buffer_ = static_cast<unsigned char*>(mmap(nullptr, curr_buffer_size_,
                                               PROT_READ | PROT_WRITE,
                                               MAP_SHARED, fd_, 0U));
    if (buffer_ == MAP_FAILED) {
        handleError("Error during mmap() call occurred");
    }
}

Tape::~Tape() {
    msync((void*)buffer_, curr_buffer_size_, MS_SYNC);
    munmap((void*)buffer_, curr_buffer_size_);
    close(fd_);
}

void Tape::shiftLeft() {
    if (buffer_ind_ > 0) {
        buffer_ind_ -= 4;
        file_ind_ -= 4;
    } else if (file_ind_ > 0) {
        msync((void*)buffer_, curr_buffer_size_, MS_SYNC);
        curr_buffer_size_ = max_buffer_size_;
        buffer_ = static_cast<unsigned char*>(
            mmap(nullptr, curr_buffer_size_, PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd_, file_ind_ - page_size));
        if (buffer_ == MAP_FAILED) {
            handleError("Error during mmap() call occurred");
        }
        file_ind_ -= 4;
        buffer_ind_ = page_size - 4;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(delays_.shift_));
}

bool Tape::shiftRight() {
    bool is_shifted = true;
    if ((buffer_ind_ + 4) < curr_buffer_size_) {
        buffer_ind_ += 4;
        file_ind_ += 4;
    } else if ((file_ind_ + 4) < file_size_) {
        msync((void*)buffer_, curr_buffer_size_, MS_SYNC);
        file_ind_ += 4;
        curr_buffer_size_ =
            std::min(page_size + file_size_ - file_ind_, max_buffer_size_);
        buffer_ = static_cast<unsigned char*>(
            mmap(nullptr, curr_buffer_size_, PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd_, file_ind_ - page_size));
        if (buffer_ == MAP_FAILED) {
            handleError("Error during mmap() call occurred");
        }
        buffer_ind_ = page_size;
    } else {
        is_shifted = false;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(delays_.shift_));
    return is_shifted;
}

void Tape::rewindLeft(unsigned int rewind_length) {
    unsigned int bytes_rewind = rewind_length * 4;
    unsigned int prev_file_ind = file_ind_;
    if (buffer_ind_ >= bytes_rewind) {
        buffer_ind_ -= bytes_rewind;
        file_ind_ -= bytes_rewind;
    } else if (file_ind_ == buffer_ind_) {
        buffer_ind_ = 0;
        file_ind_ = 0;
    } else {
        msync((void*)buffer_, curr_buffer_size_, MS_SYNC);
        curr_buffer_size_ = max_buffer_size_;
        if (file_ind_ <= bytes_rewind) {
            buffer_ = static_cast<unsigned char*>(
                mmap(nullptr, curr_buffer_size_, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fd_, 0U));
            file_ind_ = 0;
            buffer_ind_ = 0;
        } else {
            file_ind_ -= bytes_rewind;
            unsigned int left_buffer = file_ind_ / page_size;
            unsigned int right_buffer = left_buffer + 1;
            unsigned int pages_offset = 0;
            if ((file_ind_ - left_buffer * page_size) <=
                (right_buffer * page_size - file_ind_)) {
                pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
            } else {
                pages_offset = right_buffer - 1;
            }
            buffer_ = static_cast<unsigned char*>(
                mmap(nullptr, curr_buffer_size_, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fd_, pages_offset * page_size));
            buffer_ind_ = file_ind_ - pages_offset * page_size;
        }
        if (buffer_ == MAP_FAILED) {
            handleError("Error during mmap() call occurred");
        }
    }
    unsigned int total_rewind = (prev_file_ind - file_ind_) / 4;
    std::this_thread::sleep_for(
        std::chrono::microseconds(delays_.rewind_ * total_rewind));
}

void Tape::rewindRight(unsigned int rewind_length) {
    unsigned int bytes_rewind = rewind_length * 4;
    unsigned int prev_file_ind = file_ind_;
    if ((buffer_ind_ + bytes_rewind) < curr_buffer_size_) {
        buffer_ind_ += bytes_rewind;
        file_ind_ += bytes_rewind;
    } else if ((file_ind_ + (curr_buffer_size_ - buffer_ind_)) == file_size_) {
        file_ind_ = file_size_ - 4;
        buffer_ind_ = curr_buffer_size_ - 4;
    } else {
        msync((void*)buffer_, curr_buffer_size_, MS_SYNC);
        if ((file_ind_ + bytes_rewind) >= (file_size_ - 4)) {
            file_ind_ = file_size_ - 4;
        } else {
            file_ind_ += bytes_rewind;
        }
        unsigned int left_buffer = file_ind_ / page_size;
        unsigned int right_buffer = left_buffer + 1;
        unsigned int pages_offset = 0;
        if (right_buffer * page_size >= file_size_) {
            pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
        } else {
            if ((file_ind_ - left_buffer * page_size) <=
                (right_buffer * page_size - file_ind_)) {
                pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
            } else {
                pages_offset = right_buffer - 1;
            }
        }
        curr_buffer_size_ =
            std::min(file_size_ - pages_offset * page_size, max_buffer_size_);
        buffer_ = static_cast<unsigned char*>(
            mmap(nullptr, curr_buffer_size_, PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd_, pages_offset * page_size));
        buffer_ind_ = file_ind_ - pages_offset * page_size;
        if (buffer_ == MAP_FAILED) {
            handleError("Error during mmap() call occurred");
        }
    }
    unsigned int total_rewind = (file_ind_ - prev_file_ind) / 4;
    std::this_thread::sleep_for(
        std::chrono::microseconds(delays_.rewind_ * total_rewind));
}

[[nodiscard]] unsigned int Tape::read() const noexcept {
    unsigned int curr_number = 0;
    curr_number |= (static_cast<unsigned int>(buffer_[buffer_ind_]) << 24);
    curr_number |= (static_cast<unsigned int>(buffer_[buffer_ind_ + 1]) << 16);
    curr_number |= (static_cast<unsigned int>(buffer_[buffer_ind_ + 2]) << 8);
    curr_number |= (static_cast<unsigned int>(buffer_[buffer_ind_ + 3]));
    std::this_thread::sleep_for(std::chrono::microseconds(delays_.read_));
    return curr_number;
}

void Tape::write(unsigned int new_number) noexcept {
    buffer_[buffer_ind_] = static_cast<unsigned char>(new_number >> 24);
    buffer_[buffer_ind_ + 1] =
        static_cast<unsigned char>((new_number >> 16) & 0xFF);
    buffer_[buffer_ind_ + 2] =
        static_cast<unsigned char>((new_number >> 8) & 0xFF);
    buffer_[buffer_ind_ + 3] = static_cast<unsigned char>(new_number & 0xFF);
    std::this_thread::sleep_for(std::chrono::microseconds(delays_.write_));
}

[[nodiscard]] std::size_t Tape::getSize() const noexcept {
    return file_size_ / 4;
}

[[nodiscard]] bool Tape::isEnd() const noexcept {
    return (file_ind_ + 4) == file_size_;
}

[[nodiscard]] std::size_t Tape::getPageFileSize() noexcept {
    return page_size / 4;
}

// private
void Tape::handleError(const char* msg) {
    perror(msg);
    exit(255);
}

std::size_t Tape::page_size = sysconf(_SC_PAGE_SIZE);
