#include "Tape.h"

// public
Tape::Tape(const char *file_name) : buffer_ind(0), file_ind(0) {
    fd = open(file_name, O_RDWR);
    if (fd == -1) {
        handle_error("Couldn't open file");
    }
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        handle_error("Error during mmap() call occurred");
    }
    file_size = sb.st_size;
    max_buffer_size = 2 * page_size;
    curr_buffer_size = std::min(file_size, max_buffer_size);
    buffer = static_cast<unsigned char *>(
        mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0U));
    if (buffer == MAP_FAILED) {
        handle_error("Error during mmap() call occurred");
    }
}

Tape::~Tape() {
    msync((void *)buffer, curr_buffer_size, MS_SYNC);
    munmap((void *)buffer, curr_buffer_size);
    close(fd);
}

void Tape::moveLeft() {
    if (buffer_ind > 0) {
        buffer_ind -= 4;
        file_ind -= 4;
    } else if (file_ind > 0) {
        msync((void *)buffer, curr_buffer_size, MS_SYNC);
        curr_buffer_size = max_buffer_size;
        buffer = static_cast<unsigned char *>(mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE,
                                                   MAP_SHARED, fd, file_ind - page_size));
        if (buffer == MAP_FAILED) {
            handle_error("Error during mmap() call occurred");
        }
        file_ind -= 4;
        buffer_ind = page_size - 4;
    }
}

void Tape::moveRight() {
    if ((buffer_ind + 4) < curr_buffer_size) {
        buffer_ind += 4;
        file_ind += 4;
    } else if ((file_ind + 4) < file_size) {
        msync((void *)buffer, curr_buffer_size, MS_SYNC);
        file_ind += 4;
        curr_buffer_size = std::min(page_size + file_size - file_ind, max_buffer_size);
        buffer = static_cast<unsigned char *>(mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE,
                                                   MAP_SHARED, fd, file_ind - page_size));
        if (buffer == MAP_FAILED) {
            handle_error("Error during mmap() call occurred");
        }
        buffer_ind = page_size;
    }
}

void Tape::rewindLeft(unsigned int rewind_length) {
    unsigned int bytes_rewind = rewind_length * 4;
    if (buffer_ind >= bytes_rewind) {
        buffer_ind -= bytes_rewind;
        file_ind -= bytes_rewind;
    } else if (file_ind == buffer_ind) {
        buffer_ind = 0;
        file_ind = 0;
    } else {
        msync((void *)buffer, curr_buffer_size, MS_SYNC);
        curr_buffer_size = max_buffer_size;
        if (file_ind <= bytes_rewind) {
            buffer = static_cast<unsigned char *>(
                mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0U));
            file_ind = 0;
            buffer_ind = 0;
        } else {
            file_ind -= bytes_rewind;
            unsigned int left_buffer = file_ind / page_size;
            unsigned int right_buffer = left_buffer + 1;
            unsigned int pages_offset = 0;
            if ((file_ind - left_buffer * page_size) <= (right_buffer * page_size - file_ind)) {
                pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
            } else {
                pages_offset = right_buffer - 1;
            }
            buffer =
                static_cast<unsigned char *>(mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE,
                                                  MAP_SHARED, fd, pages_offset * page_size));
            buffer_ind = file_ind - pages_offset * page_size;
        }
        if (buffer == MAP_FAILED) {
            handle_error("Error during mmap() call occurred");
        }
    }
}

void Tape::rewindRight(unsigned int rewind_length) {
    unsigned int bytes_rewind = rewind_length * 4;
    if ((buffer_ind + bytes_rewind) < curr_buffer_size) {
        buffer_ind += bytes_rewind;
        file_ind += bytes_rewind;
    } else if ((file_ind + (curr_buffer_size - buffer_ind)) == file_size) {
        file_ind = file_size - 4;
        buffer_ind = curr_buffer_size - 4;
    } else {
        msync((void *)buffer, curr_buffer_size, MS_SYNC);
        if ((file_ind + bytes_rewind) >= (file_size - 4)) {
            file_ind = file_size - 4;
        } else {
            file_ind += bytes_rewind;
        }
        unsigned int left_buffer = file_ind / page_size;
        unsigned int right_buffer = left_buffer + 1;
        unsigned int pages_offset = 0;
        if (right_buffer * page_size >= file_size) {
            pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
        } else {
            if ((file_ind - left_buffer * page_size) <= (right_buffer * page_size - file_ind)) {
                pages_offset = left_buffer == 0 ? 0 : left_buffer - 1;
            } else {
                pages_offset = right_buffer - 1;
            }
        }
        curr_buffer_size = std::min(file_size - pages_offset * page_size, max_buffer_size);
        buffer = static_cast<unsigned char *>(mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE,
                                                   MAP_SHARED, fd, pages_offset * page_size));
        buffer_ind = file_ind - pages_offset * page_size;
        if (buffer == MAP_FAILED) {
            handle_error("Error during mmap() call occurred");
        }
    }
}

[[nodiscard]] unsigned int Tape::read() const noexcept {
    unsigned int curr_number = 0;
    curr_number |= (static_cast<unsigned int>(buffer[buffer_ind]) << 24);
    curr_number |= (static_cast<unsigned int>(buffer[buffer_ind + 1]) << 16);
    curr_number |= (static_cast<unsigned int>(buffer[buffer_ind + 2]) << 8);
    curr_number |= (static_cast<unsigned int>(buffer[buffer_ind + 3]));
    return curr_number;
}

void Tape::write(unsigned int new_number) noexcept {
    buffer[buffer_ind] = static_cast<unsigned char>(new_number >> 24);
    buffer[buffer_ind + 1] = static_cast<unsigned char>((new_number >> 16) & 0xFF);
    buffer[buffer_ind + 2] = static_cast<unsigned char>((new_number >> 8) & 0xFF);
    buffer[buffer_ind + 3] = static_cast<unsigned char>(new_number & 0xFF);
}

// private
void Tape::handle_error(const char *msg) {
    perror(msg);
    exit(255);
}

std::size_t Tape::page_size = sysconf(_SC_PAGE_SIZE);
