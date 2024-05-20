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
